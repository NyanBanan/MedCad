//
// Created by nyanbanan on 13.04.2024.
//

#ifndef CADSI_DICOMPATIENT_HPP
#define CADSI_DICOMPATIENT_HPP
#include <QDate>
#include <QString>

#include "DicomSeries.hpp"
#include "DicomMetaDataHashCollection.hpp"

namespace cadsi_lib::dicom {
    class DicomPatient : public DicomMetaDataHashCollection {
    public:
        DicomPatient() = default;
        DicomPatient(const QString& uid,
                     const QString& name,
                     const QString& sex,
                     const QDate& birthDate,
                     const QString& comments);
        DicomPatient(QString&& uid, QString&& name, QString&& sex, QDate&& birthDate, QString&& comments);

        [[nodiscard]] QString getId() const;
        void setUid(const QString& uid);
        void setId(QString&& id);
        void setUid(const vtkDICOMValue& uid);
        void setUid(vtkDICOMValue&& uid);
        [[nodiscard]] QString getName() const;
        void setName(const QString& name);
        void setName(QString&& name);
        void setName(const vtkDICOMValue& name);
        void setName(vtkDICOMValue&& name);
        [[nodiscard]] QString getSex() const;
        void setSex(const QString& sex);
        void setSex(QString&& sex);
        void setSex(const vtkDICOMValue& sex);
        void setSex(vtkDICOMValue&& sex);
        [[nodiscard]] QDate getBirthDate() const;
        [[nodiscard]] QString getBirthDateDicomString() const;
        [[nodiscard]] QString getBirthDateBySlashString() const;
        void setBirthDate(const QDate& birthDate);
        void setBirthDate(QDate&& birthDate);
        void setBirthDate(const QString& birthDateDicomStr);
        void setBirthDate(QString&& birthDateDicomStr);
        void setBirthDate(const vtkDICOMValue& birthDate);
        void setBirthDate(vtkDICOMValue&& birthDate);
        [[nodiscard]] QString getComments() const;
        void setComments(const QString& comments);
        void setComments(QString&& comments);
        void setComments(const vtkDICOMValue& comments);
        void setComments(vtkDICOMValue&& comments);
        [[nodiscard]] QList<DicomSeries> getSeries() const;
        void addSeries(const QList<DicomSeries>& series);
        void addSeries(QList<DicomSeries>&& series);
        void addSeries(const DicomSeries& series);
        void addSeries(DicomSeries&& series);
        void reserveSeries(qsizetype size);
        qsizetype numOfSeries() const;
        qsizetype numOfImages() const;

        template<typename... Args>
        DicomSeries& emplaceBackSeries(Args... args) {
            return _series.emplaceBack(std::forward<Args>(args)...);
        }

    private:
        QList<DicomSeries> _series;
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_DICOMPATIENT_HPP
