//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTTABLEMODEL_HPP
#define CADSI_DICOMPATIENTTABLEMODEL_HPP

#include <QAbstractTableModel>

#include "DICOMModel.hpp"

class DICOMPatientTableModel : public DICOMModel {
    Q_OBJECT
public:
    enum PatientColumnRoles {
        FIRST_ROLE = Qt::UserRole,    //required for column counting, dont use them
        NAME_ROLE,
        ID_ROLE,
        SEX_ROLE,
        BIRTHDATE_ROLE,
        COMMENTS_ROLE,
        NUM_ROLE,
        LAST_ROLE    //required for column counting, dont use them
    };

    DICOMPatientTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    void handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                const QList<cadsi_lib::dicom::DicomPatient>& new_data) override;
};

#endif    //CADSI_DICOMPATIENTTABLEMODEL_HPP
