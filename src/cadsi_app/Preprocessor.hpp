//
// Created by nyanbanan on 01.05.2024.
//

#ifndef CADSI_PREPROCESSOR_HPP
#define CADSI_PREPROCESSOR_HPP

#include <QWidget>
#include <vtkAlgorithmOutput.h>
#include "ColorMap.hpp"
#include "ErrorMessageBox.hpp"
#include "PlaneView.hpp"
#include "ui_files/ui_preprocessor.h"

class Preprocessor : public QWidget {
    Q_OBJECT
public:
    Preprocessor(QWidget* parent = nullptr);

    void setColorMapsNames(const QList<QString>& names);
    void loadImage(vtkStringArray* image_file_names);
signals:
    void lutChanged(vtkLookupTable* lut);
public slots:
    void on_colorMapsComboBox_currentTextChanged(const QString& text);

private:
    ErrorMessageBox _error_win;

    Ui::Preprocessor _ui;
};

#endif    //CADSI_PREPROCESSOR_HPP
