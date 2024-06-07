//
// Created by nyanbanan on 09.04.2024.
//

#include "SliceMetadata.hpp"

SliceMetadata::SliceMetadata(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    connect(_ui.currSliceSlider, &QSlider::valueChanged, _ui.currSliceSpinBox, &QSpinBox::setValue);
    connect(_ui.currSliceSpinBox, &QSpinBox::valueChanged, _ui.currSliceSlider, &QSlider::setValue);

    _ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void SliceMetadata::on_currSliceSlider_valueChanged(int val) {
    setCurrSlice(val);
}

void SliceMetadata::setCurrSlice(int id) {
    auto model = dynamic_cast<DICOMSliceTableModel*>(_ui.tableView->model());
    if (model == nullptr) {
        return;
    }
    model->setSliceInd(id);
}

void SliceMetadata::setModel(DICOMSliceTableModel* model) {
    _ui.tableView->setModel(model);
    connect(model, &DICOMSliceTableModel::currSliceIndChanged, this, &SliceMetadata::onCurrSliceIndChanged);
    connect(model, &DICOMSliceTableModel::currSeriesIndChanged, this, &SliceMetadata::onCurrSeriesIndChanged);
}

void SliceMetadata::onCurrSliceIndChanged() {
    auto model = _ui.tableView->model();
    if (model == nullptr) {
        return;
    }
    _ui.filePathLabel->setText(model->data({}, DICOMSliceTableModel::CURR_FILE_NAME_ROLE).toString());
}

void SliceMetadata::onCurrSeriesIndChanged(int new_ind) {
    int slices_last_index;
    if(new_ind < 0){
        slices_last_index = 0;
    }
    else {
        slices_last_index = _ui.tableView->model()->data({}, DICOMSliceTableModel::NUM_OF_SLICES_ROLE).toInt() - 1;
    }
    _ui.currSliceSlider->setMaximum(slices_last_index);
    _ui.currSliceSpinBox->setMaximum(slices_last_index);
    _ui.tableView->resizeColumnsToContents();
}
