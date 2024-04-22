//
// Created by nyanbanan on 13.04.2024.
//

#include "cadsi_lib/dicom/providers/FileDataDicomProvider.hpp"

#include "cadsi_lib/Result.hpp"

namespace cadsi_lib::dicom::providers {
    Result<QList<DicomPatient>> FileDataDicomProvider::getAllPatients() {
        return {.status{.success = true}, .data = _patients};
    }

    Result<QList<DicomPatient>> FileDataDicomProvider::readDir(const QString& dir_path) {
        QFileInfo dir(dir_path);
        if (!dir.exists()) {
            return {false, cadsi_lib::file_data::ErrorCodes::FILE_NOT_EXIST};
        } else if (!dir.isDir()) {
            return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT};
        }
        vtkNew<vtkDICOMDirectory> dicomdir;
        dicomdir->SetDirectoryName(dir.absoluteFilePath().toStdString().c_str());
        dicomdir->Update();

        int n = dicomdir->GetNumberOfPatients();
        _patients.clear();
        _patients.reserve(n);

        for (int patient_id = 0; patient_id < n; patient_id++) {
            auto& curr_patient = _patients.emplaceBack();

            auto curr_patient_record = dicomdir->GetPatientRecord(patient_id);

            auto studies_num = dicomdir->GetStudiesForPatient(patient_id);

            for (auto stud_num_iter = studies_num->Begin(); stud_num_iter != studies_num->End(); ++stud_num_iter) {
                auto study = dicomdir->GetStudyRecord(*stud_num_iter);
                int first_series_num = dicomdir->GetFirstSeriesForStudy(*stud_num_iter);
                int last_series_num = dicomdir->GetLastSeriesForStudy(*stud_num_iter);
                curr_patient.reserveSeries(last_series_num - first_series_num + 1);
                for (int series_num = first_series_num; series_num <= last_series_num; ++series_num) {
                    auto cur_series_record = dicomdir->GetSeriesRecord(series_num);

                    auto images_files = dicomdir->GetFileNamesForSeries(series_num);
                    auto num_of_images = images_files->GetNumberOfValues();

                    if (num_of_images > 0) {
                        auto& curr_series = curr_patient.emplaceBackSeries();
                        curr_series.reserveImages(num_of_images);

                        QList<DicomImage> images;

                        for (auto image_ind = 0; image_ind < num_of_images; ++image_ind) {
                            auto image_path = images_files->GetValue(image_ind).c_str();
                            auto curr_image = images.emplaceBack(image_path);
                        }

                        //Read metadata for series
                        vtkNew<vtkDICOMReader> series_data_reader;

                        series_data_reader->SetFileName(images_files->GetValue(0).c_str());
                        series_data_reader->Update();

                        createPreviewImage(series_data_reader);

                        auto meta = series_data_reader->GetMetaData();

                        for (auto iter = meta->Begin(); iter != meta->End(); ++iter) {
                            if (iter->IsPerInstance()) {
                                auto instance_num = iter->GetNumberOfInstances();
                                if (images.size() < instance_num) {
                                    instance_num = (int)images.size();
                                }
                                for (auto inst : std::views::iota(0, instance_num)) {
                                    images[inst].setMeta(*iter);
                                }
                            } else {
                                curr_series.setMeta(iter->GetTag(), iter->GetValue());
                            }
                        }

                        curr_series.assignImages(images);
                    }
                }
            }
            if (curr_patient.numOfSeries() != 0) {
                curr_patient.setName(curr_patient_record.Get(DC::PatientName));
                curr_patient.setUid(curr_patient_record.Get(DC::PatientID));
                curr_patient.setSex(curr_patient_record.Get(DC::PatientSex));
                curr_patient.setComments(curr_patient_record.Get(DC::PatientComments));
                curr_patient.setBirthDate(curr_patient_record.Get(DC::PatientBirthDate));
            } else {
                _patients.pop_back();
            }
        }
        return {true, 0, {}, _patients};
    }

    void FileDataDicomProvider::createPreviewImage(vtkDICOMReader* reader) {

    }
}    //namespace cadsi_lib::dicom::providers
