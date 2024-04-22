//
// Created by nyanbanan on 13.04.2024.
//

#include "cadsi_lib/dicom/DicomImage.hpp"

namespace cadsi_lib::dicom {
    DicomImage::DicomImage(const QString& imageFile) : _image_file(imageFile) {}

    DicomImage::DicomImage(QString&& imageFile) : _image_file(imageFile) {}

    const QString& DicomImage::getImageFilePath() const {
        return _image_file;
    }

    void DicomImage::setImageFile(const QString& imageFile) {
        _image_file = imageFile;
    }

    void DicomImage::setImageFile(QString&& imageFile) {
        _image_file = imageFile;
    }
}    //namespace cadsi_lib::dicom
