//
// Created by nyanbanan on 14.04.2024.
//

#include "DICOMImageMetaDataTableModel.hpp"

int DICOMImageMetaDataTableModel::rowCount(const QModelIndex& parent) const {
    return (int)_objects.size();
}

int DICOMImageMetaDataTableModel::columnCount(const QModelIndex& parent) const {
    return LAST_ROLE - FIRST_ROLE - 1;
}

QVariant DICOMImageMetaDataTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.isValid()) {
            switch (index.column() + FIRST_ROLE + 1) {
                case Roles::TAG_ROLE: {
                    return _objects[index.row()].getTag();
                }
                case Roles::NAME_ROLE: {
                    return _objects[index.row()].getName();
                }
                case Roles::VALUE_ROLE: {
                    return _objects[index.row()].getVal();
                }
                case Roles::VR_ROLE: {
                    return _objects[index.row()].getVR();
                }
                default: {
                    return {};
                }
            }
        }
    }
    return {};
}

QVariant DICOMImageMetaDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QAbstractItemModel::headerData(section, orientation, role);
    }
    switch (section + FIRST_ROLE + 1) {
        case Roles::TAG_ROLE: {
            return "Тег";
        }
        case Roles::NAME_ROLE: {
            return "Атрибут";
        }
        case Roles::VALUE_ROLE: {
            return "Значение";
        }
        case Roles::VR_ROLE: {
            return "VR";
        }
        default: {
            return {};
        }
    }
}

void DICOMImageMetaDataTableModel::pushBack(DICOMImageMetaDataTableModelObject&& obj) {
    auto new_elem_pos = (int)_objects.size();
    beginInsertRows({}, new_elem_pos, new_elem_pos);
    _objects.push_back(obj);
    endInsertRows();
}
