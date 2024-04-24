//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_SQLITEDICOMDATABASE_HPP
#define CADSI_SQLITEDICOMDATABASE_HPP

#include "DicomDataBase.hpp"
#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/Result.hpp"

namespace cadsi_lib::dicom {
    class SqliteDicomDataBase : public DicomDataBase{
    public:
        /*!
	    \warning If an error happens error_code returned from QSqlError::ErrorTypes
         */
        OperationStatus createOrConnect(QString path) override;
        Result<QSqlDatabase> getConnection() const override;
    private:
        QSqlDatabase _connection;
    };
}
#endif    //CADSI_SQLITEDICOMDATABASE_HPP
