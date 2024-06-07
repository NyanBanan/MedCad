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
        return QString::fromStdString(getMeta(DC::SeriesInstanceUID).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesInstanceUID);
        setMeta(dict_entry, uid);
    }

    void DicomSeries::setUid(vtkDICOMValue&& uid) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesInstanceUID);
        setMeta(dict_entry, uid);
    }

    QDate DicomSeries::getDate() const {
        return QDate::fromString(QString::fromStdString(getMeta(DC::SeriesDate).getValue().AsString()), "yyyyMMdd");
    }

    QString DicomSeries::getDateString() const {
        return QString::fromStdString(getMeta(DC::SeriesDate).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesDate);
        setMeta(dict_entry, date);
    }

    void DicomSeries::setDate(vtkDICOMValue&& date) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesDate);
        setMeta(dict_entry, date);
    }

    QTime DicomSeries::getTime() const {
        return QTime::fromString(QString::fromStdString(getMeta(DC::SeriesTime).getValue().AsString()), "hhmmss");
    }

    QString DicomSeries::getTimeString() const {
        return QString::fromStdString(getMeta(DC::SeriesTime).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesTime);
        setMeta(dict_entry, time);
    }

    void DicomSeries::setTime(vtkDICOMValue&& time) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesTime);
        setMeta(dict_entry, time);
    }

    QString DicomSeries::getDescription() const {
        return QString::fromStdString(getMeta(DC::SeriesDescription).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesDescription);
        setMeta(dict_entry, description);
    }

    void DicomSeries::setDescription(vtkDICOMValue&& description) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::SeriesDescription);
        setMeta(dict_entry, description);
    }

    QString DicomSeries::getModality() const {
        return QString::fromStdString(getMeta(DC::Modality).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::Modality);
        setMeta(dict_entry, modality);
    }

    void DicomSeries::setModality(vtkDICOMValue&& modality) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::Modality);
        setMeta(dict_entry, modality);
    }

    QString DicomSeries::getInstitutionName() const {
        return QString::fromStdString(getMeta(DC::InstitutionName).getValue().AsString());
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
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::InstitutionName);
        setMeta(dict_entry, institutionName);
    }

    void DicomSeries::setInstitutionName(vtkDICOMValue&& institutionName) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::InstitutionName);
        setMeta(dict_entry, institutionName);
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

    void DicomSeries::parseMetaData(vtkDICOMMetaData* meta) {
        for (auto iter = meta->Begin(); iter != meta->End(); ++iter) {
            auto dict_entry = meta->FindDictEntry(iter->GetTag());
            if (iter->IsPerInstance()) {
                auto instance_num = iter->GetNumberOfInstances();
                if (_images.size() < instance_num) {
                    instance_num = (int)_images.size();
                }
                for (auto inst : std::views::iota(0, instance_num)) {
                    _images[inst].setMeta(dict_entry, iter->GetValue(inst));
                }
            } else {
                setMeta(dict_entry, iter->GetValue());
            }
        }
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
