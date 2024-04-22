//
// Created by nyanbanan on 16.04.2024.
//

#ifndef CADSI_DICOMPATIENTMETADATATABLEMODELOBJECT_HPP
#define CADSI_DICOMPATIENTMETADATATABLEMODELOBJECT_HPP

#include <QPushButton>
#include <cadsi_lib/dicom/DicomPatient.hpp>

    class DICOMPatientMetaDataTableModelObject {
    public:
        DICOMPatientMetaDataTableModelObject(const cadsi_lib::dicom::DicomPatient& patient);
        DICOMPatientMetaDataTableModelObject(cadsi_lib::dicom::DicomPatient&& patient);

        [[nodiscard]] const cadsi_lib::dicom::DicomPatient& getPatient() const;
        [[nodiscard]] QPushButton* getDelButton() const;

    private:
        cadsi_lib::dicom::DicomPatient _patient;
        QPushButton* _del_button;
    };


#endif    //CADSI_DICOMPATIENTMETADATATABLEMODELOBJECT_HPP
