//
// Created by nyanbanan on 16.04.2024.
//

#include "cadsi_lib/dicom/DicomDataBase.hpp"

namespace cadsi_lib::dicom {
    QString DicomDataBase::SqlColumn::toString() const {
        return QString("%1 %2 %3").arg(name, type, constraints);
    }

    QString DicomDataBase::generate_sql_table_creation(QStringView table_name,
                                                       QList<SqlColumn> columns,
                                                       QStringList constraints) {
        {
            Q_ASSERT_X(columns.size() > 1,
                       "DicomDataBase::generate_sql_table_creation",
                       "generate_sql_table_creation required tables with 2 or more columns");
            auto result_str = QString("CREATE TABLE IF NOT EXISTS %1 (%2").arg(table_name, columns[0].toString());
            result_str = std::accumulate(std::next(columns.begin()),
                                         columns.end(),
                                         result_str,
                                         [](QStringView str, const SqlColumn& column) {
                                             return QString("%1, %2").arg(str, column.toString());
                                         });
            result_str = std::accumulate(constraints.begin(),
                                         constraints.end(),
                                         result_str,
                                         [](QStringView str, QStringView constraint) {
                                             return QString("%1, %2").arg(str, constraint);
                                         });
            result_str += ")";
            return result_str;
        }
    }

    QString DicomDataBase::generate_sql_insert(QStringView table_name, const QList<SqlColumn>& columns) {
        return generate_sql_insert_for_many_vals(table_name, columns, 1);
    }

    QString DicomDataBase::generate_sql_insert_for_many_vals(QStringView table_name,
                                                             const QList<SqlColumn>& columns,
                                                             uint num_of_vals) {
        Q_ASSERT_X(columns.size() > 1,
                   "DicomDataBase::generate_sql_insert for table",
                   "generate_sql_insert required tables with 2 or more columns");
        if (num_of_vals == 0) {
            return {};
        }
        auto values_str = std::next(columns.begin())->name;
        if (columns.size() > 2) {
            values_str = std::accumulate(std::next(columns.begin(), 2),
                                         columns.end(),
                                         values_str,
                                         [](const QString& str, const DicomDataBase::SqlColumn& column) {
                                             return QString("%1, %2").arg(str, column.name);
                                         });
        }
        QString bind_str{"(?"};
        for (auto num : std::views::iota(0, columns.size() - 2)) {
            bind_str += ", ?";
        }
        bind_str += ")";
        auto res_query = QString("INSERT INTO %1(%2) VALUES").arg(table_name, values_str);

        res_query += bind_str;
        for (auto num : std::views::iota(1, int(num_of_vals))) {
            res_query += ", " + bind_str;
        }
        return res_query;
    }

    QString DicomDataBase::generate_sql_select_by_unique_column(QStringView table_name,
                                                                QStringView uid_column_name,
                                                                QStringView unique_column_name) {
        return QString("SELECT %1 FROM %2 WHERE %3 = ?").arg(uid_column_name, table_name, unique_column_name);
    }

    QString DicomDataBase::generate_sql_select_all(QStringView table_name) {
        return QString("SELECT * FROM %1").arg(table_name);
    }

    QString DicomDataBase::generate_sql_select_by_column(QStringView table_name, QStringView column_name) {
        return QString("SELECT * FROM %1 WHERE %2=?").arg(table_name, column_name);
    }
}    //namespace cadsi_lib::dicom
