//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientMetaDataTableModel.hpp"

    int DICOMPatientMetaDataTableModel::rowCount(const QModelIndex& parent) const {
        return (int)_objects.size();
    }
    
    int DICOMPatientMetaDataTableModel::columnCount(const QModelIndex& parent) const {
        return LAST_ROLE - FIRST_ROLE - 1;
    }

    QVariant DICOMPatientMetaDataTableModel::data(const QModelIndex& index, int role) const {
        if (role == Qt::DisplayRole) {
            if (index.isValid()) {
                auto patient = _objects[index.row()].getPatient();
                switch (index.column() + FIRST_ROLE + 1) {
                    case Roles::NAME_ROLE: {
                        return patient.getName();
                    }
                    case Roles::ID_ROLE: {
                        return patient.getId();
                    }
                    case Roles::SEX_ROLE: {
                        return patient.getSex();
                    }
                    case Roles::BIRTHDATE_ROLE: {
                        return patient.getBirthDate();
                    }
                    case Roles::COMMENTS_ROLE: {
                        return patient.getComments();
                    }
                    case Roles::NUM_ROLE: {
                        return patient.numOfImages();
                    }
                    default: {
                        return {};
                    }
                }
            }
        }
        return {};
    }

    QVariant DICOMPatientMetaDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
            return QAbstractItemModel::headerData(section, orientation, role);
        }
        switch (section + FIRST_ROLE + 1) {
            case Roles::NAME_ROLE: {
                return "Имя";
            }
            case Roles::ID_ROLE: {
                return "ID";
            }
            case Roles::SEX_ROLE: {
                return "Пол";
            }
            case Roles::BIRTHDATE_ROLE: {
                return "ДР";
            }
            case Roles::COMMENTS_ROLE: {
                return "Комментарии";
            }
            case Roles::NUM_ROLE: {
                return "Кол-во";
            }
            default: {
                return {};
            }
        }
    }

    void DICOMPatientMetaDataTableModel::pushBack(const DICOMPatientMetaDataTableModelObject& obj) {
        auto new_elem_pos = (int)_objects.size();
        beginInsertRows({}, new_elem_pos, new_elem_pos);
        _objects.push_back(obj);
        endInsertRows();
    }
