//
// Created by nyanbanan on 28.04.2024.
//

#ifndef CADSI_DICOMSERIESLISTMODEL_HPP
#define CADSI_DICOMSERIESLISTMODEL_HPP

#include <QAbstractListModel>
#include <QIcon>

#include "DICOMModel.hpp"

class DICOMSeriesListModel : public DICOMModel {
    Q_OBJECT
public:
    DICOMSeriesListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    void setPatientInd(int patient_ind);
    [[nodiscard]] int getCurrPatientInd() const;

private:
    void handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                const QList<cadsi_lib::dicom::DicomPatient>& new_data) override;

    int _curr_patient_ind{-1};
};

#endif    //CADSI_DICOMSERIESLISTMODEL_HPP
