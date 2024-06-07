//
// Created by nyanbanan on 19.04.2024.
//

#include <QStringDecoder>
#include <cadsi_lib/dicom/SqliteDicomDataBase.hpp>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>
#include <vtkDICOMDictionary.h>

#include "cadsi_lib/dicom/DicomSqlTablesInspector.hpp"

void printPatient(const cadsi_lib::dicom::DicomPatient& patient) {
    auto patients_meta = patient.getMetaCollection();
    for (const auto& curr_meta : patients_meta) {
        auto tag_data = vtkDICOMDictionary::FindDictEntry(curr_meta.getDictEntry().GetTag());
        if (tag_data.IsValid()) {
            std::cout << "Tag: " << tag_data.GetTag() << ", Attr: " << tag_data.GetName()
                      << ", Value: " << curr_meta.getValue().AsString() << ", VR: " << tag_data.GetVR().GetText()
                      << std::endl;
        }
    }
    auto series = patient.getSeries();
    for (const auto& curr_series : series) {
        auto curr_series_meta = curr_series.getMetaCollection();
        for (const auto& curr_meta : curr_series_meta) {
            auto tag_data = vtkDICOMDictionary::FindDictEntry(curr_meta.getDictEntry().GetTag());
            if (tag_data.IsValid()) {
                std::cout << "Tag: " << tag_data.GetTag() << ", Attr: " << tag_data.GetName()
                          << ", Value: " << curr_meta.getValue().AsString() << ", VR: " << tag_data.GetVR().GetText()
                          << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "usage: example_FilesystemAndSqlDicom \'path to dicom directory\'" << std::endl;
        return -1;
    }
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

    cadsi_lib::dicom::providers::FileDataDicomProvider file_data_provider;
    //Windows paths with russian symbols might cause problems. Dir may be recognized as not existing. That's why I decode input
    auto to_utf8 = QStringDecoder(QStringDecoder::System);
    auto result = file_data_provider.readDir(to_utf8(argv[1]), false);
    if (!result.status.success) {
        auto status = result.status;
        std::cout << status.error_code << " " << status.error_message << std::endl;
    }
    auto data = result.data;

    auto push_patients_res = data_mapper.insertPatients(data);
    if (!push_patients_res.success) {
        std::cout << push_patients_res.error_code << " " << push_patients_res.error_message << std::endl;
        return -1;
    }

    //now read wrote data
    auto all_patients_res = data_mapper.getAllPatients();
    if (!all_patients_res.status.success) {
        auto status = all_patients_res.status;
        std::cout << status.error_code << " " << status.error_message << std::endl;
        return -1;
    }

    auto all_patients = all_patients_res.data;

    for (const auto& patient : all_patients) {
        printPatient(patient);
    }
}
