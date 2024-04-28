//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_SLICEMETADATA_HPP
#define CADSI_SLICEMETADATA_HPP

#include <QWidget>
#include <cadsi_lib/dicom/DicomSeries.hpp>

#include "dicom/DICOMImageMetaDataTableModelObject.hpp"
#include "ui_files/ui_slicemetadata.h"

class SliceMetadata : public QWidget {
    Q_OBJECT
public:
    SliceMetadata(QWidget* parent);
public slots:
    void setData(const cadsi_lib::dicom::DicomSeries& series, const QList<cadsi_lib::dicom::DicomImage>& slices);
    void setCurrSlice(int id);

private:
    QList<DICOMImageMetaDataTableModelObject> _shared_meta;
    QList<QString> _slices_paths;
    QList<QList<DICOMImageMetaDataTableModelObject>> _slices_meta;

    Ui::SliceMetadata _ui;
};

#endif    //CADSI_SLICEMETADATA_HPP
