//
// Created by nyanbanan on 16.04.2024.
//

#include <cadsi_lib/dicom/SqliteDicomDataBase.hpp>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>

#include <cadsi_lib/dicom/DicomSqlTablesInspector.hpp>

int main(int argc, char* argv[]) {
    //SqliteDicomDataBase provide functions for database connection and structure validation
    cadsi_lib::dicom::SqliteDicomDataBase db;
    //Create or connect to database file
    auto create_db_res = db.createOrConnect("./testdb.db");
    if (!create_db_res.success) {
        std::cout << create_db_res.error_code << " " << create_db_res.error_message << std::endl;
        return -1;
    }
    //Check db structure for our needs
    cadsi_lib::dicom::DicomSqlTablesInspector insp;
    auto create_tables_res = insp.checkAndCreateTables(db);
    if (!create_tables_res.success) {
        std::cout << create_tables_res.error_code << " " << create_tables_res.error_message << std::endl;
        return -1;
    }

    cadsi_lib::dicom::SqliteDicomDataMapper data_mapper;
    //set to data mapper db connection
    data_mapper.setDataBase(&db);
    //Push random patient to a database
    auto push_rand_patient_res = data_mapper.insertPatient({"Amogus", "Petr", "M", QDate(1970, 01, 01), "No Comments"});
    if (!push_rand_patient_res.success) {
        std::cout << push_rand_patient_res.error_code << " " << push_rand_patient_res.error_message << std::endl;
        return -1;
    }
    //TODO: Continue example
}
