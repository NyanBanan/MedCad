//
// Created by nyanbanan on 04.05.2024.
//

#include "ImageObject.hpp"

void ImageObject::loadImage(vtkImageData* image_data) {
    if (_image_data.Get() == nullptr) {
        _image_data = new cadsi_lib::volumes::VolumeImage;
    }
    _image_data->DeepCopy(image_data);
    emit imageLoaded();
}

void ImageObject::setSmooth(double sigma, double r) {
    if (_image_data.Get() != nullptr) {
        cadsi_lib::volumes::VolumeImageTransformations::smoothInplace(_image_data, sigma, r);
        emit imageUpdated();
    }
}

void ImageObject::setDenoise(double factor, double threshold) {
    if (_image_data.Get() != nullptr) {
        cadsi_lib::volumes::VolumeImageTransformations::denoiseInplace(_image_data, factor, threshold);
        emit imageUpdated();
    }
}

void ImageObject::setEnhance() {
    if (_image_data.Get() != nullptr) {
        cadsi_lib::volumes::VolumeImageTransformations::enhanceInplace(_image_data);
        emit imageUpdated();
    }
}

void ImageObject::flipImage(cadsi_lib::volumes::VolumeImageTransformations::FlipAxis axis) {
    if (_image_data.Get() != nullptr) {
        cadsi_lib::volumes::VolumeImageTransformations::flipInplace(_image_data, axis);
        emit imageUpdated();
    }
}

cadsi_lib::volumes::VolumeImage* ImageObject::getData() {
    return _image_data;
}
