//
// Created by nyanbanan on 03.05.2024.
//

#ifndef CADSI_SCALARBARWIDGET_HPP
#define CADSI_SCALARBARWIDGET_HPP

#include <QPainter>
#include <QWidget>
#include <ranges>
#include <vtkLookupTable.h>

class ScalarBarWidget : public QWidget {
public:
    ScalarBarWidget(QWidget* parent = nullptr);
public slots:
    void setLut(vtkLookupTable* lut);
    void setTopBottomMargins(uint margin);

    void paintEvent(QPaintEvent* event) override;

private:
    vtkSmartPointer<vtkLookupTable> _lut{nullptr};
    uint _margin{0};
};

#endif    //CADSI_SCALARBARWIDGET_HPP
