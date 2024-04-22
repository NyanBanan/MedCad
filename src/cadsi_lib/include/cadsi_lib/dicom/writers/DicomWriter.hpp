//
// Created by nyanbanan on 10.04.2024.
//

#ifndef CADSI_DICOMWRITER_HPP
#define CADSI_DICOMWRITER_HPP

#include "cadsi_lib/OperationStatus.hpp"
#include "cadsi_lib/dicom/DicomPatient.hpp"

namespace cadsi_lib::dicom::writers {
    class DicomWriter {
    public:
        virtual ~DicomWriter() = default;
        virtual OperationStatus insertPatients(const QList<DicomPatient>& patients) = 0;
    };

}    //namespace cadsi_lib::dicom::writers

#endif    //CADSI_DICOMWRITER_HPP
