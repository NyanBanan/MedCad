//
// Created by nyanbanan on 09.04.2024.
//

#include "DICOMDatabaseDialog.hpp"

DICOMDatabaseDialog::DICOMDatabaseDialog(QWidget* parent) : QDialog(parent) {
        _ui.setupUi(this);
        cadsi_lib::dicom::SqliteDicomDataMapper map;
        cadsi_lib::dicom::providers::FileDataDicomProvider provider;
        auto data = provider.readDir("C:/Users/moksh/OneDrive/Рабочий стол/Dicoms/dicom/AN11F1967");
        auto patient_data = data.data;
        auto patient_model = new DICOMPatientMetaDataTableModel;
        for(auto i = 0; i < 100; ++i) {
            patient_model->pushBack(patient_data[0]);
        }
        _ui.tableViewPatients->setModel(patient_model);
//        auto patient_delegate = new DICOMPatientMetaDataTableDelegate;
//        _ui.tableViewPatients->setItemDelegate(patient_delegate);
        auto series_data = patient_data[0].getSeries();
        auto model = new DICOMImageMetaDataTableModel;
        for (const auto& curr_series : series_data) {
            auto curr_series_meta = curr_series.getMetaCollection();
            for (const auto& curr_meta : curr_series_meta) {
                model->pushBack(DICOMImageMetaDataTableModelObject::fromDicomDataElement(curr_meta));
            }
        }
        _ui.seriesDataTableView->setModel(model);
        _ui.seriesDataTableView->update();
    }