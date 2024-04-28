//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientItemModel.hpp"

int DICOMPatientItemModel::rowCount(const QModelIndex& parent) const {
    return (int)_patients.size();
}

int DICOMPatientItemModel::columnCount(const QModelIndex& parent) const {
    return LAST_ROLE - FIRST_ROLE - 1;
}

QVariant DICOMPatientItemModel::data(const QModelIndex& index, int role) const {
    if (index.isValid()) {
        switch (role) {
            case Qt::DisplayRole: {
                auto patient = _patients[index.row()];
                switch (index.column() + FIRST_ROLE + 1) {
                    case PatientColumnRoles::NAME_ROLE: {
                        return patient.getName();
                    }
                    case PatientColumnRoles::ID_ROLE: {
                        return patient.getId();
                    }
                    case PatientColumnRoles::SEX_ROLE: {
                        return patient.getSex();
                    }
                    case PatientColumnRoles::BIRTHDATE_ROLE: {
                        return patient.getBirthDateBySlashString();
                    }
                    case PatientColumnRoles::COMMENTS_ROLE: {
                        return patient.getComments();
                    }
                    case PatientColumnRoles::NUM_ROLE: {
                        return patient.numOfImages();
                    }
                    default: {
                        return {};
                    }
                }
            }
                //КАЖДАЯ МОДЕЛЬ (ПАЦИЕНТ СЕРИЯ СНИМОК) НАСЛЕДНИКИ ЭТОЙ МОДЕЛИ СО СВОИМИ РОЛЯМИ И ПЕРЕГРУЗКАМИ ДАТЫ ИНДЕКСА И РОДИТЕЛЯ 
            case PatientDataRoles::ALL_SERIES_FOR_PATIENT_ROLE: {
                return QVariant::fromValue(_patients[index.row()].getSeries());
            }
            case PatientDataRoles::SERIES_ROLE: {
                auto series_index = index;
                auto patient_id = (int)series_index.internalId();
                auto patient_index = this->index(patient_id, 0);
                if (!patient_index.isValid()) {
                    return {};
                }
                auto series_data = data(patient_index, ALL_SERIES_FOR_PATIENT_ROLE).value<QList<cadsi_lib::dicom::DicomSeries>>();
                auto slices_data = series_data[series_index.row()].getImages();
                return QVariant::fromValue(slices_data);
            }
            default: {
                return {};
            }
        }
    }
    return {};
}

QVariant DICOMPatientItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QAbstractItemModel::headerData(section, orientation, role);
    }
    switch (section + FIRST_ROLE + 1) {
        case PatientColumnRoles::NAME_ROLE: {
            return "Имя";
        }
        case PatientColumnRoles::ID_ROLE: {
            return "ID";
        }
        case PatientColumnRoles::SEX_ROLE: {
            return "Пол";
        }
        case PatientColumnRoles::BIRTHDATE_ROLE: {
            return "ДР";
        }
        case PatientColumnRoles::COMMENTS_ROLE: {
            return "Комментарии";
        }
        case PatientColumnRoles::NUM_ROLE: {
            return "Кол-во";
        }
        default: {
            return {};
        }
    }
}

void DICOMPatientItemModel::setPatients(const QList<cadsi_lib::dicom::DicomPatient>& patients) {
    beginResetModel();
    if (!_patients.isEmpty()) {
        beginRemoveRows({}, 0, (int)_patients.size() - 1);
        _patients.clear();
        endRemoveRows();
    }
    if (!patients.isEmpty()) {
        beginInsertRows({}, 0, (int)patients.size() - 1);
        _patients = patients;
        endInsertRows();
    }
    endResetModel();
}

void DICOMPatientItemModel::pushBack(const cadsi_lib::dicom::DicomPatient& patient) {
    auto new_elem_pos = (int)_patients.size();
    beginInsertRows({}, new_elem_pos, new_elem_pos);
    _patients.append(patient);
    endInsertRows();
}

QModelIndex DICOMPatientItemModel::index(int row, int column, const QModelIndex& parent) const {
    return hasIndex(row, column, parent) ? createIndex(row, column, parent.row()) : QModelIndex();
}

QModelIndex DICOMPatientItemModel::parent(const QModelIndex& child) const {
    if (!child.isValid()) {
        return {};
    }
    auto parent_id = (int)child.internalId();
    auto parent_index = index(parent_id, 0);
    if (!parent_index.isValid()) {
        return {};
    }
    return parent_index;
}
