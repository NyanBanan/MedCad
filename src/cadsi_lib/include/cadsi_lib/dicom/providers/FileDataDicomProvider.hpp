//
// Created by nyanbanan on 13.04.2024.
//

#ifndef CADSI_FILEDATADICOMPROVIDER_HPP
#define CADSI_FILEDATADICOMPROVIDER_HPP

#include <QFileInfo>
#include <ranges>
#include <string>
#include <vtkDICOMCTRectifier.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMFileSorter.h>
#include <vtkDICOMItem.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMParser.h>
#include <vtkDICOMReader.h>
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkStringArray.h>

#include "DicomProvider.hpp"
#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/Result.hpp"
#include "cadsi_lib/dicom/DicomPatient.hpp"
#include "cadsi_lib/dicom/PreviewImage.hpp"
#include "cadsi_lib/file_data/FileDataErrors.hpp"
#include "cadsi_lib/volumes/VolumeObject.hpp"

namespace cadsi_lib::dicom::providers {

    class FileDataDicomProvider : public DicomProvider {
    public:
        Result<QList<DicomPatient>> getAllPatients() override;
        Result<QList<DicomPatient>> readDir(const QString& dir_path);

    private:
        QImage createPreviewImage(vtkDICOMReader* reader);

        QList<DicomPatient> _patients;
    };

}    //namespace cadsi_lib::dicom::providers

//TODO: check private dicts
#endif    //CADSI_FILEDATADICOMPROVIDER_HPP
