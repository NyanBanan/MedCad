//
// Created by nyanbanan on 13.04.2024.
//

#ifndef CADSI_DICOMSERIES_HPP
#define CADSI_DICOMSERIES_HPP

#include <QDate>
#include <QList>
#include <QTime>

#include "DicomImage.hpp"
#include "DicomMetaDataHashCollection.hpp"

namespace cadsi_lib::dicom {
    class DicomSeries : public DicomMetaDataHashCollection {
    public:
        DicomSeries() = default;
        DicomSeries(const QString& uid,
                    const QDate& date,
                    const QTime& time,
                    const QString& description,
                    const QString& modality,
                    const QString& institutionName);
        DicomSeries(QString&& uid,
                    QDate&& date,
                    QTime&& time,
                    QString&& description,
                    QString&& modality,
                    QString&& institutionName);

        [[nodiscard]] QString getUid() const;
        void setUid(const QString& uid);
        void setUid(QString&& uid);
        void setUid(const vtkDICOMValue& uid);
        void setUid(vtkDICOMValue&& uid);
        [[nodiscard]] QDate getDate() const;
        [[nodiscard]] QString getDateString() const;
        void setDate(const QDate& date);
        void setDate(QDate&& date);
        void setDate(const vtkDICOMValue& date);
        void setDate(vtkDICOMValue&& date);
        [[nodiscard]] QTime getTime() const;
        [[nodiscard]] QString getTimeString() const;
        void setTime(const QTime& time);
        void setTime(QTime&& time);
        void setTime(const vtkDICOMValue& time);
        void setTime(vtkDICOMValue&& time);
        [[nodiscard]] QString getDescription() const;
        void setDescription(const QString& description);
        void setDescription(QString&& description);
        void setDescription(const vtkDICOMValue& description);
        void setDescription(vtkDICOMValue&& description);
        [[nodiscard]] QString getModality() const;
        void setModality(const QString& modality);
        void setModality(QString&& modality);
        void setModality(const vtkDICOMValue& modality);
        void setModality(vtkDICOMValue&& modality);
        [[nodiscard]] QString getInstitutionName() const;
        void setInstitutionName(const QString& institutionName);
        void setInstitutionName(QString&& institutionName);
        void setInstitutionName(const vtkDICOMValue& institutionName);
        void setInstitutionName(vtkDICOMValue&& institutionName);
        [[nodiscard]] QList<DicomImage> getImages() const;
        void assignImages(QList<DicomImage> images);
        void addImage(const DicomImage& image);
        void addImage(DicomImage&& image);
        void reserveImages(qsizetype size);
        [[nodiscard]] qsizetype numOfImages() const;

        template<typename... Args>
        DicomImage& emplaceBackImage(Args... args) {
            return _images.emplaceBack(std::forward<Args>(args)...);
        }

    private:
        QHash<vtkDICOMTag, vtkDICOMDataElement> _series_meta;
        //TODO: maybe add preview array
        QList<DicomImage> _images;
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_DICOMSERIES_HPP
