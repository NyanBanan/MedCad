//
// Created by nyanbanan on 13.05.2024.
//

#include "DICOMPlaneViewer.hpp"

DICOMPlaneViewer::DICOMPlaneViewer(QWidget* parent) : QVTKOpenGLNativeWidget(parent) {
    setRenderWindow(vtkGenericOpenGLRenderWindow::New());
    setEnabled(false);
    interactor()->SetInteractorStyle(vtkInteractorStyleImage::New());
    renderWindow()->AddRenderer(_ren);

    _first_alg = _colorizer;

    _mapper->SetInputConnection(_colorizer->GetOutputPort());
    _slice->SetMapper(_mapper);
    _slice->SetPosition(0, 0, 0);
    _ren->AddViewProp(_slice);
}

void DICOMPlaneViewer::loadImage(vtkAlgorithmOutput* data) {
    _colorizer->SetInputConnection(data);

    onImageLoaded();
    emit slicesNumChanged(_mapper->GetSliceNumberMinValue(), _mapper->GetSliceNumberMaxValue());
}

void DICOMPlaneViewer::onImageUpdated() {
    renderWindow()->Render();
}

void DICOMPlaneViewer::onImageLoaded() {
    setEnabled(true);
}

void DICOMPlaneViewer::setOrientationFromInt(int orientation) {
    if (orientation < SAGITTAL || orientation > AXIAL) {
        return;
    }
    setOrientation((Orientations)orientation);
}

void DICOMPlaneViewer::setOrientation(DICOMPlaneViewer::Orientations new_orientation) {
    if (_first_alg->GetInput() != nullptr) {
        if (_orientation != new_orientation) {
            _mapper->SetOrientation(new_orientation);

            switch (new_orientation) {
                case SAGITTAL: {
                    _slice->SetOrientation(0, 90, 90);

                    break;
                }
                case CORONAL: {
                    _slice->SetOrientation(90, 0, 180);

                    break;
                }
                case AXIAL: {
                    _slice->SetOrientation(0, 0, 0);
                    break;
                }
            }
            _ren->ResetCamera();
            renderWindow()->Render();
            _orientation = new_orientation;
            emit slicesNumChanged(_mapper->GetSliceNumberMinValue(), _mapper->GetSliceNumberMaxValue());
        }
    }
}

void DICOMPlaneViewer::setLut(vtkLookupTable* lut) {
    _colorizer->SetLookupTable(lut);
    onImageUpdated();
}

void DICOMPlaneViewer::setDensityLevel(int level) {
    if (_first_alg->GetInput() != nullptr) {
        if (_colorizer->GetLevel() != level) {
            _colorizer->SetLevel(level);
            onImageUpdated();
        }
    }
}

void DICOMPlaneViewer::setWindowLevel(int window) {
    if (_first_alg->GetInput() != nullptr) {
        if (_colorizer->GetWindow() != window) {
            _colorizer->SetWindow(window);
            onImageUpdated();
        }
    }
}

void DICOMPlaneViewer::setCurrentSlice(int index) {
    if (_first_alg->GetInput() != nullptr) {
        _mapper->SetSliceNumber(index);
        onImageUpdated();
    }
}
