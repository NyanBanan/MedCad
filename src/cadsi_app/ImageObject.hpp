//
// Created by nyanbanan on 04.05.2024.
//

#ifndef CADSI_IMAGEOBJECT_HPP
#define CADSI_IMAGEOBJECT_HPP

#include <QObject>
#include <cadsi_lib/volumes/VolumeImage.hpp>
#include <cadsi_lib/volumes/VolumeImageTransformations.hpp>

class ImageObject : public QObject {
    Q_OBJECT
public:
    void loadImage(vtkImageData* image_data);
    void setSmooth(double sigma, double r);
    void setDenoise(double factor, double threshold);
    void setEnhance();
    void flipImage(cadsi_lib::volumes::VolumeImageTransformations::FlipAxis axis);

    cadsi_lib::volumes::VolumeImage* getData();

signals:
    void imageLoaded();
    void imageUpdated();

private:
    vtkSmartPointer<cadsi_lib::volumes::VolumeImage> _image_data{nullptr};
};

#endif    //CADSI_IMAGEOBJECT_HPP
