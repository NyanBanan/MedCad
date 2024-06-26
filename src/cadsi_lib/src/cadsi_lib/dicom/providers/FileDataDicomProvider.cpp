//
// Created by nyanbanan on 13.04.2024.
//

#include "cadsi_lib/dicom/providers/FileDataDicomProvider.hpp"

namespace cadsi_lib::dicom::providers {
    Result<QList<DicomPatient>> FileDataDicomProvider::getAllPatients() {
        return {.status{.success = true}, .data = _patients};
    }

    Result<QList<DicomPatient>> FileDataDicomProvider::readDir(const QString& dir_path, bool need_deep_search) {
        QFileInfo dir(dir_path);
        if (!dir.exists()) {
            return {false, cadsi_lib::file_data::ErrorCodes::FILE_NOT_EXIST};
        } else if (!dir.isDir()) {
            return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT};
        }
        vtkNew<vtkDICOMDirectory> dicomdir;
        dicomdir->SetDirectoryName(dir.absoluteFilePath().toStdString().c_str());
        if (need_deep_search) {
            dicomdir->SetScanDepth(countDepth(dir_path));
        }
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

                        DicomImageDataProvider provider;

                        auto res = provider.parseDicomFiles(images_files);

                        if (!res.success) {
                            return {.status = res, .data = {}};
                        }

                        auto image_data =
                            PreviewImage::generatePreviewImage(provider.getPatientMatrix(), provider.getOutputPort());

                        auto preview = PreviewImage::vtkImageDataToQImage(image_data);
                        curr_series.setPreview(std::move(preview));
                        curr_series.assignImages(images);

                        auto meta = provider.getMetaData();

                        curr_series.parseMetaData(meta);
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

    //TODO: Try remove recursion
    int FileDataDicomProvider::countDepth(const QString& dir_path) {
        QDir dir(dir_path);
        auto entry_dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        if (entry_dirs.isEmpty()) {
            return 1;
        }
        auto max_depth = 0;
        for (const auto& dir_name : entry_dirs) {
            auto count = countDepth(dir.absoluteFilePath(dir_name));
            if (count > max_depth) {
                max_depth = count + 1;
            }
        }
        return max_depth;
    }
}    //namespace cadsi_lib::dicom::providers
