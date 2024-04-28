//
// Created by nyanbanan on 16.04.2024.
//

#include "cadsi_lib/dicom/SqliteDicomDataBase.hpp"

namespace cadsi_lib::dicom {
    OperationStatus SqliteDicomDataBase::createOrConnect(QString path) {
        if(!_connection.isValid()) {
            _connection = QSqlDatabase::addDatabase("QSQLITE", "DICOMDB");
            _connection.setDatabaseName(path);
        }
        if (_connection.open()) {
            return {.success = true};
        } else {
            auto error = _connection.lastError();
            return {.success = false,
                    .error_code = static_cast<unsigned int>(error.type()),
                    .error_message = error.text().toStdString()};
        }
    }

    Result<QSqlDatabase> SqliteDicomDataBase::getConnection() const {
        if (!_connection.isOpen()) {
            return {.status = {.success = false, .error_code = ErrorCodes::DB_CLOSED}};
        } else {
            return {.status = {.success = true}, .data = _connection};
        }
    }
}    //namespace cadsi_lib::dicom
