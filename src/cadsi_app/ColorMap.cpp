//
// Created by nyanbanan on 06.05.2024.
//

#include "ColorMap.hpp"

ColorMap::ColorMap(QWidget* parent) {
    _ui.setupUi(this);

    connect(_ui.levelSpinBoxLevel, &QSpinBox::valueChanged, _ui.slider, &DensityWindowSliderWidget::setDensityCenter);
    connect(_ui.windowSpinBox, &QSpinBox::valueChanged, _ui.slider, &DensityWindowSliderWidget::setDensityWindowSize);

    connect(_ui.slider, &DensityWindowSliderWidget::windowValueChanged, _ui.windowSpinBox, &QSpinBox::setValue);
    connect(_ui.slider, &DensityWindowSliderWidget::centerDensityChanged, _ui.levelSpinBoxLevel, &QSpinBox::setValue);

    connect(_ui.slider, &DensityWindowSliderWidget::windowValueChanged, this, &ColorMap::windowValueChanged);
    connect(_ui.slider, &DensityWindowSliderWidget::centerDensityChanged, this, &ColorMap::centerDensityChanged);

    connect(this, &ColorMap::lutChanged, _ui.bar, &ScalarBarWidget::setLut);

    auto min_dens = -1000;
    auto max_dens = 1000;
    _ui.slider->setMaxMinDensity(max_dens, min_dens);
    _ui.windowSpinBox->setMinimum(min_dens);
    _ui.windowSpinBox->setMaximum(max_dens);
}

void ColorMap::setColorMapNames(QList<QString> color_map_names) {
    std::ranges::for_each(color_map_names, [this](auto name) {
        _ui.cmapComboBox->addItem(name);
    });
}

void ColorMap::on_cmapComboBox_currentTextChanged(const QString& text) {
    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto lut = global_color_maps_provider.toStrongRef()->getLUT(text);
        emit lutChanged(lut);
    } else {
        emit error("global color provider not initialized");
    }
}
