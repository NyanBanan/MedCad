//
// Created by nyanbanan on 20.04.2024.
//

#include "cadsi_lib/geometry/Mesh.hpp"

#include <vtkSelectVisiblePoints.h>
#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkTransformPolyDataFilter.h>

namespace cadsi_lib::geometry {

    Mesh* Mesh::New() {
        return new Mesh;
    }

    OperationStatus Mesh::load(const QString& file_name) {
        QFileInfo file_info(file_name);
        if (!file_info.exists()) {
            return {.success = false, .error_code = file_data::ErrorCodes::FILE_NOT_EXIST};
        } else if (!file_info.isFile()) {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = file_name.toStdString() + " is not a file"};
        }
        auto extension = file_info.completeSuffix();
        vtkSmartPointer<vtkAbstractPolyDataReader> reader;
        if (extension == "ply") {
            reader = vtkSmartPointer<vtkPLYReader>::New();
        } else if (extension == "stl") {
            reader = vtkSmartPointer<vtkSTLReader>::New();
        } else {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "Wrong file format, supported formats .stl and .ply"};
        }
        //TODO: There is also link_to_file in original, but I dont know which purpose for it, so, I dont make link, but should remember if errors will occur
        reader->SetFileName(file_name.toStdString().c_str());
        reader->Update();
        vtkPolyData::DeepCopy(reader->GetOutput());
        return {true};
    }

    OperationStatus Mesh::save(const QString& file_path, bool binary) {
        QFileInfo file_info(file_path);
        /*if (!file_info.isFile()) {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "file_path must be a file"};
        }*/
        auto extension = file_info.completeSuffix();
        if (extension == "ply") {
            return saveWithSaverType<vtkPLYWriter>(file_path, binary);
        } else if (extension == "stl") {
            return saveWithSaverType<vtkSTLWriter>(file_path, binary);
        } else {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "Wrong file format, supported formats .stl and .ply"};
        }
    }

    Mesh* Mesh::vectorExtrude(vtkVector3d direction) {
        vtkNew<vtkLinearExtrusionFilter> extruder;
        extruder->SetInputData(this);
        extruder->SetExtrusionTypeToVectorExtrusion();
        extruder->SetVector(-direction.GetX(), -direction.GetY(), -direction.GetZ());
        extruder->Update();

        vtkNew<Mesh> mesh;
        mesh->DeepCopy(extruder->GetOutput());
        return mesh;
    }

    void Mesh::clean() {
        vtkNew<vtkCleanPolyData> cleaner;
        cleaner->SetInputData(this);
        cleaner->Update();
        this->DeepCopy(cleaner->GetOutput());
    }

    void Mesh::reverseSense() {
        vtkNew<vtkReverseSense> reverse;
        reverse->SetInputData(this);
        reverse->ReverseCellsOn();
        reverse->ReverseNormalsOn();
        reverse->Update();
        this->DeepCopy(reverse->GetOutput());
    }

    void Mesh::fillHoles(double hole_size) {
        vtkNew<vtkFillHolesFilter> filler;
        filler->SetInputData(this);
        filler->SetHoleSize(hole_size);
        filler->Update();
        this->DeepCopy(filler->GetOutput());
    }

    void Mesh::closeMesh() {
        vtkNew<vtkContourTriangulator> triang;
        triang->SetInputData(openEdges());
        triang->Update();
        vtkNew<Mesh> contours;
        contours->DeepCopy(triang->GetOutput());
        auto filled = Mesh::fromMeshes(this, contours.Get());
        filled->clean();
    }

    Mesh* Mesh::openEdges() {
        vtkNew<vtkFeatureEdges> edge_extr;
        edge_extr->SetInputData(this);
        edge_extr->BoundaryEdgesOn();
        edge_extr->FeatureEdgesOff();
        edge_extr->Update();
        auto mesh = new Mesh;
        mesh->DeepCopy(edge_extr->GetOutput());
        return mesh;
    }

    Mesh* Mesh::clipByMesh(Mesh* mesh, bool inverse) {
        // Используем трехмерную триангуляцию делоне, чтобы разбить меш на примитивы
        // Наверное можно без этого
        vtkNew<vtkDelaunay3D> tri;
        tri->SetInputData(mesh);
        tri->BoundingTriangulationOff();

        // Нужна какая-нибудь скалярная величина, чтобы понимать где нутрь, а где наружа
        vtkNew<vtkElevationFilter> elev;
        elev->SetInputConnection(tri->GetOutputPort());
        elev->Update();
        // Преобразуем в неявную функию
        vtkNew<vtkImplicitDataSet> implicit;
        implicit->SetDataSet(elev->GetOutput());

        // Оставляем только ту часть меша what (предположительно более сложного)
        // Которая находится внутри меша by_what
        vtkNew<vtkClipPolyData> cpd;
        cpd->SetClipFunction(implicit);
        cpd->SetInputData(this);
        cpd->SetInsideOut(inverse);
        cpd->Update();
        auto result_mesh = new Mesh;
        result_mesh->DeepCopy(cpd->GetOutput());
        return result_mesh;
    }

    Mesh* Mesh::clipByMesh(vtkPlanes* mesh, bool inverse) {
        vtkNew<vtkExtractPolyDataGeometry> es;
        es->SetInputData(this);
        es->SetImplicitFunction(mesh);
        es->SetExtractInside(!inverse);
        es->Update();
        auto result_mesh = new Mesh;
        result_mesh->DeepCopy(es->GetOutput());
        return result_mesh;
    }

    Mesh* Mesh::selectSphere(Point3d center, double radius) {
        vtkNew<vtkSphere> sphere;
        sphere->SetCenter(center.getData());
        sphere->SetRadius(radius);

        vtkNew<vtkExtractPolyDataGeometry> extractor;
        extractor->SetInputData(this);
        extractor->SetImplicitFunction(sphere);
        extractor->Update();
        auto mesh = new Mesh;
        mesh->DeepCopy(extractor->GetOutput());
        return mesh;
    }

    Mesh* Mesh::filterVisible(vtkRenderer* renderer) {
        vtkNew<vtkSelectVisiblePoints> selector;
        selector->SetInputData(this);
        selector->SetRenderer(renderer);
        selector->Update();
        auto mesh = new Mesh;
        mesh->DeepCopy(selector->GetOutput());
        return mesh;
    }

    Mesh* Mesh::computeOriginalIds() {
        auto ids_array = GetPointData()->GetArray("OriginalIds");
        if (ids_array != nullptr) {
            return this;
        } else {
            vtkNew<vtkIdFilter> filter;
            filter->SetInputData(this);
            filter->PointIdsOn();
            filter->SetPointIdsArrayName("OriginalIds");
            filter->Update();

            vtkNew<vtkDataSetSurfaceFilter> surf_filter;
            surf_filter->SetInputConnection(filter->GetOutputPort());
            surf_filter->Update();
            auto mesh = new Mesh;
            mesh->DeepCopy(surf_filter->GetOutput());
            return mesh;
        }
    }

    QList<uint> Mesh::getOriginalIds() {
        QList<uint> result;
        auto ids_array = GetPointData()->GetArray("OriginalIds");
        if (ids_array != nullptr) {
            for (auto val : std::ranges::iota_view(0, ids_array->GetNumberOfValues())) {
                result.append(ids_array->GetVariantValue(val).ToUnsignedInt());
            }
        }
        return result;
    }

    Mesh* Mesh::applyTransform(vtkTransform* transform) {
        transform->Modified();

        vtkNew<vtkTransformPolyDataFilter> tpdf;
        tpdf->SetInputData(this);
        tpdf->SetTransform(transform);
        tpdf->Update();

        auto mesh = new Mesh;
        mesh->DeepCopy(tpdf->GetOutput());
        return mesh;
    }

    double* Mesh::bounds() {
        vtkPointSet::ComputeBounds();
        return GetBounds();
    }

    Mesh* Mesh::createSphere(vtkVector3d center, double radius, int resolution_theta, int resolution_phi) {
        vtkNew<vtkSphereSource> sphere;
        sphere->SetCenter(center.GetData());
        sphere->SetRadius(radius);
        sphere->SetThetaResolution(resolution_theta);
        sphere->SetPhiResolution(resolution_phi);
        sphere->Update();
        auto mesh = new Mesh;
        mesh->DeepCopy(sphere->GetOutput());
        return mesh;
    }

    Mesh* Mesh::fromPoints(vtkPoints* points_list) {
        vtkNew<vtkPolyData> poly_data;
        vtkNew<vtkCellArray> lines;
        auto num_of_points = (int)points_list->GetNumberOfPoints();
        lines->InsertNextCell(num_of_points + 1);
        for (auto i : std::views::iota(0, num_of_points)) {
            lines->InsertCellPoint(i);
        }
        lines->InsertCellPoint(0);
        poly_data->SetPoints(points_list);
        poly_data->SetLines(lines);
        auto mesh = new Mesh;
        mesh->DeepCopy(poly_data);
        return mesh;
    }

    Mesh* Mesh::fromMeshes(QList<Mesh*> args) {
        vtkNew<vtkAppendPolyData> appender;
        std::ranges::for_each(args, [&appender](Mesh* arg) {
            appender->AddInputData(arg);
        });
        appender->Update();
        auto mesh = new Mesh;
        mesh->DeepCopy(appender->GetOutput());
        return mesh;
    }

}    //namespace cadsi_lib::geometry
