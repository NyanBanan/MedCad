//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientTableModel.hpp"

DICOMPatientTableModel::DICOMPatientTableModel(QObject* parent) : DICOMModel(parent) {}

int DICOMPatientTableModel::rowCount(const QModelIndex& parent) const {
    return _dicom_data.isNull() ? 0 : (int)_dicom_data->patientNum();
}

int DICOMPatientTableModel::columnCount(const QModelIndex& parent) const {
    return LAST_ROLE - FIRST_ROLE - 1;
}

QVariant DICOMPatientTableModel::data(const QModelIndex& index, int role) const {
    if (index.isValid()) {
        if (role == Qt::DisplayRole) {
            auto& patient = _dicom_data->getPatient(index.row());
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
        return {};
        //КАЖДАЯ МОДЕЛЬ (ПАЦИЕНТ СЕРИЯ СНИМОК) НАСЛЕДНИКИ ЭТОЙ МОДЕЛИ СО СВОИМИ РОЛЯМИ И ПЕРЕГРУЗКАМИ ДАТЫ ИНДЕКСА И РОДИТЕЛЯ
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

QModelIndex DICOMPatientTableModel::index(int row, int column, const QModelIndex& parent) const {
    return hasIndex(row, column, parent) ? createIndex(row, column, nullptr) : QModelIndex();
}

QModelIndex DICOMPatientTableModel::parent(const QModelIndex& child) const {
    return {};
}

void DICOMPatientTableModel::handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                                    const QList<cadsi_lib::dicom::DicomPatient>& new_data) {
    beginResetModel();
    if (!old_data.isEmpty()) {
        beginRemoveRows({}, 0, (int)(old_data.size() - 1));
        endRemoveRows();
    }
    if (!new_data.isEmpty()) {
        beginInsertRows({}, 0, (int)(new_data.size() - 1));
        endInsertRows();
    }
    endResetModel();
}

Qt::ItemFlags DICOMPatientTableModel::flags(const QModelIndex& index) const {
    return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemNeverHasChildren;
}
