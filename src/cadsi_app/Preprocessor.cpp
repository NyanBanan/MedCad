//
// Created by nyanbanan on 01.05.2024.
//

#include "Preprocessor.hpp"

#include <vtkDICOMCTRectifier.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMReader.h>

Preprocessor::Preprocessor(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    connect(_ui.colormap, &ColorMap::error, &_error_win, &ErrorMessageBox::showMessage);

    connect(this, &Preprocessor::lutChanged, _ui.colormap, &ColorMap::lutChanged);
    connect(this, &Preprocessor::lutChanged, &_plane_viewer, &DICOMPlaneViewer::setLut);
    connect(_ui.imageOrientationComboBox,
            &QComboBox::currentIndexChanged,
            &_plane_viewer,
            &DICOMPlaneViewer::setOrientationFromInt);

    std::ranges::for_each(QList{"SAGITTAL", "CORONAL", "AXIAL"}, [this](auto orientation) {
        _ui.imageOrientationComboBox->addItem(orientation);
    });
    _ui.imageOrientationComboBox->setCurrentIndex(0);

    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto names = global_color_maps_provider.toStrongRef()->colorMapsNames();
        setColorMapsNames(names);
    }

    _ui.splitter->setStretchFactor(0, 1);
    _ui.splitter->setStretchFactor(1, 0);

    _ui.planeview->setPlane(&_plane_viewer);
}

void Preprocessor::on_colorMapsComboBox_currentTextChanged(const QString& text) {
    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto lut = global_color_maps_provider.toStrongRef()->getLUT(text);
        emit lutChanged(lut);
    } else {
        _error_win.showMessage("global color provider not initialized");
    }
}

void Preprocessor::setColorMapsNames(const QList<QString>& names) {
    _ui.colorMapsComboBox->clear();
    std::ranges::for_each(names, [this](auto name) {
        _ui.colorMapsComboBox->addItem(name);
    });
    _ui.colormap->setColorMapNames(names);
}

void Preprocessor::loadImage(vtkAlgorithmOutput* input) {
    _plane_viewer.loadImage(input);
}
