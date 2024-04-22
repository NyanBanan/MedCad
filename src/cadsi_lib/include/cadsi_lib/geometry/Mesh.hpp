//
// Created by nyanbanan on 20.04.2024.
//

#ifndef CADSI_MESH_HPP
#define CADSI_MESH_HPP

#include <QFileInfo>
#include <QString>
#include <vtkPLYReader.h>
#include <vtkPLYWriter.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>

#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/file_data/FileDataErrors.hpp"

namespace cadsi_lib::geometry {
    class Mesh : public vtkPolyData {
    public:
        OperationStatus load(const QString& file_name);
        OperationStatus load(vtkPolyData* data);
        OperationStatus save(const QString& file_path, bool binary);

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
