//
// Created by nyanbanan on 13.04.2024.
//

#ifndef CADSI_DICOMIMAGE_HPP
#define CADSI_DICOMIMAGE_HPP

#include <QHash>
#include <filesystem>
#include <vtkDICOMDataElement.h>

#include "DicomMetaDataHashCollection.hpp"
#include "DicomTagStdHashSpecialization.hpp"

namespace cadsi_lib::dicom {
    class DicomImage : public DicomMetaDataHashCollection{
    public:
        DicomImage() = default;
        DicomImage(const QString& imageFile);
        DicomImage(QString&& imageFile);

        [[nodiscard]] const QString& getImageFilePath() const;
        void setImageFile(const QString& imageFile);
        void setImageFile(QString&& imageFile);

    private:
        QString _image_file;
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_DICOMIMAGE_HPP
