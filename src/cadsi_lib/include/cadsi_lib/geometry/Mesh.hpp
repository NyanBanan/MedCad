//
// Created by nyanbanan on 20.04.2024.
//

#ifndef CADSI_MESH_HPP
#define CADSI_MESH_HPP

#include <QFileInfo>
#include <QString>
#include <ranges>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkClipPolyData.h>
#include <vtkContourTriangulator.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkDelaunay3D.h>
#include <vtkElevationFilter.h>
#include <vtkExtractPolyDataGeometry.h>
#include <vtkFeatureEdges.h>
#include <vtkFillHolesFilter.h>
#include <vtkIdFilter.h>
#include <vtkImplicitDataSet.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>
#include <vtkPlanes.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkReverseSense.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkTransform.h>
#include <vtkVector.h>

#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/file_data/FileDataErrors.hpp"
#include "cadsi_lib/geometry/Point3d.hpp"

namespace cadsi_lib::geometry {
    class Mesh : public vtkPolyData {
    public:
        static Mesh* New();

        OperationStatus load(const QString& file_name);
        OperationStatus save(const QString& file_path, bool binary = true);
        Mesh* vectorExtrude(vtkVector3d direction);
        void clean();
        void reverseSense();
        void fillHoles(double hole_size = 1000);
        void closeMesh();
        Mesh* openEdges();
        Mesh* clipByMesh(Mesh* mesh, bool inverse);
        Mesh* clipByMesh(vtkPlanes* mesh, bool inverse);
        Mesh* selectSphere(Point3d center, double radius);
        Mesh* filterVisible(vtkRenderer* renderer);

        Mesh* computeOriginalIds();
        QList<uint> getOriginalIds();

        Mesh* applyTransform(vtkTransform* transform);
        double* bounds();

        static Mesh* createSphere(vtkVector3d center = {0, 0, 0},
                                  double radius = 2,
                                  int resolution_theta = 31,
                                  int resolution_phi = 31);

        static Mesh* fromPoints(vtkPoints* points_list);

        static Mesh* fromMeshes(QList<Mesh*> args);

        static Mesh* fromMeshes(std::convertible_to<Mesh*> auto... args) {
            vtkNew<vtkAppendPolyData> appender;
            (appender->AddInputData(args), ...);
            appender->Update();
            auto mesh = new Mesh;
            mesh->DeepCopy(appender->GetOutput());
            return mesh;
        }

    private:
        template<typename SaverType>
        OperationStatus saveWithSaverType(const QString& file_path, bool binary) {
            vtkNew<SaverType> writer;
            writer->SetFileName(file_path.toStdString().c_str());
            if (binary) {
                writer->SetFileTypeToBinary();
            } else {
                writer->SetFileTypeToASCII();
            }
            writer->SetInputData(this);
            auto result = writer->Write();
            if (result == 0) {
                return {.success = false,
                        .error_code = writer->GetErrorCode(),
                        .error_message = "Error on write from vtk, check vtk error_code"};
            } else {
                return {true};
            }
        }
    };
}    //namespace cadsi_lib::geometry
#endif    //CADSI_MESH_HPP
