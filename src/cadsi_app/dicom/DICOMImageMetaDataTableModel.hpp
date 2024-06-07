//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMIMAGEMETADATATABLEMODEL_HPP
#define CADSI_DICOMIMAGEMETADATATABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>

#include "DICOMSliceMetaDataObject.hpp"

class DICOMImageMetaDataTableModel : public QAbstractTableModel {
    public:
        enum Roles {
            FIRST_ROLE = Qt::UserRole,    //required for column counting, dont use them
            TAG_ROLE,
            NAME_ROLE,
            VALUE_ROLE,
            VR_ROLE,
            LAST_ROLE    //required for column counting, dont use them
        };

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        void pushBack(DICOMSliceMetaDataObject&& obj);

    private:
        QList<DICOMSliceMetaDataObject> _objects;
    };

#endif    //CADSI_DICOMIMAGEMETADATATABLEMODEL_HPP
