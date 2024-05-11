//
// Created by nyanbanan on 06.05.2024.
//

#ifndef CADSI_COLORMAP_HPP
#define CADSI_COLORMAP_HPP
#include <QWidget>
#include <cadsi_lib/color_maps/providers/GlobalColorMapsProvider.hpp>

#include "ScalarBarWidget.hpp"
#include "ui_files/ui_colormap.h"

class ColorMap : public QWidget {
    Q_OBJECT
public:
    ColorMap(QWidget* parent = nullptr);
    void setColorMapNames(QList<QString> color_map_names);

signals:
    void windowValueChanged(int windowValue);
    void centerDensityChanged(int levelValue);
    void lutChanged(vtkLookupTable* lut);
    void error(const QString& error_message);
public slots:
    void on_cmapComboBox_currentTextChanged(const QString& text);

private:
    Ui::ColorMap _ui;
};

#endif    //CADSI_COLORMAP_HPP
