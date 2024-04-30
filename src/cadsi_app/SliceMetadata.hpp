//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_SLICEMETADATA_HPP
#define CADSI_SLICEMETADATA_HPP

#include <QWidget>

#include "dicom/models/DICOMSliceTableModel.hpp"
#include "ui_files/ui_slicemetadata.h"

class SliceMetadata : public QWidget {
    Q_OBJECT
public:
    SliceMetadata(QWidget* parent);
public slots:
    void onCurrSliceIndChanged();
    void onCurrSeriesIndChanged(int new_ind);
    void setModel(DICOMSliceTableModel* model);
    void setCurrSlice(int id);

    void on_currSliceSlider_valueChanged(int val);
//TODO: Possibly lags when resizing, look in release build and think what you can do
private:
    Ui::SliceMetadata _ui;
};

#endif    //CADSI_SLICEMETADATA_HPP
