//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_DICOMDATABASEDIALOG_HPP
#define CADSI_DICOMDATABASEDIALOG_HPP

#include <QDialog>
#include <QFileDialog>
#include <QModelIndex>
#include <QProcessEnvironment>
#include <QProgressDialog>
#include <QThread>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>

#include "../ui_files/ui_dicomdatabasedialog.h"
#include "DICOMFromFilesToSqlMapper.hpp"
#include "DICOMImageMetaDataTableModel.hpp"
#include "DICOMScanDialog.hpp"
#include "DICOMSeriesListWidgetItem.hpp"
#include "../ErrorMessageBox.hpp"
#include "models/DICOMPatientTableModel.hpp"
#include "models/DICOMSeriesListModel.hpp"
#include "models/DICOMSliceTableModel.hpp"

class DICOMDatabaseDialog : public QDialog {
    Q_OBJECT
public:
    DICOMDatabaseDialog(QWidget* parent = nullptr);

signals:
    void dicomLoaded(int patient_id, int series_id);
    void error(const QString& error_message);
public slots:
    void patientSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void seriesSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void scanDicomDir(bool deep_scan, const QString& scan_dir);
    void on_scanPushButton_pressed();
    void on_importPushButton_pressed();
    void on_deletePushButton_pressed();

    void setDICOMSharedData(QSharedPointer<DICOMData> dicom_data);

private:
    void initDataBaseFile();

    QString _db_file;
    DICOMPatientTableModel* _patient_model;
    DICOMSeriesListModel* _series_model;
    DICOMSliceTableModel* _slices_model;
    DICOMFromFilesToSqlMapper _mapper;
    Ui::DICOMDatabaseDialog _ui;
};

#endif    //CADSI_DICOMDATABASEDIALOG_HPP
