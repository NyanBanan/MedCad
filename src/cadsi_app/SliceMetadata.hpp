//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_SLICEMETADATA_HPP
#define CADSI_SLICEMETADATA_HPP

#include <QWidget>

#include "dicom/DICOMImageMetaDataTableModelObject.hpp"

#include "ui_files/ui_slicemetadata.h"

class SliceMetadata : public QWidget {
    Q_OBJECT
public:
    SliceMetadata(QWidget* parent);

private:
    QList<DICOMImageMetaDataTableModelObject> _slices;

    Ui::SliceMetadata _ui;
};

#endif    //CADSI_SLICEMETADATA_HPP
