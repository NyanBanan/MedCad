//
// Created by nyanbanan on 21.04.2024.
//

#include "cadsi_lib/volumes/VolumeImage.hpp"

namespace cadsi_lib::volumes{

    OperationStatus VolumeImage::load(const QString& file_name) {
        QFileInfo file_info(file_name);
        if (!file_info.exists()) {
            return {.success = false, .error_code = file_data::ErrorCodes::FILE_NOT_EXIST};
        } else if (!file_info.isFile()) {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = file_name.toStdString() + " is not a file"};
        }
        auto extension = file_info.completeSuffix();
        if (extension == "vti") {
            vtkNew<vtkXMLImageDataReader> reader;
            //TODO: There is also link_to_file in original, but I dont know which purpose for it, so, I dont make link, but should remember if errors will occur
            reader->SetFileName(file_name.toStdString().c_str());
            reader->Update();
            return load(reader->GetOutput());
        } else {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "Wrong file format, supported formats .stl and .ply"};
        }
    }

    OperationStatus VolumeImage::load(vtkImageData* data) {
        vtkImageData::DeepCopy(data);
        return {true};
    }

    OperationStatus VolumeImage::save(const QString& file_name) {
        QFileInfo file_info(file_name);
        if (!file_info.isFile()) {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = file_name.toStdString() + " is not a file"};
        }
        auto extension = file_info.completeSuffix();
        if (extension == "vti") {
            vtkNew<vtkXMLImageDataWriter> writer;
            //TODO: There is also link_to_file in original, but I dont know which purpose for it, so, I dont make link, but should remember if errors will occur
            writer->SetFileName(file_name.toStdString().c_str());
            writer->Update();
            auto result = writer->Write();
            if (result == 0) {
                return {.success = false,
                        .error_code = writer->GetErrorCode(),
                        .error_message = "Error on write from vtkXMLImageDataWriter, check vtk error_code"};
            } else {
                return {true};
            }
        } else {
            return {.success = false,
                    .error_code = file_data::ErrorCodes::WRONG_FILE_FORMAT,
                    .error_message = "Wrong file format, supported formats .stl and .ply"};
        }
    }
}    //namespace cadsi_lib
