//
// Created by nyanbanan on 10.04.2024.
//

#ifndef CADSI_SQLITEDICOMDATAMAPPER_HPP
#define CADSI_SQLITEDICOMDATAMAPPER_HPP

#include <QSqlDatabase>
#include <QSqlRecord>
#include <qbuffer.h>
#include <ranges>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMReader.h>
#include <vtkNew.h>
#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include "SqliteDicomDataBase.hpp"
#include "providers/DicomProvider.hpp"
#include "writers/DicomWriter.hpp"

namespace cadsi_lib::dicom {
    class SqliteDicomDataMapper : public providers::DicomProvider,
                                  writers::DicomWriter {
    public:
        enum ErrorCodes {
            DB_NOT_SETTED
        };

        void setDataBase(DicomDataBase* db);
        Result<QList<DicomPatient>> getAllPatients() override;
        /*!
         \brief methods with QSqlDatabase& conn parameter are necessary to reduce number of calls _db->getConnection() and success checkouts of this call
        */
        OperationStatus insertPatients(const QList<DicomPatient>& patients) override;
        OperationStatus insertPatient(const DicomPatient& patient);
        OperationStatus insertSeries(uint patient_uid, const DicomSeries& series);
        OperationStatus insertSeries(uint patient_uid, const QList<DicomSeries>& series);
        OperationStatus insertSlice(uint series_uid, const DicomImage& slice);
        OperationStatus insertSlices(uint series_uid, const QList<DicomImage>& slices);

        OperationStatus deletePatients(QList<QString> patients_uid) override;
        OperationStatus deleteSeries(QList<QString> series_uid) override;

    private:
        /*!
         \brief methods with QSqlDatabase& conn parameter are necessary to reduce number of calls _db->getConnection() and success checkouts of this call
        */

        Result<QList<DicomSeries>> selectAllSeriesForPatient(QSqlDatabase& conn, uint patient_uid);
        /*!
         \warning function return images without dicom metadata. If you need them parse image file manually or use selectAllSeriesForPatient or getAllPatients
         */
        Result<QList<DicomImage>> selectAllSlicesForSeries(QSqlDatabase& conn, uint series_uid);

        OperationStatus insertPatients(QSqlDatabase& conn, const QList<DicomPatient>& patients);
        OperationStatus insertPatient(QSqlDatabase& conn, const DicomPatient& patient);
        OperationStatus insertSeries(QSqlDatabase& conn, uint patient_uid, const DicomSeries& series);
        OperationStatus insertSeries(QSqlDatabase& conn, uint patient_uid, const QList<DicomSeries>& series);
        OperationStatus insertSlice(QSqlDatabase& conn, uint series_uid, const DicomImage& slice);
        OperationStatus insertSlices(QSqlDatabase& conn, uint series_uid, const QList<DicomImage>& slices);

        DicomDataBase* _db{nullptr};
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_SQLITEDICOMDATAMAPPER_HPP
