//
// Created by nyanbanan on 24.04.2024.
//

#include "DICOMSeriesListWidgetItem.hpp"

DICOMSeriesListWidgetItem::DICOMSeriesListWidgetItem(const cadsi_lib::dicom::DicomSeries& series, QListWidget* parent)
    : QListWidgetItem(parent, DICOM_SERIES_LIST_WIDGET_ITEM) {
    setText(series.getDescription());
    QIcon icon;
    auto preview = series.getPreview();
    if (preview.isNull()) {
        icon.addPixmap(QPixmap(":/icons/photo.jpg"), QIcon::Normal, QIcon::Off);
    } else {
        auto pix = QPixmap::fromImage(preview);
        icon.addPixmap(pix, QIcon::Normal, QIcon::Off);
    }
    setIcon(icon);
    setToolTip(QString("<b>Модальность:</b> %1<br>"
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
                   .arg(series.numOfImages()));
}

void DICOMSeriesListWidgetItem::setModelIndex(const QModelIndex& index) {
    setData(MODEL_INDEX, index);
}

void DICOMSeriesListWidgetItem::setModelIndex(QModelIndex&& index) {
    setData(MODEL_INDEX, index);
}
