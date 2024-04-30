//
// Created by nyanbanan on 28.04.2024.
//

#include "DICOMModel.hpp"

DICOMModel::DICOMModel(QObject* parent) : QAbstractItemModel(parent) {}

void DICOMModel::setDicomData(QSharedPointer<DICOMData> dicom_data) {
    _dicom_data = dicom_data;
    connect(_dicom_data.data(), &DICOMData::dataUpdated, this, &DICOMModel::handleDicomDataChanged);
}
