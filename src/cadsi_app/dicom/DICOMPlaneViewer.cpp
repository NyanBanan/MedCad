//
// Created by nyanbanan on 13.05.2024.
//

#include "DICOMPlaneViewer.hpp"

DICOMPlaneViewer::DICOMPlaneViewer(QWidget* parent) : QVTKOpenGLNativeWidget(parent) {
    setRenderWindow(vtkGenericOpenGLRenderWindow::New());
    setEnabled(false);
    interactor()->SetInteractorStyle(vtkInteractorStyleImage::New());
    renderWindow()->AddRenderer(_ren);
    _viewer->SetInteractor(interactor());
    auto global_color_provider = cadsi_lib::colors::providers::GlobalColorsProvider::getGlobalColorsProvider();
    if (global_color_provider) {
        _viewer->GetTextProperty()->SetColor(global_color_provider.toStrongRef()->color("red").GetData());
    }
    _viewer->DisplayTextOn();
}

void DICOMPlaneViewer::loadImage(vtkAlgorithmOutput* data) {
    _viewer->SetInputConnection(data);

    onImageLoaded();
}

void DICOMPlaneViewer::onImageUpdated() {
    renderWindow()->Render();
}

void DICOMPlaneViewer::onImageLoaded() {
    _viewer->SetPlaneOrientation(_orientation);
    _viewer->SetRestrictPlaneToVolume(true);
    _viewer->SetResliceInterpolateToNearestNeighbour();
    _viewer->On();

    /*    _ren->GetActiveCamera()->SetParallelScale(data->GetDimensions()[0] / 5.0);*/

    updateOrientation();

    setEnabled(true);
}

void DICOMPlaneViewer::setOrientationFromInt(int orientation) {
    if (orientation < SAGITTAL || orientation > AXIAL) {
        return;
    }
    setOrientation((Orientations)orientation);
}

void DICOMPlaneViewer::setOrientation(DICOMPlaneViewer::Orientations orientation) {
    if (_viewer->GetInput() != nullptr) {
        _viewer->SetPlaneOrientation(_orientation);
        updateOrientation();
    }
}

void DICOMPlaneViewer::setLut(vtkLookupTable* lut) {
    if (_viewer->GetInput() != nullptr) {
        _viewer->SetLookupTable(lut);
        onImageUpdated();
    }
}

void DICOMPlaneViewer::setDensityLevel(int level) {
    if (_viewer->GetInput() != nullptr) {
        if (_viewer->GetLevel() != level) {
            _viewer->SetWindowLevel(_viewer->GetWindow(), level);
            onImageUpdated();
        }
    }
}

void DICOMPlaneViewer::setWindowLevel(int window) {
    if (_viewer->GetInput() != nullptr) {
        if (_viewer->GetWindow() != window) {
            _viewer->SetWindowLevel(window, _viewer->GetLevel());
            onImageUpdated();
        }
    }
}

void DICOMPlaneViewer::setCurrentSlice(int index) {
    if (_viewer->GetInput() != nullptr) {
        _viewer->SetSliceIndex(index);
        auto camera = _ren->GetActiveCamera();

        onImageUpdated();
    }
}

void DICOMPlaneViewer::updateOrientation() {
    _viewer->SetPlaneOrientation(_orientation);
    double center[3];
    _viewer->GetCenter(center);

    auto camera = _ren->GetActiveCamera();
    camera->SetFocalPoint(center);
    camera->SetViewUp(center);
    camera->SetViewUp(0, 0, -1);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetPosition(0, 1000, 0);


//    double camera_pos[3];
//    memcpy(camera_pos, center, sizeof(center));
//    switch (_orientation) {
//        case SAGITTAL: {
//            camera_pos[0] += 400;
//            camera->SetRoll(270);
//
//            break;
//        }
//        case AXIAL: {
//            camera_pos[2] -= 400;
//            camera->SetRoll(180);
//
//            break;
//        }
//        case CORONAL: {
//            camera_pos[1] -= 400;
//            camera->SetRoll(0);
//            break;
//        }
//    }
    camera->ComputeViewPlaneNormal();
//    camera->Azimuth(30.0);
//    camera->Elevation(30.0);
    camera->ParallelProjectionOn();

    _ren->ResetCamera();
    renderWindow()->Render();
}
