//
// Created by nyanbanan on 28.04.2024.
//

#ifndef CADSI_DICOMMODEL_HPP
#define CADSI_DICOMMODEL_HPP

#include <QAbstractItemModel>
#include <utility>

#include "DICOMData.hpp"

class DICOMModel : public QAbstractItemModel {
    Q_OBJECT
public:
    DICOMModel(QObject* parent = nullptr);

    void setDicomData(QSharedPointer<DICOMData> dicom_data);

protected:
    QSharedPointer<DICOMData> _dicom_data{nullptr};
private slots:
    virtual void handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                        const QList<cadsi_lib::dicom::DicomPatient>& new_data) = 0;
};

#endif    //CADSI_DICOMMODEL_HPP
