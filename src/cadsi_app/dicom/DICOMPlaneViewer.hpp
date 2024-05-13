//
// Created by nyanbanan on 13.05.2024.
//

#ifndef CADSI_DICOMPLANEVIEWER_HPP
#define CADSI_DICOMPLANEVIEWER_HPP

#include <QVTKOpenGLNativeWidget.h>
#include <cadsi_lib/colors/providers/GlobalColorsProvider.hpp>
#include <cadsi_lib/volumes/VolumeImage.hpp>
#include <vtkCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageData.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageProperty.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>
#include <vtkViewport.h>

class DICOMPlaneViewer : public QVTKOpenGLNativeWidget {
public:
    enum Orientations {
        SAGITTAL = 0,
        CORONAL = 1,
        AXIAL = 2
    };

    DICOMPlaneViewer(QWidget* parent = nullptr);

    void loadImage(vtkAlgorithmOutput* input);
    void setOrientation(DICOMPlaneViewer::Orientations orientation);
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
    vtkNew<vtkImageResliceMapper> _mapper;
    vtkNew<vtkImagePlaneWidget> _viewer;
    vtkNew<vtkImageSlice> _slice;
    vtkNew<vtkRenderer> _ren;
};

#endif    //CADSI_DICOMPLANEVIEWER_HPP
