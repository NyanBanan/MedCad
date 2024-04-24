//
// Created by nyanbanan on 23.04.2024.
//

#ifndef CADSI_DICOMSQLTABLESINSPECTOR_HPP
#define CADSI_DICOMSQLTABLESINSPECTOR_HPP

#include "SqliteDicomDataBase.hpp"

namespace cadsi_lib::dicom {
    class DicomSqlTablesInspector {
    public:
        OperationStatus checkAndCreateTables(const DicomDataBase& db);
    private:
        bool checkTablesExists(const QSqlDatabase& conn);
        OperationStatus createTables(const QSqlDatabase& conn);
    };
}
#endif    //CADSI_DICOMSQLTABLESINSPECTOR_HPP
