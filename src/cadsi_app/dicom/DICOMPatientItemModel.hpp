//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTITEMMODEL_HPP
#define CADSI_DICOMPATIENTITEMMODEL_HPP

#include <QAbstractItemModel>
#include <cadsi_lib/dicom/DicomPatient.hpp>

#include "CadsiLibDicomDeclareMetatype.hpp"

class DICOMPatientItemModel : public QAbstractItemModel {
public:
    /*!
     * \brief DICOMPatientItemModel describe a qt model containing patients data
     * PatientColumnRoles is a roles for pretty look usage in table views
     * PatientDataRoles is a roles for getting cadsi_lib::dicom::DicomSeries and DicomImages lists from DicomPatient
     */
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
        ALL_SERIES_FOR_PATIENT_ROLE
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    /*!
     * If index is valid and dont have internal id - this is patient index
     * If index is valid and have internal id - this is series list index
     * His internal id reference to patient row number
     */
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;

    void setPatients(const QList<cadsi_lib::dicom::DicomPatient>& patients);
    void pushBack(const cadsi_lib::dicom::DicomPatient& patient);

private:
    QList<cadsi_lib::dicom::DicomPatient> _patients;
};

#endif    //CADSI_DICOMPATIENTITEMMODEL_HPP
