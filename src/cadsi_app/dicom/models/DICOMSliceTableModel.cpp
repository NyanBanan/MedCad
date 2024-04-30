//
// Created by nyanbanan on 28.04.2024.
//

#include "DICOMSliceTableModel.hpp"

DICOMSliceTableModel::DICOMSliceTableModel(QObject* parent) : DICOMModel(parent) {}

int DICOMSliceTableModel::rowCount(const QModelIndex& parent) const {
    return (int)_slice_data.size();
}

int DICOMSliceTableModel::columnCount(const QModelIndex& parent) const {
    return LAST_ROLE - FIRST_ROLE - 1;
}

QVariant DICOMSliceTableModel::data(const QModelIndex& index, int role) const {
    switch (role) {
        case Qt::DisplayRole: {
            if (!index.isValid()) {
                return {};
            }
            auto& curr_meta = _slice_data[index.row()];
            switch (index.column() + FIRST_ROLE + 1) {
                case TAG_ROLE: {
                    return curr_meta.getTag();
                }
                case ATTRIBUTE_ROLE: {
                    return curr_meta.getName();
                }
                case VAL_ROLE: {
                    return curr_meta.getVal();
                }
                case VR_ROLE: {
                    return curr_meta.getVR();
                }
                default: {
                    return {};
                }
            }
        }
        case CURR_FILE_NAME_ROLE: {
            auto file_name =
                _dicom_data->getImage(_curr_patient_ind, _curr_series_ind, _curr_slice_ind).getImageFilePath();
            return file_name.isEmpty() ? "Путь к файлу" : file_name;
        }
        case NUM_OF_SLICES_ROLE: {
            return _dicom_data->getImagesNum(_curr_patient_ind, _curr_series_ind);
        }
        default: {
            return {};
        }
    }
}

QVariant DICOMSliceTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return {};
    }
    switch (section + FIRST_ROLE + 1) {
        case TAG_ROLE: {
            return "Тег";
        }
        case ATTRIBUTE_ROLE: {
            return "Атрибут";
        }
        case VAL_ROLE: {
            return "Значение";
        }
        case VR_ROLE: {
            return "VR";
        }
        default: {
            return {};
        }
    }
}

QModelIndex DICOMSliceTableModel::index(int row, int column, const QModelIndex& parent) const {
    return hasIndex(row, column, parent) ? createIndex(row, column, nullptr) : QModelIndex();
}

QModelIndex DICOMSliceTableModel::parent(const QModelIndex& child) const {
    return {};
}

void DICOMSliceTableModel::handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                                  const QList<cadsi_lib::dicom::DicomPatient>& new_data) {
    setPatientInd(-1);
}

void DICOMSliceTableModel::setPatientInd(int patient_ind) {
    if (_curr_patient_ind == patient_ind) {
        return;
    }
    _curr_patient_ind = patient_ind;
    setSeriesInd(-1);
}

void DICOMSliceTableModel::setSeriesInd(int series_ind) {
    if (_curr_series_ind == series_ind) {
        return;
    }
    _curr_series_ind = series_ind;
    if (_curr_series_ind < 0) {
        setSliceInd(-1);
    } else {
        setSliceInd(0);
    }
    emit currSeriesIndChanged(series_ind);
}

void DICOMSliceTableModel::setSliceInd(int slice_ind) {
    beginResetModel();
    auto old_slice_last_ind = (int)_slice_data.size() - 1;
    if (old_slice_last_ind >= 0) {
        beginRemoveRows({}, 0, old_slice_last_ind);
        _slice_data.clear();
        endRemoveRows();
    }
    _curr_slice_ind = slice_ind;
    auto new_slice_last_ind = (int)_dicom_data->getImagesNum(_curr_patient_ind, _curr_series_ind) - 1;
    if (new_slice_last_ind >= 0) {
        auto& series_meta = _dicom_data->getSeries(_curr_patient_ind, _curr_series_ind).getMetaCollection();
        auto& image_meta =
            _dicom_data->getImage(_curr_patient_ind, _curr_series_ind, _curr_slice_ind).getMetaCollection();

        auto new_meta_last_ind = (int)series_meta.size() + (int)image_meta.size() - 1;
        beginInsertRows({}, 0, new_meta_last_ind);

        std::ranges::for_each(series_meta, [this](auto series) {
            _slice_data.append(DICOMSliceMetaDataObject::fromDicomDataElement(series));
        });
        std::ranges::for_each(image_meta, [this](auto image) {
            _slice_data.append(DICOMSliceMetaDataObject::fromDicomDataElement(image));
        });

        std::ranges::sort(_slice_data, {}, &DICOMSliceMetaDataObject::getTag);

        endInsertRows();
    }
    endResetModel();
    emit currSliceIndChanged();
}

Qt::ItemFlags DICOMSliceTableModel::flags(const QModelIndex& index) const {
    return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemNeverHasChildren;
}
