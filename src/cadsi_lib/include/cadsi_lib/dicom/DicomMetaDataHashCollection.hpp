//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMMETADATAHASHCOLLECTION_HPP
#define CADSI_DICOMMETADATAHASHCOLLECTION_HPP

#include <QHash>

#include "DicomTagStdHashSpecialization.hpp"
#include "cadsiDicomDataElement.hpp"

namespace cadsi_lib::dicom {
    //TODO: Talk about private dictionaries and their additions
    class DicomMetaDataHashCollection {
    public:
        virtual ~DicomMetaDataHashCollection() = default;

        [[nodiscard]] const QHash<vtkDICOMTag, cadsiDicomDataElement>& getMetaCollection() const;
        [[nodiscard]] cadsiDicomDataElement getMeta(const vtkDICOMTag& tag) const;
        void setMeta(const cadsiDicomDataElement& data);
        void setMeta(cadsiDicomDataElement&& data);
        void setMeta(const vtkDICOMDictEntry& dictEntry, const vtkDICOMValue& value);

        void reserveMetaCollection(qsizetype size);
    private:
        QHash<vtkDICOMTag, cadsiDicomDataElement> _meta_collection;
    };
}
#endif    //CADSI_DICOMMETADATAHASHCOLLECTION_HPP
