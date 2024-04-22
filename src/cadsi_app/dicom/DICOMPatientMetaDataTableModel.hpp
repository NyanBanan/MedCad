//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTMETADATATABLEMODEL_HPP
#define CADSI_DICOMPATIENTMETADATATABLEMODEL_HPP

#include <QAbstractTableModel>

#include "DICOMPatientMetaDataTableModelObject.hpp"


    class DICOMPatientMetaDataTableModel : public QAbstractTableModel{
    public:
        enum Roles {
            FIRST_ROLE = Qt::UserRole,    //required for column counting, dont use them
            NAME_ROLE,
            ID_ROLE,
            SEX_ROLE,
            BIRTHDATE_ROLE,
            COMMENTS_ROLE,
            NUM_ROLE,
            LAST_ROLE    //required for column counting, dont use them
        };

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        void pushBack(const DICOMPatientMetaDataTableModelObject& obj);

    private:
        QList<DICOMPatientMetaDataTableModelObject> _objects;
    };

#endif    //CADSI_DICOMPATIENTMETADATATABLEMODEL_HPP
