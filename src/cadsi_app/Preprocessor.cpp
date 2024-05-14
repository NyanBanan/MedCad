//
// Created by nyanbanan on 01.05.2024.
//

#include "Preprocessor.hpp"

Preprocessor::Preprocessor(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    connect(this, &Preprocessor::lutChanged, _ui.colormap, &ColorMap::lutChanged);
    connect(this, &Preprocessor::lutChanged, &_plane_viewer, &DICOMPlaneViewer::setLut);
    connect(_ui.imageOrientationComboBox,
            &QComboBox::currentIndexChanged,
            &_plane_viewer,
            &DICOMPlaneViewer::setOrientationFromInt);

    std::ranges::for_each(QList{"SAGITTAL", "CORONAL", "AXIAL"}, [this](auto orientation) {
        _ui.imageOrientationComboBox->addItem(orientation);
    });
    _ui.imageOrientationComboBox->setCurrentIndex(2);

    connect(_ui.colormap, &ColorMap::error, &_error_win, &ErrorMessageBox::showMessage);
    connect(_ui.colormap, &ColorMap::windowValueChanged, &_plane_viewer, &DICOMPlaneViewer::setWindowLevel);
    connect(_ui.colormap, &ColorMap::centerDensityChanged, &_plane_viewer, &DICOMPlaneViewer::setDensityLevel);

    connect(_ui.colorMapsComboBox, &QComboBox::currentTextChanged, _ui.colormap, &ColorMap::setCmapComboBoxCurrentText);

    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto names = global_color_maps_provider.toStrongRef()->colorMapsNames();
        setColorMapsNames(names);
    }

    _ui.splitter->setStretchFactor(0, 1);
    _ui.splitter->setStretchFactor(1, 0);

    _ui.planeview->setPlane(&_plane_viewer);

    connect(_ui.denoiseFactorSlider, &QSlider::valueChanged, _ui.denoiseFactorSpinBox, &QSpinBox::setValue);
    connect(_ui.denoiseFactorSpinBox, &QSpinBox::valueChanged, _ui.denoiseFactorSlider, &QSlider::setValue);

    connect(_ui.denoiseThresholdSlider, &QSlider::valueChanged, _ui.denoiseThresholdSpinBox, &QSpinBox::setValue);
    connect(_ui.denoiseThresholdSpinBox, &QSpinBox::valueChanged, _ui.denoiseThresholdSlider, &QSlider::setValue);
}

void Preprocessor::setColorMapsNames(const QList<QString>& names) {
    _ui.colorMapsComboBox->clear();
    std::ranges::for_each(names, [this](auto name) {
        _ui.colorMapsComboBox->addItem(name);
    });
    if (!names.isEmpty()) {
        on_colorMapsComboBox_currentTextChanged(names[0]);
    }
    _ui.colormap->setColorMapNames(names);
}

void Preprocessor::loadImage(vtkAlgorithmOutput* input) {
    _trans_pipe.setInputConnection(input);
    _plane_viewer.loadImage(_trans_pipe.getOutputConnection());
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

void Preprocessor::on_smoothSigmaDoubleSpinBox_valueChanged() {
    _ui.smoothApply->setEnabled(true);
}

void Preprocessor::on_smoothWindowDoubleSpinBox_valueChanged() {
    _ui.smoothApply->setEnabled(true);
}

void Preprocessor::on_smoothApply_pressed() {
    _ui.smoothApply->setEnabled(false);
    _trans_pipe.smooth(_ui.smoothSigmaDoubleSpinBox->value(), _ui.smoothWindowDoubleSpinBox->value());
}

void Preprocessor::on_denoiseFactorSlider_valueChanged() {
    _ui.denoiseApply->setEnabled(true);
}

void Preprocessor::on_denoiseFactorSpinBox_valueChanged() {
    _ui.denoiseApply->setEnabled(true);
}

void Preprocessor::on_denoiseThresholdSlider_valueChanged() {
    _ui.denoiseApply->setEnabled(true);
}

void Preprocessor::on_denoiseThresholdSpinBox_valueChanged() {
    _ui.denoiseApply->setEnabled(true);
}

void Preprocessor::on_denoiseApply_pressed() {
    _ui.denoiseApply->setEnabled(false);
    _trans_pipe.denoise(_ui.denoiseFactorSpinBox->value(), _ui.denoiseThresholdSpinBox->value());
}

void Preprocessor::on_enhancePushButton_pressed() {
    _trans_pipe.enhance();
}

void Preprocessor::on_flipXPushButton_pressed() {
    _trans_pipe.flip(PreprocessorTransformationsPipe::X);
}

void Preprocessor::on_flipYPushButton_pressed() {
    _trans_pipe.flip(PreprocessorTransformationsPipe::Y);
}

void Preprocessor::on_flipZPushButton_pressed() {
    _trans_pipe.flip(PreprocessorTransformationsPipe::Z);
}
