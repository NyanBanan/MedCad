//
// Created by nyanbanan on 04.05.2024.
//

#ifndef CADSI_PLANEVIEW_HPP
#define CADSI_PLANEVIEW_HPP

#include <QPointer>
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
#include <vtkImageMapToColors.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>
#include <vtkViewport.h>

#include "ImageObject.hpp"
#include "dicom/DICOMPlaneViewer.hpp"
#include "ui_files/ui_planeview.h"

class PlaneView : public QWidget {
public:
    enum Orientations {
        SAGITTAL = 0,
        CORONAL = 1,
        AXIAL = 2
    };

    PlaneView(QWidget* parent = nullptr);

    void setPlane(DICOMPlaneViewer* plane_view);

private:
    QPointer<DICOMPlaneViewer> _plane_view;

    Ui::PlaneView _ui;
};

#endif    //CADSI_PLANEVIEW_HPP
