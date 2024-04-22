//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTMETADATATABLEDELEGATE_HPP
#define CADSI_DICOMPATIENTMETADATATABLEDELEGATE_HPP

#include <QStyledItemDelegate>

class DICOMPatientMetaDataTableDelegate : public QStyledItemDelegate{
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif    //CADSI_DICOMPATIENTMETADATATABLEDELEGATE_HPP
