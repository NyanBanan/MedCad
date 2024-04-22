//
// Created by nyanbanan on 13.04.2024.
//
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>
#include <iostream>
#include <vtkDICOMDictionary.h>

int main(int argc, char* argv[]) {
    cadsi_lib::dicom::providers::FileDataDicomProvider provider;
    auto result = provider.readDir("C:/Users/moksh/OneDrive/Рабочий стол/Dicoms/dicom/AN14F1981");
    if (!result.status.success) {
        auto status = result.status;
        std::cout << status.error_code << " " << status.error_message << std::endl;
    }
    auto data = result.data;

    for (const auto& patient : data) {
        auto patients_meta = patient.getMetaCollection();
        for (const auto& meta : patients_meta) {
            std::cout << meta.GetTag() << " " << meta.GetValue() << std::endl;
        }
        auto series = patient.getSeries();
        for (const auto& curr_series : series) {
            auto curr_series_meta = curr_series.getMetaCollection();
            for (const auto& curr_meta : curr_series_meta) {
                auto tag_data = vtkDICOMDictionary::FindDictEntry(curr_meta.GetTag());
                if (tag_data.IsValid()) {
                    std::cout << "Tag: " << tag_data.GetTag() << ", Attr: " << tag_data.GetName() << ", Value: "
                              << curr_meta.GetValue().AsString() << ", VR: " << tag_data.GetVR().GetText()
                              << std::endl;
                }
            }
        }
    }
}
