//
// Created by nyanbanan on 28.04.2024.
//

#include "DICOMSeriesListModel.hpp"

DICOMSeriesListModel::DICOMSeriesListModel(QObject* parent) : DICOMModel(parent) {}

int DICOMSeriesListModel::rowCount(const QModelIndex& parent) const {
    return _dicom_data.isNull() ? 0 : (int)_dicom_data->getSeriesNum(_curr_patient_ind);
}

int DICOMSeriesListModel::columnCount(const QModelIndex& parent) const {
    return 1;
}

QVariant DICOMSeriesListModel::data(const QModelIndex& index, int role) const {
    if (index.isValid()) {
        auto& series = _dicom_data->getSeries(_curr_patient_ind, index.row());
        switch (role) {
            case Qt::DisplayRole: {
                return series.getUid();
            }
            case Qt::DecorationRole: {
                QIcon icon;
                auto preview = series.getPreview();
                if (preview.isNull()) {
                    icon.addPixmap(QPixmap(":/icons/photo.jpg"), QIcon::Normal, QIcon::Off);
                } else {
                    auto pix = QPixmap::fromImage(preview);
                    icon.addPixmap(pix, QIcon::Normal, QIcon::Off);
                }
                return icon;
            }
            case Qt::ToolTipRole: {
                return QString("<b>Модальность:</b> %1<br>"
                               "<b>Дата:</b> %2<br>"
                               "<b>Время:</b> %3<br>"
                               "<b>Учреждение:</b> %4<br>"
                               "<b>Комментарии:</b> %5<br>"
                               "<b>Кол-во снимков:</b> %6<br>")
                    .arg(series.getModality(),
                         series.getDate().toString("yyyy-MM-dd"),
                         series.getTime().toString("hh:mm:ss"),
                         series.getInstitutionName(),
                         series.getDescription())
                    .arg(series.numOfImages());
            }
            default: {
                return {};
            }
        }
    } else {
        return {};
    }
}

QModelIndex DICOMSeriesListModel::index(int row, int column, const QModelIndex& parent) const {
    return hasIndex(row, column, parent) ? createIndex(row, column, nullptr) : QModelIndex();
}

QModelIndex DICOMSeriesListModel::parent(const QModelIndex& child) const {
    return {};
}

void DICOMSeriesListModel::setPatientInd(int patient_ind) {
    if (patient_ind == _curr_patient_ind) {
        return;
    }
    auto old_series_last_ind = (int)_dicom_data->getSeriesNum(_curr_patient_ind) - 1;
    if (old_series_last_ind >= 0) {
        beginRemoveRows({}, 0, old_series_last_ind);
        endRemoveRows();
    }

    _curr_patient_ind = patient_ind;
    auto new_series_last_ind = (int)_dicom_data->getSeriesNum(_curr_patient_ind) - 1;
    if (new_series_last_ind >= 0) {
        beginInsertRows({}, 0, new_series_last_ind);
        endInsertRows();
    }
}

int DICOMSeriesListModel::getCurrPatientInd() const {
    return _curr_patient_ind;
}

void DICOMSeriesListModel::handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                                  const QList<cadsi_lib::dicom::DicomPatient>& new_data) {
    beginResetModel();
    setPatientInd(-1);
    endResetModel();
}
