//
// Created by nyanbanan on 23.04.2024.
//

#include "DICOMFromFilesToSqlMapper.hpp"

DICOMFromFilesToSqlMapper::DICOMFromFilesToSqlMapper(QObject* parent) : QObject(parent) {}

void DICOMFromFilesToSqlMapper::setDataBaseFile(const QString& db_path) {
    if (_db_file_path != db_path) {
        _connection_need_update = true;
        _db_file_path = db_path;
    }
}

void DICOMFromFilesToSqlMapper::setDicomDir(const QString& dicom_dir) {
    _dicom_dir = dicom_dir;
}

void DICOMFromFilesToSqlMapper::loadToDataBase() {
    updateConnection();

    cadsi_lib::dicom::providers::FileDataDicomProvider file_data_provider;
    auto result = file_data_provider.readDir(_dicom_dir);
    if (!result.status.success) {
        emit error(QString::fromStdString(result.status.error_message));
        return;
    }

    auto push_patients_res = _db_mapper.insertPatients(result.data);
    if (!push_patients_res.success) {
        emit error(QString::fromStdString(push_patients_res.error_message));
        return;
    }

    loadFromSql();
}

void DICOMFromFilesToSqlMapper::loadFromSql() {
    updateConnection();

    auto all_patients_res = _db_mapper.getAllPatients();
    if (!all_patients_res.status.success) {
        emit error(QString::fromStdString(all_patients_res.status.error_message));
        return;
    }
    emit updatedData(all_patients_res.data);
    emit finished();
}

void DICOMFromFilesToSqlMapper::updateConnection() {
    if (_connection_need_update) {
        auto db_conn_res = _db.createOrConnect(_db_file_path);
        if (!db_conn_res.success) {
            emit error(QString::fromStdString(db_conn_res.error_message));
            return;
        }

        cadsi_lib::dicom::DicomSqlTablesInspector insp;
        auto create_tables_res = insp.checkAndCreateTables(_db);
        if (!create_tables_res.success) {
            emit error(QString::fromStdString(create_tables_res.error_message));
            return;
        }

        _db_mapper.setDataBase(&_db);
    }
}
