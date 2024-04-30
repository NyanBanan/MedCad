//
// Created by nyanbanan on 28.04.2024.
//

#include "DICOMData.hpp"

void DICOMData::setData(const QList<cadsi_lib::dicom::DicomPatient>& new_data) {
    auto old_data = _dicom_data;
    emit dataUpdated(old_data, new_data);
    _dicom_data = new_data;
}

uint DICOMData::patientNum() {
    return _dicom_data.size();
}

uint DICOMData::getSeriesNum(int patient_ind) {
    return getPatient(patient_ind).numOfSeries();
}

const cadsi_lib::dicom::DicomPatient& DICOMData::getPatient(int patient_ind) {
    if (patient_ind >= _dicom_data.size() || patient_ind < 0) {
        return _null_patient;
    }
    return _dicom_data[patient_ind];
}

uint DICOMData::getImagesNum(int patient_ind, int series_ind) {
    return getSeries(patient_ind, series_ind).numOfImages();
}

const cadsi_lib::dicom::DicomSeries& DICOMData::getSeries(int patient_ind, int series_ind) {
    auto& patient = getPatient(patient_ind);
    auto& series_collection = patient.getSeries();
    if (series_ind >= series_collection.size() || series_ind < 0) {
        return _null_series;
    }
    return series_collection[series_ind];
}

const cadsi_lib::dicom::DicomImage& DICOMData::getImage(int patient_ind, int series_ind, int image_ind) {
    auto& series = getSeries(patient_ind, series_ind);
    auto& images_collection = series.getImages();
    if (image_ind >= images_collection.size() || image_ind < 0) {
        return _null_image;
    }
    return images_collection[image_ind];
}
