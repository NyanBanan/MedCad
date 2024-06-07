//
// Created by nyanbanan on 28.04.2024.
//

#ifndef CADSI_DICOMDATA_HPP
#define CADSI_DICOMDATA_HPP

#include <QObject>

#include "cadsi_app/dicom/CadsiLibDicomDeclareMetatype.hpp"
#include "cadsi_lib/include/cadsi_lib/dicom/DicomPatient.hpp"

class DICOMData : public QObject {
    Q_OBJECT
public:
    const cadsi_lib::dicom::DicomImage& getImage(int patient_ind, int series_ind, int image_ind);
    const cadsi_lib::dicom::DicomSeries& getSeries(int patient_ind, int series_ind);
    const cadsi_lib::dicom::DicomPatient& getPatient(int patient_ind);
    uint patientNum();
    uint getSeriesNum(int patient_ind);
    uint getImagesNum(int patient_ind, int series_ind);
public slots:
    void setData(const QList<cadsi_lib::dicom::DicomPatient>& new_data);
signals:
    void dataUpdated(const QList<cadsi_lib::dicom::DicomPatient>& old_data, const QList<cadsi_lib::dicom::DicomPatient>& new_data);

private:
    QList<cadsi_lib::dicom::DicomPatient> _dicom_data{};

    cadsi_lib::dicom::DicomPatient _null_patient{};
    cadsi_lib::dicom::DicomSeries _null_series{};
    cadsi_lib::dicom::DicomImage _null_image{};
};

#endif    //CADSI_DICOMDATA_HPP
