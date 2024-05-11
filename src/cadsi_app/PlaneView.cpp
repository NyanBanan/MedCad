//
// Created by nyanbanan on 04.05.2024.
//

#include "PlaneView.hpp"

PlaneView::PlaneView(QWidget* parent) : QVTKOpenGLNativeWidget(parent) {
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

    connect(&_image, &ImageObject::imageLoaded, this, &PlaneView::onImageLoaded);
    connect(&_image, &ImageObject::imageUpdated, this, &PlaneView::onImageUpdated);
}

void PlaneView::loadImage(vtkImageData* data) {
    _image.loadImage(data);
}

void PlaneView::onImageUpdated() {
    renderWindow()->Render();
}

void PlaneView::onImageLoaded() {
    auto data = _image.getData();

    _viewer->SetInputData(data);
    _viewer->SetPlaneOrientation(_orientation);
    _viewer->SetRestrictPlaneToVolume(true);
    _viewer->SetResliceInterpolateToNearestNeighbour();
    _viewer->On();

    _ren->GetActiveCamera()->SetParallelScale(data->GetDimensions()[0] / 5.0);

    updateOrientation();

    setEnabled(true);
}

void PlaneView::setOrientationFromInt(int orientation) {
    if (orientation < SAGITTAL || orientation > AXIAL) {
        return;
    }
    setOrientation((Orientations)orientation);
}

void PlaneView::setOrientation(PlaneView::Orientations orientation) {
    _orientation = orientation;
    renderWindow()->Render();
}

void PlaneView::setLut(vtkLookupTable* lut) {
    _viewer->SetLookupTable(lut);
    update();
}

void PlaneView::setDensityLevel(int level) {
    if (_viewer->GetLevel() != level) {
        _viewer->SetWindowLevel(_viewer->GetWindow(), level);
        update();
    }
}

void PlaneView::setWindowLevel(int window) {
    if (_viewer->GetWindow() != window) {
        _viewer->SetWindowLevel(window, _viewer->GetLevel());
        update();
    }
}

void PlaneView::setCurrentSlice(int index) {
    _viewer->SetSliceIndex(index);
    update();
}

void PlaneView::updateOrientation() {
    double center[3];
    _viewer->GetCenter(center);

    auto camera = _ren->GetActiveCamera();
    camera->SetFocalPoint(center);
    camera->SetViewUp(center);
    double camera_pos[3];
    memcpy(camera_pos, center, sizeof (center));
    switch (_orientation) {
        case AXIAL: {
            camera_pos[2] -= 400;
//            camera->SetRoll(180);

            break;
        }
        case CORONAL: {
            camera_pos[1] -= 400;
//            camera->SetRoll(0);
            break;
        }
        case SAGITTAL: {
            camera_pos[0] += 400;
//            camera->SetRoll(270);
            break;
        }
    }
    camera->SetPosition(camera_pos);
    camera->ComputeViewPlaneNormal();
    camera->ParallelProjectionOn();

    _ren->ResetCamera();
    renderWindow()->Render();
}
