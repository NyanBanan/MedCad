//
// Created by nyanbanan on 16.04.2024.
//

#include "cadsi_lib/dicom/SqliteDicomDataBase.hpp"

namespace cadsi_lib::dicom {
    OperationStatus SqliteDicomDataBase::createOrConnect(QString path) {
        _connection = QSqlDatabase::addDatabase("QSQLITE", "DICOMDB");
        _connection.setDatabaseName(path);
        if (_connection.open()) {
            return {.success = true};
        } else {
            auto error = _connection.lastError();
            return {.success = false,
                    .error_code = static_cast<unsigned int>(error.type()),
                    .error_message = error.text().toStdString()};
        }
    }

    Result<QSqlDatabase> SqliteDicomDataBase::getConnection() {
        if (!_connection.isOpen()) {
            return {.status = {.success = false, .error_code = ErrorCodes::DB_CLOSED}};
        } else {
            return {.status = {.success = true}, .data = _connection};
        }
    }

    Result<bool> SqliteDicomDataBase::checkTablesExists() {
        auto conn_result = getConnection();
        if (!conn_result.status.success) {
            return {.status = std::move(conn_result.status)};
        } else {
            auto tables = _connection.tables();
            std::ranges::sort(tables);
            auto tables_exist = std::ranges::includes(tables, tables_names, [](const QString& str1, const QString& str2) {
                return str1.toStdString() < str2.toStdString();
            });
            return {.status = {.success = true}, .data = tables_exist};
        }
    }

    OperationStatus SqliteDicomDataBase::createTables() {
        auto conn_result = getConnection();
        if (!conn_result.status.success) {
            return conn_result.status;
        }
        auto conn = conn_result.data;
        QSqlQuery create_query{conn};

        OperationStatus creationResult{.success = true};
        std::ranges::for_each(sql_create_tables, [&](const auto& sql_table_create) {
            if (!create_query.exec(sql_table_create)) {
                auto error = create_query.lastError();
                creationResult.success = false;
                creationResult.error_code = static_cast<unsigned int>(error.type());
                creationResult.error_message = std::move(error.text().toStdString());
            }
        });
        return creationResult;
    }

}    //namespace cadsi_lib::dicom
