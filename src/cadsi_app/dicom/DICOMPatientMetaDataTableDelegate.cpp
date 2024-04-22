//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientMetaDataTableDelegate.hpp"

#include <QPushButton>

void DICOMPatientMetaDataTableDelegate::paint(QPainter* painter,
                                              const QStyleOptionViewItem& option,
                                              const QModelIndex& index) const {
    if (index.isValid() && index.column() == 6) {
        auto button = new QPushButton;
        button->render(
            painter /*, option.rect.topLeft()*/ /*, {option.rect.topLeft().x(), option.rect.topLeft().y(), 50, 50}*/);
    }
    QStyledItemDelegate::paint(painter, option, index);
}
