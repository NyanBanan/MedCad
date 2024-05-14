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
#include "PreprocessorTransformationsPipe.hpp"
#include "ui_files/ui_preprocessor.h"

class Preprocessor : public QWidget {
    Q_OBJECT
public:
    Preprocessor(QWidget* parent = nullptr);

    void setColorMapsNames(const QList<QString>& names);
    void loadImage(vtkAlgorithmOutput* input);
signals:
    void lutChanged(vtkLookupTable* lut);
public slots:
    void on_colorMapsComboBox_currentTextChanged(const QString& text);

    void on_smoothSigmaDoubleSpinBox_valueChanged();
    void on_smoothWindowDoubleSpinBox_valueChanged();
    void on_smoothApply_pressed();

    void on_denoiseFactorSlider_valueChanged();
    void on_denoiseFactorSpinBox_valueChanged();
    void on_denoiseThresholdSlider_valueChanged();
    void on_denoiseThresholdSpinBox_valueChanged();
    void on_denoiseApply_pressed();

    void on_enhancePushButton_pressed();

    void on_flipXPushButton_pressed();
    void on_flipYPushButton_pressed();
    void on_flipZPushButton_pressed();
private:
    ErrorMessageBox _error_win;
    PreprocessorTransformationsPipe _trans_pipe;
    DICOMPlaneViewer _plane_viewer;

    Ui::Preprocessor _ui;
};

#endif    //CADSI_PREPROCESSOR_HPP
