//
// Created by nyanbanan on 13.04.2024.
//

#include "cadsi_lib/dicom/DicomPatient.hpp"

#include <utility>

namespace cadsi_lib::dicom {

    DicomPatient::DicomPatient(const QString& uid,
                               const QString& name,
                               const QString& sex,
                               const QDate& birthDate,
                               const QString& comments) {
        setUid(uid);
        setName(name);
        setSex(sex);
        setBirthDate(birthDate);
        setComments(comments);
    }

    DicomPatient::DicomPatient(QString&& uid, QString&& name, QString&& sex, QDate&& birthDate, QString&& comments) {
        setUid(uid);
        setName(name);
        setSex(sex);
        setBirthDate(birthDate);
        setComments(comments);
    }

    QString DicomPatient::getId() const {
        return QString::fromStdString(getMeta(DC::PatientID).getValue().AsString());
    }

    void DicomPatient::setUid(const QString& uid) {
        vtkDICOMValue val{vtkDICOMVR::LO, uid.toStdString()};
        setUid(val);
    }

    void DicomPatient::setId(QString&& id) {
        vtkDICOMValue val{vtkDICOMVR::LO, id.toStdString()};
        setUid(val);
    }

    void DicomPatient::setUid(const vtkDICOMValue& uid) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientID);
        setMeta(dict_entry, uid);
    }

    void DicomPatient::setUid(vtkDICOMValue&& uid) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientID);
        setMeta(dict_entry, uid);
    }

    QString DicomPatient::getName() const {
        return QString::fromStdString(getMeta(DC::PatientName).getValue().AsString());
    }

    void DicomPatient::setName(const QString& name) {
        vtkDICOMValue val{vtkDICOMVR::PN, name.toStdString()};
        setName(val);
    }

    void DicomPatient::setName(QString&& name) {
        vtkDICOMValue val{vtkDICOMVR::PN, name.toStdString()};
        setName(val);
    }

    void DicomPatient::setName(const vtkDICOMValue& name) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientName);
        setMeta(dict_entry, name);
    }

    void DicomPatient::setName(vtkDICOMValue&& name) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientName);
        setMeta(dict_entry, name);
    }

    QString DicomPatient::getSex() const {
        return QString::fromStdString(getMeta(DC::PatientSex).getValue().AsString());
    }

    void DicomPatient::setSex(const QString& sex) {
        vtkDICOMValue val{vtkDICOMVR::CS, sex.toStdString()};
        setSex(val);
    }

    void DicomPatient::setSex(QString&& sex) {
        vtkDICOMValue val{vtkDICOMVR::CS, sex.toStdString()};
        setSex(val);
    }

    void DicomPatient::setSex(const vtkDICOMValue& sex) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientSex);
        setMeta(dict_entry, sex);
    }

    void DicomPatient::setSex(vtkDICOMValue&& sex) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientSex);
        setMeta(dict_entry, sex);
    }

    QDate DicomPatient::getBirthDate() const {
        return QDate::fromString(getBirthDateDicomString(), "yyyyMMdd");
    }

    QString DicomPatient::getBirthDateDicomString() const {
        return QString::fromStdString(getMeta(DC::PatientBirthDate).getValue().AsString());
    }

    QString DicomPatient::getBirthDateBySlashString() const {
        return getBirthDate().toString("yyyy/MM/dd");
    }

    void DicomPatient::setBirthDate(const QDate& birthDate) {
        setBirthDate(std::move(birthDate.toString("yyyyMMdd")));
    }

    void DicomPatient::setBirthDate(QDate&& birthDate) {
        setBirthDate(std::move(birthDate.toString("yyyyMMdd")));
    }

    void DicomPatient::setBirthDate(const QString& birthDateDicomStr) {
        vtkDICOMValue val{vtkDICOMVR::DA, birthDateDicomStr.toStdString()};
        setBirthDate(std::move(val));
    }

    void DicomPatient::setBirthDate(QString&& birthDateDicomStr) {
        vtkDICOMValue val{vtkDICOMVR::DA, birthDateDicomStr.toStdString()};
        setBirthDate(std::move(val));
    }

    void DicomPatient::setBirthDate(const vtkDICOMValue& birthDate) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientBirthDate);
        setMeta(dict_entry, birthDate);
    }

    void DicomPatient::setBirthDate(vtkDICOMValue&& birthDate) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientBirthDate);
        setMeta(dict_entry, birthDate);
    }

    QString DicomPatient::getComments() const {
        return QString::fromStdString(getMeta(DC::PatientComments).getValue().AsString());
    }

    void DicomPatient::setComments(const QString& comments) {
        vtkDICOMValue val{vtkDICOMVR::LT, comments.toStdString()};
        setComments(val);
    }

    void DicomPatient::setComments(QString&& comments) {
        vtkDICOMValue val{vtkDICOMVR::LT, comments.toStdString()};
        setComments(val);
    }

    void DicomPatient::setComments(const vtkDICOMValue& comments) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientComments);
        setMeta(dict_entry, comments);
    }

    void DicomPatient::setComments(vtkDICOMValue&& comments) {
        auto dict_entry = vtkDICOMDictionary::FindDictEntry(DC::PatientComments);
        setMeta(dict_entry, comments);
    }

    const QList<DicomSeries>& DicomPatient::getSeries() const {
        return _series;
    }

    void DicomPatient::addSeries(const DicomSeries& series) {
        _series.push_back(series);
    }

    void DicomPatient::addSeries(const QList<DicomSeries>& series) {
        _series.append(series);
    }

    void DicomPatient::addSeries(QList<DicomSeries>&& series) {
        _series.append(series);
    }

    void DicomPatient::addSeries(DicomSeries&& series) {
        _series.push_back(series);
    }

    void DicomPatient::reserveSeries(qsizetype size) {
        _series.reserve(size);
    }

    qsizetype DicomPatient::numOfSeries() const {
        return _series.size();
    }

    qsizetype DicomPatient::numOfImages() const {
        auto a =
            std::accumulate(_series.begin(), _series.end(), qsizetype{0}, [](const qsizetype& a, const DicomSeries& b) {
                auto bc = b.numOfImages();
                return a + bc;
            });
        return a;
    }
}    //namespace cadsi_lib::dicom
