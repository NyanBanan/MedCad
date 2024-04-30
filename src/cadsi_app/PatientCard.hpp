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
    void onDicomLoaded(int patient_id, int series_id);
    void on_changePhotoButton_pressed();
    void on_birthdateDateTimeEdit_dateChanged(QDate born);
    void on_dicomPushButton_pressed();

private:
    QSharedPointer<DICOMData> _dicom_data{nullptr};
    DICOMDatabaseDialog* _dicom_dialog{nullptr};
    DICOMSliceTableModel _slices_model;

    Ui::PatientCard _ui;
};

#endif    //CADSI_PATIENTCARD_HPP
