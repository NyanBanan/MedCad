//
// Created by nyanbanan on 09.04.2024.
//

#include "DICOMDatabaseDialog.hpp"

DICOMDatabaseDialog::DICOMDatabaseDialog(QWidget* parent) : QDialog(parent) {
    initDataBaseFile();

    _ui.setupUi(this);

    _ui.importPushButton->setEnabled(false);
    _ui.deletePushButton->setEnabled(false);

    _patient_model = new DICOMPatientTableModel(this);
    _series_model = new DICOMSeriesListModel(this);
    _slices_model = new DICOMSliceTableModel(this);

    _ui.patientsTableView->setModel(_patient_model);

    auto patient_selection_model = _ui.patientsTableView->selectionModel();
    connect(patient_selection_model,
            &QItemSelectionModel::selectionChanged,
            this,
            &DICOMDatabaseDialog::patientSelectionChanged);

    _ui.seriesListView->setModel(_series_model);

    auto series_selection_model = _ui.seriesListView->selectionModel();
    connect(series_selection_model,
            &QItemSelectionModel::selectionChanged,
            this,
            &DICOMDatabaseDialog::seriesSelectionChanged);

    _ui.widgetSlices->setModel(_slices_model);

    connect(&_mapper, &DICOMFromFilesToSqlMapper::error, this, &DICOMDatabaseDialog::showErrorMessage);

    _mapper.setDataBaseFile(_db_file);
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
    auto all_selected_ind = _ui.patientsTableView->selectionModel()->selectedRows();
    auto size = all_selected_ind.size();
    auto is_series_selected = _ui.seriesListView->selectionModel()->hasSelection();
    if (size == 0 && !is_series_selected) {
        _series_model->setPatientInd(-1);
        _slices_model->setPatientInd(-1);
        _ui.seriesListView->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(false);
    } else if (size == 1) {
        _ui.seriesListView->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(true);
        auto patient_index = all_selected_ind[0];
        if (!patient_index.isValid()) {
            return;
        }
        _series_model->setPatientInd(patient_index.row());
        _slices_model->setPatientInd(patient_index.row());
    } else if (size > 0) {
        _series_model->setPatientInd(-1);
        _slices_model->setPatientInd(-1);
        _ui.seriesListView->selectionModel()->clear();
        _ui.deletePushButton->setEnabled(true);
    }
}

void DICOMDatabaseDialog::seriesSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
    auto all_selected_ind = _ui.seriesListView->selectionModel()->selectedRows();
    auto size = all_selected_ind.size();
    if (size == 0) {
        _slices_model->setSeriesInd(-1);
        _ui.importPushButton->setEnabled(false);
        _ui.deletePushButton->setEnabled(false);
    } else if (size == 1) {
        _ui.patientsTableView->selectionModel()->clear();

        _ui.importPushButton->setEnabled(true);
        _ui.deletePushButton->setEnabled(true);
        auto series_index = all_selected_ind[0];
        if (!series_index.isValid()) {
            return;
        }
        _slices_model->setSeriesInd(series_index.row());
    } else if (size > 0) {
        _ui.patientsTableView->selectionModel()->clear();

        _slices_model->setSeriesInd(-1);
        _ui.importPushButton->setEnabled(false);
        _ui.deletePushButton->setEnabled(true);
    }
}

void DICOMDatabaseDialog::showErrorMessage(const QString& error_message) {
    _error_win.showMessage(error_message);
}

void DICOMDatabaseDialog::on_scanPushButton_pressed() {
    auto scanDialog = new DICOMScanDialog(this);

    connect(scanDialog, &QDialog::finished, scanDialog, &QObject::deleteLater);

    connect(scanDialog, &DICOMScanDialog::scanDirSelected, this, &DICOMDatabaseDialog::scanDicomDir);

    scanDialog->show();
}

void DICOMDatabaseDialog::scanDicomDir(bool deep_scan, const QString& scan_dir) {
    auto progress_dialog = new QProgressDialog(this);

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

void DICOMDatabaseDialog::setDICOMSharedData(QSharedPointer<DICOMData> dicom_data) {
    connect(&_mapper, &DICOMFromFilesToSqlMapper::dataUpdated, dicom_data.data(), &DICOMData::setData);

    _patient_model->setDicomData(dicom_data);
    _series_model->setDicomData(dicom_data);
    _slices_model->setDicomData(dicom_data);

    _mapper.loadFromSql();
}

void DICOMDatabaseDialog::on_importPushButton_pressed() {
    auto selected_series = _ui.seriesListView->selectionModel()->selectedRows();
    if (selected_series.size() != 1) {
        _error_win.showMessage("Wrong series selection (only 1 series must be selected)");
        return;
    }
    auto curr_series_id = selected_series.first().row();
    auto curr_patient_id = _series_model->getCurrPatientInd();
    if (curr_patient_id < 0) {
        _error_win.showMessage("Get patient id error");
        return;
    }
    emit dicomLoaded(curr_patient_id, curr_series_id);
    close();
}

void DICOMDatabaseDialog::on_deletePushButton_pressed() {
    auto patients = _ui.patientsTableView->selectionModel()->selectedRows();

    if (!patients.isEmpty()) {
        QList<QString> patients_id;
        auto column_num = DICOMPatientTableModel::ID_ROLE - DICOMPatientTableModel::FIRST_ROLE - 1;
        std::ranges::for_each(patients, [this, &patients_id, &column_num](const QModelIndex& patient_ind) {
            auto name_index = patient_ind.model()->index(patient_ind.row(), column_num);
            auto unique_name = _patient_model->data(name_index).toString();
            patients_id.push_back(unique_name);
        });
        _mapper.deletePatients(patients_id);
    } else {
        auto series = _ui.seriesListView->selectionModel()->selectedRows();
        if (!series.isEmpty()) {
            QList<QString> series_id;
            std::ranges::for_each(series, [this, &series_id](auto series_ind) {
                auto unique_name = _series_model->data(series_ind).toString();
                series_id.push_back(unique_name);
            });
            _mapper.deleteSeries(series_id);
        }
    }
}
