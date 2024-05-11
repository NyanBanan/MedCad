//
// Created by nyanbanan on 04.05.2024.
//

#ifndef CADSI_PLANEVIEW_HPP
#define CADSI_PLANEVIEW_HPP

#include <QVTKOpenGLNativeWidget.h>
#include <cadsi_lib/colors/providers/GlobalColorsProvider.hpp>
#include <cadsi_lib/volumes/VolumeImage.hpp>
#include <vtkCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageData.h>
#include <vtkImagePlaneWidget.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>
#include <vtkViewport.h>

#include "ImageObject.hpp"
#include "ui_files/ui_planeview.h"

class PlaneView : public QVTKOpenGLNativeWidget {
public:
    enum Orientations {
        SAGITTAL,
        CORONAL,
        AXIAL
    };

    PlaneView(QWidget* parent = nullptr);

    void loadImage(vtkImageData* data);
    void setOrientation(PlaneView::Orientations orientation);
    void setDensityLevel(int level);
    void setWindowLevel(int window);
public slots:
    void setOrientationFromInt(int orientation);
    void setLut(vtkLookupTable* lut);
    void setCurrentSlice(int index);

private slots:
    void onImageLoaded();
    void onImageUpdated();

private:
    void updateOrientation();

    Orientations _orientation{CORONAL};
    vtkNew<vtkImagePlaneWidget> _viewer;
    vtkNew<vtkRenderer> _ren;

    ImageObject _image;

    Ui::PlaneView _ui;
};

#endif    //CADSI_PLANEVIEW_HPP
