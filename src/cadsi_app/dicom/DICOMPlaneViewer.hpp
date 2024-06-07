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
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageProperty.h>
#include <vtkImageResliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageViewer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkLookupTable.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkViewport.h>

class DICOMPlaneViewer : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    enum Orientation {
        SAGITTAL = 0,
        CORONAL = 1,
        AXIAL = 2
    };

    DICOMPlaneViewer(QWidget* parent = nullptr);

    void loadImage(vtkAlgorithmOutput* input);
    void setOrientation(DICOMPlaneViewer::Orientation new_orientation);
signals:
    void slicesNumChanged(int min_slice_ind, int max_slice_ind);
public slots:
    void setOrientationFromInt(int orientation);
    void setLut(vtkLookupTable* lut);
    void setCurrentSlice(int index);
    //TODO: Lagging when density slider slide. Test in release, if problem remain, reduce number of Render() calls or signals emit
    void setDensityLevel(int level);
    void setWindowLevel(int window);

private slots:
    void onImageLoaded();
    void onImageUpdated();

private:
    vtkImageAlgorithm* _first_alg;

    Orientation _orientation{AXIAL};
    vtkNew<vtkImageSliceMapper> _mapper;
    vtkNew<vtkImageSlice> _slice;
    vtkNew<vtkImageMapToWindowLevelColors> _colorizer;
    vtkNew<vtkRenderer> _ren;
};

#endif    //CADSI_DICOMPLANEVIEWER_HPP
