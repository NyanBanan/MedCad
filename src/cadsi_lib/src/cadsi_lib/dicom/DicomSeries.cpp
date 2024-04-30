//
// Created by nyanbanan on 13.04.2024.
//

#include "cadsi_lib/dicom/DicomSeries.hpp"

#include <utility>

namespace cadsi_lib::dicom {
    DicomSeries::DicomSeries(const QString& uid,
                             const QDate& date,
                             const QTime& time,
                             const QString& description,
                             const QString& modality,
                             const QString& institutionName) {
        setUid(uid);
        setDate(date);
        setTime(time);
        setDescription(description);
        setModality(modality);
        setInstitutionName(institutionName);
    }

    DicomSeries::DicomSeries(QString&& uid,
                             QDate&& date,
                             QTime&& time,
                             QString&& description,
                             QString&& modality,
                             QString&& institutionName) {
        setUid(uid);
        setDate(date);
        setTime(time);
        setDescription(description);
        setModality(modality);
        setInstitutionName(institutionName);
    }

    QString DicomSeries::getUid() const {
        return QString::fromStdString(getMeta(DC::SeriesInstanceUID).GetValue().AsString());
    }

    void DicomSeries::setUid(const QString& uid) {
        vtkDICOMValue val{vtkDICOMVR::UI, uid.toStdString()};
        setUid(val);
    }

    void DicomSeries::setUid(QString&& uid) {
        vtkDICOMValue val{vtkDICOMVR::UI, uid.toStdString()};
        setUid(val);
    }

    void DicomSeries::setUid(const vtkDICOMValue& uid) {
        vtkDICOMDataElement data_elem(DC::SeriesInstanceUID, uid);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setUid(vtkDICOMValue&& uid) {
        vtkDICOMDataElement data_elem(DC::SeriesInstanceUID, uid);
        setMeta(std::move(data_elem));
    }

    QDate DicomSeries::getDate() const {
        return QDate::fromString(QString::fromStdString(getMeta(DC::SeriesDate).GetValue().AsString()), "yyyyMMdd");
    }

    QString DicomSeries::getDateString() const {
        return QString::fromStdString(getMeta(DC::SeriesDate).GetValue().AsString());
    }

    void DicomSeries::setDate(const QDate& date) {
        vtkDICOMValue val{vtkDICOMVR::DA, date.toString("yyyyMMdd").toStdString()};
        setDate(val);
    }

    void DicomSeries::setDate(QDate&& date) {
        vtkDICOMValue val{vtkDICOMVR::DA, date.toString("yyyyMMdd").toStdString()};
        setDate(val);
    }

    void DicomSeries::setDate(const vtkDICOMValue& date) {
        vtkDICOMDataElement data_elem(DC::SeriesDate, date);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setDate(vtkDICOMValue&& date) {
        vtkDICOMDataElement data_elem(DC::SeriesDate, date);
        setMeta(std::move(data_elem));
    }

    QTime DicomSeries::getTime() const {
        return QTime::fromString(QString::fromStdString(getMeta(DC::SeriesTime).GetValue().AsString()), "hhmmss");
    }

    QString DicomSeries::getTimeString() const {
        return QString::fromStdString(getMeta(DC::SeriesTime).GetValue().AsString());
    }

    void DicomSeries::setTime(const QTime& time) {
        vtkDICOMValue val{vtkDICOMVR::TM, time.toString("hhmmss").toStdString()};
        setTime(val);
    }

    void DicomSeries::setTime(QTime&& time) {
        vtkDICOMValue val{vtkDICOMVR::TM, time.toString("hhmmss").toStdString()};
        setTime(val);
    }

    void DicomSeries::setTime(const vtkDICOMValue& time) {
        vtkDICOMDataElement data_elem(DC::SeriesTime, time);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setTime(vtkDICOMValue&& time) {
        vtkDICOMDataElement data_elem(DC::SeriesTime, time);
        setMeta(std::move(data_elem));
    }

    QString DicomSeries::getDescription() const {
        return QString::fromStdString(getMeta(DC::SeriesDescription).GetValue().AsString());
    }

    void DicomSeries::setDescription(const QString& description) {
        vtkDICOMValue val{vtkDICOMVR::LO, description.toStdString()};
        setDescription(val);
    }

    void DicomSeries::setDescription(QString&& description) {
        vtkDICOMValue val{vtkDICOMVR::LO, description.toStdString()};
        setDescription(val);
    }

    void DicomSeries::setDescription(const vtkDICOMValue& description) {
        vtkDICOMDataElement data_elem(DC::SeriesDescription, description);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setDescription(vtkDICOMValue&& description) {
        vtkDICOMDataElement data_elem(DC::SeriesDescription, description);
        setMeta(std::move(data_elem));
    }

    QString DicomSeries::getModality() const {
        return QString::fromStdString(getMeta(DC::Modality).GetValue().AsString());
    }

    void DicomSeries::setModality(const QString& modality) {
        vtkDICOMValue val{vtkDICOMVR::CS, modality.toStdString()};
        setModality(val);
    }

    void DicomSeries::setModality(QString&& modality) {
        vtkDICOMValue val{vtkDICOMVR::CS, modality.toStdString()};
        setModality(val);
    }

    void DicomSeries::setModality(const vtkDICOMValue& modality) {
        vtkDICOMDataElement data_elem(DC::Modality, modality);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setModality(vtkDICOMValue&& modality) {
        vtkDICOMDataElement data_elem(DC::Modality, modality);
        setMeta(std::move(data_elem));
    }

    QString DicomSeries::getInstitutionName() const {
        return QString::fromStdString(getMeta(DC::InstitutionName).GetValue().AsString());
    }

    void DicomSeries::setInstitutionName(const QString& institutionName) {
        vtkDICOMValue val{vtkDICOMVR::LO, institutionName.toStdString()};
        setInstitutionName(val);
    }

    void DicomSeries::setInstitutionName(QString&& institutionName) {
        vtkDICOMValue val{vtkDICOMVR::LO, institutionName.toStdString()};
        setInstitutionName(val);
    }

    void DicomSeries::setInstitutionName(const vtkDICOMValue& institutionName) {
        vtkDICOMDataElement data_elem(DC::InstitutionName, institutionName);
        setMeta(std::move(data_elem));
    }

    void DicomSeries::setInstitutionName(vtkDICOMValue&& institutionName) {
        vtkDICOMDataElement data_elem(DC::InstitutionName, institutionName);
        setMeta(std::move(data_elem));
    }

    QImage DicomSeries::getPreview() const {
        return _preview_image;
    }

    void DicomSeries::setPreview(const QImage& preview_image) {
        _preview_image = preview_image;
    }

    void DicomSeries::setPreview(QImage&& preview_image) {
        _preview_image = preview_image;
    }

    void DicomSeries::assignImages(QList<DicomImage> images) {
        _images.assign(images.begin(), images.end());
    }

    const QList<DicomImage>& DicomSeries::getImages() const {
        return _images;
    }

    void DicomSeries::addImage(const DicomImage& image) {
        _images.push_back(image);
    }

    void DicomSeries::addImage(DicomImage&& image) {
        _images.push_back(image);
    }

    void DicomSeries::reserveImages(qsizetype size) {
        _images.reserve(size);
    }

    qsizetype DicomSeries::numOfImages() const {
        return _images.size();
    }
}    //namespace cadsi_lib::dicom
