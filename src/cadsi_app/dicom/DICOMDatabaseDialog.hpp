//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_DICOMDATABASEDIALOG_HPP
#define CADSI_DICOMDATABASEDIALOG_HPP

#include <QDialog>
#include <QErrorMessage>
#include <QFileDialog>
#include <QProcessEnvironment>
#include <QProgressDialog>
#include <QThread>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>

#include "../ui_files/ui_dicomdatabasedialog.h"
#include "DICOMFromFilesToSqlMapper.hpp"
#include "DICOMImageMetaDataTableModel.hpp"
#include "DICOMPatientTableModel.hpp"
#include "DICOMSeriesListWidgetItem.hpp"

class DICOMDatabaseDialog : public QDialog {
    Q_OBJECT
public:
    DICOMDatabaseDialog(QWidget* parent = nullptr);
public slots:
    void patientSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void updatePatientsData(QList<cadsi_lib::dicom::DicomPatient> patients);
    void showErrorMessage(const QString& error_message);
    void on_scanPushButton_pressed();

private:
    void initDataBaseFile();

    QString _db_file;
    QErrorMessage _error_win;
    DICOMPatientTableModel _model;
    DICOMFromFilesToSqlMapper _mapper;
    Ui::DICOMDatabaseDialog _ui;
};

#endif    //CADSI_DICOMDATABASEDIALOG_HPP
