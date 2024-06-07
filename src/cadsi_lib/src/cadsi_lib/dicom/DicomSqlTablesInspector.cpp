//
// Created by nyanbanan on 23.04.2024.
//

#include "cadsi_lib/dicom/DicomSqlTablesInspector.hpp"

namespace cadsi_lib::dicom {

    OperationStatus DicomSqlTablesInspector::checkAndCreateTables(const DicomDataBase& db) {
        auto conn_result = db.getConnection();
        if (!conn_result.status.success) {
            return std::move(conn_result.status);
        } else {
            auto conn = conn_result.data;
            auto exist = checkTablesExists(conn);
            if (!exist) {
                return createTables(conn);
            }
            return {true};
        }
    }

    bool DicomSqlTablesInspector::checkTablesExists(const QSqlDatabase& conn) {
        auto tables = conn.tables();
        std::ranges::sort(tables);
        auto tables_exist =
            std::ranges::includes(tables, DicomDataBase::tables_names, [](const QString& str1, const QString& str2) {
                return str1.toStdString() < str2.toStdString();
            });
        return tables_exist;
    }

    OperationStatus DicomSqlTablesInspector::createTables(const QSqlDatabase& conn) {
        QSqlQuery create_query{conn};

        OperationStatus creationResult{.success = true};
        std::ranges::for_each(DicomDataBase::sql_create_tables, [&](const auto& sql_table_create) {
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
