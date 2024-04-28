//
// Created by nyanbanan on 09.04.2024.
//

#include "DICOMDatabaseDialog.hpp"

DICOMDatabaseDialog::DICOMDatabaseDialog(QWidget* parent) : QDialog(parent) {
    initDataBaseFile();

    _ui.setupUi(this);

    _ui.tableViewPatients->setModel(&_model);

    auto selection_model = _ui.tableViewPatients->selectionModel();
    connect(selection_model, &QItemSelectionModel::selectionChanged, this, &DICOMDatabaseDialog::patientSelectionChanged);

    connect(&_mapper, &DICOMFromFilesToSqlMapper::error, this, &DICOMDatabaseDialog::showErrorMessage);
    connect(&_mapper, &DICOMFromFilesToSqlMapper::updatedData, this, &DICOMDatabaseDialog::updatePatientsData);

    _mapper.setDataBaseFile(_db_file);

    _mapper.loadFromSql();
}

void DICOMDatabaseDialog::initDataBaseFile() {
    QDir _db_file_path{QProcessEnvironment::systemEnvironment().value("APPDATA")};
    if (!_db_file_path.cd("cadsi")) {
        _db_file_path.mkdir("cadsi");
        _db_file_path.cd("cadsi");
    }
    _db_file = _db_file_path.absoluteFilePath("cadsi_dicom.db");
}

void DICOMDatabaseDialog::patientSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
    auto size = selected.size();
    if (size == 0) {
        _ui.seriesListWidget->clear();
        _ui.seriesListWidget->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(false);
    } else if (size == 1) {
        _ui.seriesListWidget->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(true);
        auto patient_index = selected.indexes()[0];
        auto series_list = patient_index.data(DICOMPatientItemModel::PatientDataRoles::ALL_SERIES_FOR_PATIENT_ROLE)
                               .value<QList<cadsi_lib::dicom::DicomSeries>>();

        int curr_series_ind = 0;
        std::ranges::for_each(series_list,
                              [&curr_series_ind, &patient_index, this](const cadsi_lib::dicom::DicomSeries& series) {
                                  auto* curr_item = new DICOMSeriesListWidgetItem(series);

                                  auto series_index = patient_index.model()->index(curr_series_ind++, 0, patient_index);
                                  curr_item->setModelIndex(series_index);
                                  _ui.seriesListWidget->addItem(curr_item);
                              });
    } else if (size > 0) {
        _ui.seriesListWidget->clear();
        _ui.seriesListWidget->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(true);
    }
}

void DICOMDatabaseDialog::showErrorMessage(const QString& error_message) {
    _error_win.showMessage(error_message);
}

void DICOMDatabaseDialog::updatePatientsData(const QList<cadsi_lib::dicom::DicomPatient>& patients) {
    _model.setPatients(patients);
}

void DICOMDatabaseDialog::on_scanPushButton_pressed() {
    auto scanDialog = new DICOMScanDialog();

    connect(scanDialog, &QDialog::finished, scanDialog, &QObject::deleteLater);

    connect(scanDialog, &DICOMScanDialog::scanDirSelected, this, &DICOMDatabaseDialog::scanDicomDir);

    scanDialog->show();
}

void DICOMDatabaseDialog::scanDicomDir(bool deep_scan, const QString& scan_dir) {
    auto progress_dialog = new QProgressDialog();

    connect(progress_dialog, &QProgressDialog::finished, progress_dialog, &QObject::deleteLater);

    progress_dialog->setMinimum(0);
    progress_dialog->setMaximum(0);
    progress_dialog->setValue(0);
    progress_dialog->resize(400, 100);
    progress_dialog->setLabel(new QLabel("Чтение DICOM файлов", this));
    progress_dialog->setModal(true);
    progress_dialog->show();

    auto thread = new QThread();

    connect(&_mapper, &DICOMFromFilesToSqlMapper::finished, thread, &QThread::quit);

    connect(progress_dialog, &QProgressDialog::canceled, thread, &QThread::quit);

    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, &_mapper, [this]() {
        _mapper.moveToThread(QApplication::instance()->thread());
    });
    connect(thread, &QThread::finished, progress_dialog, &QProgressDialog::close);
    connect(thread, &QThread::started, &_mapper, &DICOMFromFilesToSqlMapper::loadToDataBase);

    _mapper.moveToThread(thread);
    _mapper.setNeedDeepScan(deep_scan);
    _mapper.setDicomDir(scan_dir);

    thread->start();
}
