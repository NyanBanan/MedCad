//
// Created by nyanbanan on 16.04.2024.
//

#include "cadsi_lib/dicom/SqliteDicomDataMapper.hpp"

namespace cadsi_lib::dicom {
    void SqliteDicomDataMapper::setDataBase(DicomDataBase* db) {
        _db = db;
    }

    Result<QList<DicomPatient>> SqliteDicomDataMapper::getAllPatients() {
        if (_db == nullptr) {
            return {
                .status = {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"}};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return {.status = conn_res.status};
        }
        auto conn = conn_res.data;

        QSqlQuery query(conn);

        query.exec(DicomDataBase::sql_patient_select_all);

        if (!query.exec()) {
            auto error = query.lastError();
            return {.status = {.success = false,
                               .error_code = static_cast<unsigned int>(error.type()),
                               .error_message = std::format("getAllPatients error: {}", error.text().toStdString())}};
        }

        QList<DicomPatient> patients;

        while (query.next()) {
            auto patient_uid = query.value(0).value<uint>();
            auto patients_series_res = selectAllSeriesForPatient(conn, patient_uid);
            if (!patients_series_res.status.success) {
                return {patients_series_res.status};
            }
            auto& patient = patients.emplaceBack();
            patient.addSeries(std::move(patients_series_res.data));
            patient.setId(query.value(1).toString());
            patient.setName(query.value(2).toString());
            patient.setSex(query.value(3).toString());
            patient.setBirthDate(query.value(4).toString());
            patient.setComments(query.value(5).toString());
        }

        return {.status{.success = true}, .data = std::move(patients)};
    }

    Result<QList<DicomSeries>> SqliteDicomDataMapper::selectAllSeriesForPatient(QSqlDatabase& conn, uint patient_uid) {
        QSqlQuery series_query(conn);

        series_query.prepare(DicomDataBase::sql_series_select_by_patient_uid);
        series_query.addBindValue(patient_uid);

        if (!series_query.exec()) {
            auto error = series_query.lastError();
            return {.status = {.success = false,
                               .error_code = static_cast<unsigned int>(error.type()),
                               .error_message = std::format("selectAllSeriesForPatient with id - {} error: {}",
                                                            patient_uid,
                                                            error.text().toStdString())}};
        }

        QList<DicomSeries> series;

        int preview_field_ind = series_query.record().indexOf("preview_picture");
        while (series_query.next()) {
            auto series_uid = series_query.value(0).value<uint>();
            auto slices_res = selectAllSlicesForSeries(conn, series_uid);
            if (!slices_res.status.success) {
                return {slices_res.status};
            }
            auto& curr_series = series.emplaceBack();
            curr_series.setPreview(QImage::fromData(series_query.value(preview_field_ind).toByteArray(), "jpg"));

            auto slices = slices_res.data;

            if (slices.empty()) {
                continue;
            }
            auto first_image = slices[0];

            vtkNew<vtkDICOMReader> series_meta_data_reader;

            series_meta_data_reader->SetFileName(first_image.getImageFilePath().toStdString().c_str());
            series_meta_data_reader->Update();

            auto meta = series_meta_data_reader->GetMetaData();

            for (auto iter = meta->Begin(); iter != meta->End(); ++iter) {
                if (iter->IsPerInstance()) {
                    auto instance_num = iter->GetNumberOfInstances();
                    if (slices.size() < instance_num) {
                        instance_num = (int)slices.size();
                    }
                    for (auto inst : std::views::iota(0, instance_num)) {
                        slices[inst].setMeta(*iter);
                    }
                } else {
                    curr_series.setMeta(*iter);
                }
            }

            curr_series.assignImages(slices);
        }

        return {.status{.success = true}, .data = std::move(series)};
    }

    Result<QList<DicomImage>> SqliteDicomDataMapper::selectAllSlicesForSeries(QSqlDatabase& conn, uint series_uid) {
        QSqlQuery series_query(conn);

        series_query.prepare(DicomDataBase::sql_slices_select_by_series_uid);
        series_query.addBindValue(series_uid);

        if (!series_query.exec()) {
            auto error = series_query.lastError();
            return {.status = {.success = false,
                               .error_code = static_cast<unsigned int>(error.type()),
                               .error_message = std::format("selectAllSlicesForSeries with id - {} error: {}",
                                                            series_uid,
                                                            error.text().toStdString())}};
        }

        QList<DicomImage> slices;

        while (series_query.next()) {
            slices.emplaceBack(series_query.value(1).toString());
        }

        return {.status{.success = true}, .data = std::move(slices)};
    }

    OperationStatus SqliteDicomDataMapper::deletePatients(QList<QString> patients_uid) {
        if (_db == nullptr) {
            return {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return conn_res.status;
        }
        auto conn = conn_res.data;

        QSqlQuery query(conn);

        query.prepare(DicomDataBase::sql_patient_delete_by_unique_for_many_vals(patients_uid.size()));
        std::ranges::for_each(patients_uid, [&query](auto id) {
            query.addBindValue(id);
        });

        if (!query.exec()) {
            auto error = query.lastError();
            return {.success = false,
                    .error_code = static_cast<unsigned int>(error.type()),
                    .error_message = std::format("deletePatients error: {}", error.text().toStdString())};
        }
        return {true};
    }

    OperationStatus SqliteDicomDataMapper::deleteSeries(QList<QString> series_uid) {
        if (_db == nullptr) {
            return {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return conn_res.status;
        }
        auto conn = conn_res.data;

        QSqlQuery query(conn);

        query.prepare(DicomDataBase::sql_series_delete_by_unique_for_many_vals(series_uid.size()));
        std::ranges::for_each(series_uid, [&query](auto id) {
            query.addBindValue(id);
        });

        if (!query.exec()) {
            auto error = query.lastError();
            return {.success = false,
                    .error_code = static_cast<unsigned int>(error.type()),
                    .error_message = std::format("deleteSeries error: {}", error.text().toStdString())};
        }
        return {true};
    }

    OperationStatus SqliteDicomDataMapper::insertPatient(const DicomPatient& patient) {
        return insertPatients(QList{patient});
    }

    OperationStatus SqliteDicomDataMapper::insertPatients(const QList<DicomPatient>& patients) {
        if (_db == nullptr) {
            return {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return conn_res.status;
        }
        auto conn = conn_res.data;

        conn.transaction();
        auto res = insertPatients(conn, patients);
        if (!res.success) {
            conn.rollback();
            return res;
        }
        conn.commit();

        return {true};
    }

    OperationStatus SqliteDicomDataMapper::insertPatient(QSqlDatabase& conn, const DicomPatient& patient) {
        return insertPatients(conn, QList{patient});
    }

    OperationStatus SqliteDicomDataMapper::insertPatients(QSqlDatabase& conn, const QList<DicomPatient>& patients) {
        QSqlQuery query(conn);

        auto query_str = DicomDataBase::sql_patient_insert;

        for (const auto& patient : patients) {
            uint patient_id;

            query.prepare(query_str);
            query.addBindValue(patient.getId());
            query.addBindValue(patient.getName());
            query.addBindValue(patient.getSex());
            query.addBindValue(patient.getBirthDateDicomString());
            query.addBindValue(patient.getComments());
            if (!query.exec()) {
                auto error = query.lastError();
                auto sqlite_code = error.nativeErrorCode().toInt();
                if (sqlite_code
                    == cadsi_lib::dicom::SqliteDicomDataBase::SQLiteNativeErrorCodes::SQLITE_CONSTRAINT_UNIQUE) {
                    auto select_patient_id_query_str = DicomDataBase::sql_patient_select_by_unique_column;
                    query.prepare(select_patient_id_query_str);
                    query.addBindValue(patient.getName());

                    if (!query.exec()) {
                        error = query.lastError();
                        return {.success = false,
                                .error_code = static_cast<unsigned int>(error.type()),
                                .error_message = std::format("insertPatients select inserted patient id with name - "
                                                             "{},  "
                                                             "error: {}",
                                                             patient.getName().toStdString(),
                                                             error.text().toStdString())};
                    }
                    query.next();
                    patient_id = query.value(0).value<uint>();
                } else {
                    return {.success = false,
                            .error_code = static_cast<unsigned int>(error.type()),
                            .error_message = std::format("insertPatients with name - {},  error: {}",
                                                         patient.getName().toStdString(),
                                                         error.text().toStdString())};
                }
            } else {
                auto id_var = query.lastInsertId();
                if (id_var.isValid()) {
                    patient_id = id_var.value<uint>();
                }
            }
            //Push patient series to database
            for (const auto& series : patient.getSeries()) {
                auto res = insertSeries(conn, patient_id, series);
                if (!res.success) {
                    return res;
                }
            }
        }
        return {true};
    }

    OperationStatus SqliteDicomDataMapper::insertSeries(uint patient_uid, const DicomSeries& series) {
        return insertSeries(patient_uid, QList{series});
    }

    OperationStatus SqliteDicomDataMapper::insertSeries(uint patient_uid, const QList<DicomSeries>& series) {
        if (_db == nullptr) {
            return {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return conn_res.status;
        }
        auto conn = conn_res.data;
        conn.transaction();
        auto res = insertSeries(conn, patient_uid, series);
        if (!res.success) {
            conn.rollback();
        } else {
            conn.commit();
        }
        return res;
    }

    OperationStatus SqliteDicomDataMapper::insertSeries(QSqlDatabase& conn, uint patient_uid, const DicomSeries& series) {
        return insertSeries(conn, patient_uid, QList{series});
    }

    OperationStatus SqliteDicomDataMapper::insertSeries(QSqlDatabase& conn,
                                                        uint patient_uid,
                                                        const QList<DicomSeries>& series) {
        QSqlQuery query(conn);

        auto query_str = DicomDataBase::sql_series_insert;

        for (const auto& curr_series : series) {
            uint series_id;

            query.prepare(query_str);
            query.addBindValue(curr_series.getUid());
            query.addBindValue(curr_series.getDateString());
            query.addBindValue(curr_series.getTimeString());
            query.addBindValue(curr_series.getDescription());
            query.addBindValue(curr_series.getModality());
            query.addBindValue(curr_series.getInstitutionName());

            QByteArray preview_array;
            QBuffer buf(&preview_array);
            buf.open(QIODevice::WriteOnly);
            curr_series.getPreview().save(&buf, "jpg");

            query.addBindValue(preview_array);
            query.addBindValue(patient_uid);
            if (!query.exec()) {
                auto error = query.lastError();
                auto sqlite_code = error.nativeErrorCode().toInt();
                if (sqlite_code
                    == cadsi_lib::dicom::SqliteDicomDataBase::SQLiteNativeErrorCodes::SQLITE_CONSTRAINT_UNIQUE) {
                    auto select_series_id_query_str = DicomDataBase::sql_series_select_by_unique_column;
                    query.prepare(select_series_id_query_str);
                    query.addBindValue(curr_series.getUid());

                    if (!query.exec()) {
                        error = query.lastError();

                        return {.success = false,
                                .error_code = static_cast<unsigned int>(error.type()),
                                .error_message = std::format("insertSeries select inserted series id with series "
                                                             "number - "
                                                             "{},  error: {}",
                                                             curr_series.getUid().toStdString(),
                                                             error.text().toStdString())};
                    }
                    query.next();
                    series_id = query.value(0).value<uint>();
                } else {
                    return {.success = false,
                            .error_code = static_cast<unsigned int>(error.type()),
                            .error_message = std::format("insertSeries with series number - {},  error: {}",
                                                         curr_series.getUid().toStdString(),
                                                         error.text().toStdString())};
                }
            } else {
                auto id_var = query.lastInsertId();
                if (id_var.isValid()) {
                    series_id = id_var.value<uint>();
                }
            }
            //Push series images to database
            for (const auto& slice : curr_series.getImages()) {
                auto res = insertSlice(conn, series_id, slice);
                if (!res.success) {
                    return res;
                }
            }
        }
        return {true};
    }

    OperationStatus SqliteDicomDataMapper::insertSlice(uint series_uid, const DicomImage& slice) {
        return insertSlices(series_uid, QList{slice});
    }

    OperationStatus SqliteDicomDataMapper::insertSlice(QSqlDatabase& conn, uint series_uid, const DicomImage& slice) {
        return insertSlices(conn, series_uid, QList{slice});
    }

    OperationStatus SqliteDicomDataMapper::insertSlices(uint series_uid, const QList<DicomImage>& slices) {
        if (_db == nullptr) {
            return {.success = false, .error_code = DB_NOT_SETTED, .error_message = "database pointer is nullptr"};
        }
        auto conn_res = _db->getConnection();
        if (!conn_res.status.success) {
            return conn_res.status;
        }
        auto conn = conn_res.data;
        conn.transaction();
        auto res = insertSlices(conn, series_uid, slices);
        if (!res.success) {
            conn.rollback();
        } else {
            conn.commit();
        }
        return res;
    }

    OperationStatus SqliteDicomDataMapper::insertSlices(QSqlDatabase& conn,
                                                        uint series_uid,
                                                        const QList<DicomImage>& slices) {
        QSqlQuery query(conn);
        auto query_str = DicomDataBase::sql_slices_insert_many_vals(slices.size());
        query.prepare(query_str);
        std::ranges::for_each(slices, [&query, series_uid](const DicomImage& slice) {
            query.addBindValue(slice.getImageFilePath().toStdString().c_str());
            query.addBindValue(series_uid);
        });

        if (!query.exec()) {
            auto error = query.lastError();
            return {.success = false,
                    .error_code = static_cast<unsigned int>(error.type()),
                    .error_message = std::format("insertSlices with series uid - {},  error: {}",
                                                 series_uid,
                                                 error.text().toStdString())};
        }
        return {true};
    }
}    //namespace cadsi_lib::dicom
