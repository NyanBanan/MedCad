//
// Created by nyanbanan on 10.04.2024.
//

#ifndef CADSI_DICOMPROVIDER_HPP
#define CADSI_DICOMPROVIDER_HPP

#include "cadsi_lib/Result.hpp"
#include "cadsi_lib/dicom/DicomPatient.hpp"

namespace cadsi_lib::dicom::providers {
    class DicomProvider {
    public:
        virtual ~DicomProvider() = default;
        virtual Result<QList<DicomPatient>> getAllPatients() = 0;
    };
}    //namespace cadsi_lib::dicom::providers
#endif    //CADSI_DICOMPROVIDER_HPP
