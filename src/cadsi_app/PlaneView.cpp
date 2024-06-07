//
// Created by nyanbanan on 04.05.2024.
//

#include "PlaneView.hpp"

PlaneView::PlaneView(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    connect(_ui.sliceSlider, &QSlider::valueChanged, _ui.sliceSpinBox, &QSpinBox::setValue);
    connect(_ui.sliceSpinBox, &QSpinBox::valueChanged, _ui.sliceSlider, &QSlider::setValue);
}

void PlaneView::setPlane(DICOMPlaneViewer* plane_view) {
    if (_plane_view) {
        _ui.layout->removeWidget(_plane_view);
    }
    _plane_view = plane_view;
    _ui.layout->addWidget(_plane_view, 1);

    connect(_ui.sliceSlider, &QSlider::valueChanged, _plane_view, &DICOMPlaneViewer::setCurrentSlice);
    connect(_plane_view, &DICOMPlaneViewer::slicesNumChanged, this, &PlaneView::onSlicesNumChanged);
}

void PlaneView::onSlicesNumChanged(int min_slice_ind, int max_slice_ind) {
    _ui.sliceSlider->setMinimum(min_slice_ind);
    _ui.sliceSlider->setMaximum(max_slice_ind);
}
