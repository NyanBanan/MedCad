//
// Created by nyanbanan on 20.04.2024.
//

#include "cadsi_lib/geometry/Mesh.hpp"

namespace cadsi_lib::geometry {

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
        return load(reader->GetOutput());
    }

    OperationStatus Mesh::load(vtkPolyData* data) {
        vtkPolyData::DeepCopy(data);
        return {true};
    }

    OperationStatus Mesh::save(const QString& file_path, bool binary) {
        QFileInfo file_info(file_path);
        if (!file_info.isFile()) {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "file_path must be a file"};
        }
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
}    //namespace cadsi_lib::geometry
