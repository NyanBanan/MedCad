//
// Created by nyanbanan on 24.04.2024.
//

#ifndef CADSI_CADSILIBDICOMDECLAREMETATYPE_HPP
#define CADSI_CADSILIBDICOMDECLAREMETATYPE_HPP

#include <cadsi_lib/dicom/DicomPatient.hpp>
#include <QObject>

Q_DECLARE_METATYPE(cadsi_lib::dicom::DicomPatient)
Q_DECLARE_METATYPE(cadsi_lib::dicom::DicomSeries)
Q_DECLARE_METATYPE(cadsi_lib::dicom::DicomImage)

#endif    //CADSI_CADSILIBDICOMDECLAREMETATYPE_HPP
