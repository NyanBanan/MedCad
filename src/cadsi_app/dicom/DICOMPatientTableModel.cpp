//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientTableModel.hpp"

int DICOMPatientTableModel::rowCount(const QModelIndex& parent) const {
    return (int)_patients.size();
}

int DICOMPatientTableModel::columnCount(const QModelIndex& parent) const {
    return LAST_ROLE - FIRST_ROLE - 1;
}

QVariant DICOMPatientTableModel::data(const QModelIndex& index, int role) const {
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
            case PatientDataRoles::SERIES_ROLE: {
                return QVariant::fromValue(_patients[index.row()].getSeries());
            }
            case PatientDataRoles::SLICES_ROLE: {
                auto series_index = index;
                auto patient_index_ptr = static_cast<QModelIndex*>(series_index.internalPointer());
                if (patient_index_ptr == nullptr) {
                    return {};
                }
                auto patient_index = *patient_index_ptr;
                if (!patient_index.isValid()) {
                    return {};
                }
                auto series_data = data(patient_index, SERIES_ROLE).value<QList<cadsi_lib::dicom::DicomSeries>>();
                auto slices_data = series_data[series_index.row()].getImages();
                return QVariant::fromValue(slices_data);
            }
        }
    }
    return {};
}

QVariant DICOMPatientTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void DICOMPatientTableModel::setPatients(const QList<cadsi_lib::dicom::DicomPatient>& patients) {
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
}

void DICOMPatientTableModel::pushBack(const cadsi_lib::dicom::DicomPatient& patient) {
    auto new_elem_pos = (int)_patients.size();
    beginInsertRows({}, new_elem_pos, new_elem_pos);
    _patients.append(patient);
    endInsertRows();
}

QModelIndex DICOMPatientTableModel::index(int row, int column, const QModelIndex& parent) const {
    return hasIndex(row, column, parent) ? createIndex(row, column, &parent) : QModelIndex();
}

QModelIndex DICOMPatientTableModel::parent(const QModelIndex& child) const {
    if (!child.isValid()) {
        return {};
    }
    auto parent_ptr = static_cast<QModelIndex*>(child.internalPointer());
    if (parent_ptr == nullptr) {
        return {};
    }
    auto parent = *parent_ptr;
    if (!parent.isValid()) {
        return {};
    }
    return parent;
}
