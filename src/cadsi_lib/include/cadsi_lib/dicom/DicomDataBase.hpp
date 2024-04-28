//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMDATABASE_HPP
#define CADSI_DICOMDATABASE_HPP

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <ranges>

#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/Result.hpp"

namespace cadsi_lib::dicom {
    //TODO: Try move all init to compile time. I think this possible
    /*!
          \brief DicomDataBase this is abstract class containing static function and constants for work with DICOM data base. \n
          All tables must have at least 2 columns. First of them is integer autoincrement primary key, second must be constrained by UNIQUE
         */
    class DicomDataBase {
    public:
        virtual ~DicomDataBase() = default;

        enum ErrorCodes {
            CONNECTION_ERROR,
            DB_CLOSED
        };

        struct SqlColumn {
            QString name;
            QString type;
            QString constraints;

            [[nodiscard]] QString toString() const;
        };

        /*!
	    \warning If an error happens error_code returned from QSqlError::ErrorTypes
         */
        virtual OperationStatus createOrConnect(QString path) = 0;
        [[nodiscard]] virtual Result<QSqlDatabase> getConnection() const = 0;

        /*!
          \warning generate_sql_table_creation required tables with 2 or more columns. Violation of this condition will cause ASSERT
         */
        static QString generate_sql_table_creation(QStringView table_name,
                                                   QList<SqlColumn> columns,
                                                   QStringList constraints);

        static inline const QString patients_table_name{"patients"};
        static inline const QString series_table_name{"series"};
        static inline const QString slices_table_name{"slices"};
        static inline const QStringList tables_names{patients_table_name, series_table_name, slices_table_name};

        static inline const QList patients_table_columns{
            SqlColumn{"patient_uid", "INTEGER", "PRIMARY KEY AUTOINCREMENT NOT NULL"},
            SqlColumn{"patient_name", "VARCHAR(255)", "NULL"},
            SqlColumn{"patient_id", "VARCHAR(255)", "NULL"},
            SqlColumn{"patient_sex", " VARCHAR(255)", " NULL"},
            SqlColumn{"patient_birth_date", "DATE", "NULL"},
            SqlColumn{"patient_comments", " VARCHAR(255)", "NULL"}};

        static inline const QStringList patients_table_constraints{{"UNIQUE(patient_name, patient_birth_date)"}};

        static inline const QString sql_patients_table_create =
            generate_sql_table_creation(patients_table_name, patients_table_columns, patients_table_constraints);

        static inline const QList series_table_columns{
            SqlColumn{"series_instance_uid", "INTEGER", "PRIMARY KEY AUTOINCREMENT NOT NULL"},
            SqlColumn{"series_number", "VARCHAR(255)", "NULL"},
            SqlColumn{"series_date", "VARCHAR(255)", "NULL"},
            SqlColumn{"series_time", "TIME", " NULL"},
            SqlColumn{"series_description", "VARCHAR(255)", "NULL"},
            SqlColumn{"modality", " VARCHAR(255)", "NULL"},
            SqlColumn{"institution_name", "VARCHAR(255)", "NULL"},
            SqlColumn{"preview_picture", "BLOB", "NULL"},
            SqlColumn{"patient_uid", "INTEGER", "NULL"}};

        static inline const QStringList series_table_constraints{{"UNIQUE(series_number)"},
                                                                 {"FOREIGN KEY (patient_uid) "
                                                                  "REFERENCES "
                                                                  "patients(patient_uid) ON DELETE "
                                                                  "CASCADE"}};

        static inline const QString sql_series_table_create =
            generate_sql_table_creation(series_table_name, series_table_columns, series_table_constraints);

        static inline const QList<SqlColumn> slices_table_columns{
            {"slice_id", "INTEGER", "PRIMARY KEY AUTOINCREMENT NOT NULL"},
            {"slice_path", "TEXT", "NOT NULL"},
            {"series_instance_uid", "INTEGER", "NOT NULL"}};

        static inline const QList<QString> slices_table_constraints{{"UNIQUE(slice_path) ON CONFLICT IGNORE"},
                                                                    {"FOREIGN KEY (series_instance_uid) REFERENCES "
                                                                     "series(series_instance_uid) ON DELETE CASCADE"}};

        static inline const QString sql_slices_table_create =
            generate_sql_table_creation(slices_table_name, slices_table_columns, slices_table_constraints);

        static inline const QStringList sql_create_tables{sql_patients_table_create,
                                                          sql_series_table_create,
                                                          sql_slices_table_create};

        /*!
          \warning generate_sql_insert required tables with 2 or more columns. Violation of this condition will cause ASSERT
         */
        static QString generate_sql_insert(QStringView table_name, const QList<SqlColumn>& columns);

        static inline const QString sql_patient_insert = generate_sql_insert(patients_table_name, patients_table_columns);
        static inline const QString sql_series_insert = generate_sql_insert(series_table_name, series_table_columns);
        static inline const QString sql_slices_insert = generate_sql_insert(slices_table_name, slices_table_columns);

        static QString generate_sql_insert_for_many_vals(QStringView table_name,
                                                         const QList<SqlColumn>& columns,
                                                         uint num_of_vals);

        static inline const auto sql_patient_insert_many_vals = [](uint num_of_vals) {
            return generate_sql_insert_for_many_vals(patients_table_name, patients_table_columns, num_of_vals);
        };
        static inline const auto sql_series_insert_many_vals = [](uint num_of_vals) {
            return generate_sql_insert_for_many_vals(series_table_name, series_table_columns, num_of_vals);
        };
        static inline const auto sql_slices_insert_many_vals = [](uint num_of_vals) {
            return generate_sql_insert_for_many_vals(slices_table_name, slices_table_columns, num_of_vals);
        };

        static QString generate_sql_select_by_unique_column(QStringView table_name,
                                                            QStringView uid_column_name,
                                                            QStringView unique_column_name);

        static inline const QString sql_patient_select_by_unique_column =
            generate_sql_select_by_unique_column(patients_table_name,
                                                 patients_table_columns[0].name,
                                                 patients_table_columns[1].name);
        static inline const QString sql_series_select_by_unique_column =
            generate_sql_select_by_unique_column(series_table_name,
                                                 series_table_columns[0].name,
                                                 series_table_columns[1].name);
        static inline const QString sql_slices_select_by_unique_column =
            generate_sql_select_by_unique_column(slices_table_name,
                                                 slices_table_columns[0].name,
                                                 slices_table_columns[1].name);

        static QString generate_sql_select_all(QStringView table_name);

        static inline const QString sql_patient_select_all = generate_sql_select_all(patients_table_name);
        static inline const QString sql_series_select_all = generate_sql_select_all(series_table_name);
        static inline const QString sql_slices_select_all = generate_sql_select_all(slices_table_name);

        static QString generate_sql_select_by_column(QStringView table_name, QStringView column_name);

        static inline const QString sql_series_select_by_patient_uid =
            generate_sql_select_by_column(series_table_name, patients_table_columns[0].name);
        static inline const QString sql_slices_select_by_series_uid =
            generate_sql_select_by_column(slices_table_name, series_table_columns[0].name);
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_DICOMDATABASE_HPP
