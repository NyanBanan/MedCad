//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTTABLEMODEL_HPP
#define CADSI_DICOMPATIENTTABLEMODEL_HPP

#include <QAbstractItemModel>
#include <cadsi_lib/dicom/DicomPatient.hpp>

#include "CadsiLibDicomDeclareMetatype.hpp"

class DICOMPatientTableModel : public QAbstractItemModel {
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

    enum PatientDataRoles {
        SERIES_ROLE = LAST_ROLE + 1,
        SLICES_ROLE
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    void setPatients(const QList<cadsi_lib::dicom::DicomPatient>& patients);
    void pushBack(const cadsi_lib::dicom::DicomPatient& patient);

private:
    QList<cadsi_lib::dicom::DicomPatient> _patients;
};

#endif    //CADSI_DICOMPATIENTTABLEMODEL_HPP
