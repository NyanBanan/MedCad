//
// Created by nyanbanan on 23.04.2024.
//

#ifndef CADSI_DICOMFROMFILESTOSQLMAPPER_HPP
#define CADSI_DICOMFROMFILESTOSQLMAPPER_HPP

#include <QObject>
#include <cadsi_lib/dicom/DicomDataBase.hpp>
#include <cadsi_lib/dicom/DicomSqlTablesInspector.hpp>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>

class DICOMFromFilesToSqlMapper : public QObject {
    Q_OBJECT
public:
    DICOMFromFilesToSqlMapper(QObject* parent = nullptr);

    void setDataBaseFile(const QString& db_path);
    void setDicomDir(const QString& dicom_dir);
public slots:
    void loadToDataBase();
    void loadFromSql();
signals:
    void error(const QString& error_message);
    void updatedData(QList<cadsi_lib::dicom::DicomPatient> patients);
    void finished();
private:
    void updateConnection();

    bool _connection_need_update{false};
    QString _db_file_path{};
    QString _dicom_dir{};
    cadsi_lib::dicom::SqliteDicomDataBase _db;
    cadsi_lib::dicom::SqliteDicomDataMapper _db_mapper;
};

#endif    //CADSI_DICOMFROMFILESTOSQLMAPPER_HPP
