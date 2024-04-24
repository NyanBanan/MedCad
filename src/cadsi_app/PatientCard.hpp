//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_PATIENTCARD_HPP
#define CADSI_PATIENTCARD_HPP

#include <QDate>
#include <QFileDialog>
#include <QWidget>

#include "SliceMetadata.hpp"
#include "dicom/DICOMDatabaseDialog.hpp"
#include "ui_files/ui_patientcard.h"

class PatientCard : public QWidget {
    Q_OBJECT
public:
    PatientCard(QWidget* parent = nullptr);

public slots:
    void on_changePhotoButton_pressed();
    void on_birthdateDateTimeEdit_dateChanged(QDate born);
    void on_dicomPushButton_pressed();

private:
    SliceMetadata _slice_metadata{nullptr};
    DICOMDatabaseDialog* _dicom_dialog{nullptr};

    Ui::PatientCard _ui;
};

#endif    //CADSI_PATIENTCARD_HPP
