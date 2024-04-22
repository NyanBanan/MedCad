//
// Created by nyanbanan on 16.04.2024.
//

#include "DICOMPatientMetaDataTableModelObject.hpp"


    DICOMPatientMetaDataTableModelObject::DICOMPatientMetaDataTableModelObject(const cadsi_lib::dicom::DicomPatient& patient)
        : _patient(patient) {}

    DICOMPatientMetaDataTableModelObject::DICOMPatientMetaDataTableModelObject(cadsi_lib::dicom::DicomPatient&& patient)
        : _patient(patient) {}

    const cadsi_lib::dicom::DicomPatient& DICOMPatientMetaDataTableModelObject::getPatient() const {
        return _patient;
    }

    QPushButton* DICOMPatientMetaDataTableModelObject::getDelButton() const {
        return _del_button;
    }

