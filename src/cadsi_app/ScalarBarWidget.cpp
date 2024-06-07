//
// Created by nyanbanan on 03.05.2024.
//

#include "ScalarBarWidget.hpp"

ScalarBarWidget::ScalarBarWidget(QWidget* parent) : QWidget(parent) {}

void ScalarBarWidget::setLut(vtkLookupTable* lut) {
    _lut = lut;
    update();
}

void ScalarBarWidget::paintEvent(QPaintEvent* event) {
    if (_lut.GetPointer() == nullptr) {
        return;
    }
    QPainter painter(this);

    auto width = QWidget::width();
    auto height = QWidget::height();

    auto g = (double)_lut->GetNumberOfAvailableColors() / height;

    for (auto y : std::views::iota(_margin, height - _margin)) {
        auto color = _lut->GetTable()->GetTuple4(y * g);
        painter.setPen(QColor((int)color[0], (int)color[1], (int)color[2], (int)color[3]));
        painter.drawLine(0, height - y, width, height - y);
    }
}

void ScalarBarWidget::setTopBottomMargins(uint margin) {
    _margin = margin;
}
