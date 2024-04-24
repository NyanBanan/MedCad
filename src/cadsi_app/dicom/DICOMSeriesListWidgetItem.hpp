//
// Created by nyanbanan on 24.04.2024.
//

#ifndef CADSI_DICOMSERIESLISTWIDGETITEM_HPP
#define CADSI_DICOMSERIESLISTWIDGETITEM_HPP

#include <QListWidgetItem>
#include <cadsi_lib/OperationStatus.hpp>
#include <cadsi_lib/dicom/DicomSeries.hpp>

class DICOMSeriesListWidgetItem : public QListWidgetItem {
public:
    enum Roles {
        DICOM_SERIES_LIST_WIDGET_ITEM = Qt::UserRole,
        MODEL_INDEX
    };

    enum ErrorCodes {
        WRONG_INDEX_FORMAT
    };

    DICOMSeriesListWidgetItem(const cadsi_lib::dicom::DicomSeries& series, QListWidget* parent = nullptr);
    void setModelIndex(const QModelIndex& index);
    void setModelIndex(QModelIndex&& index);
};

#endif    //CADSI_DICOMSERIESLISTWIDGETITEM_HPP
