//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMMETADATAHASHCOLLECTION_HPP
#define CADSI_DICOMMETADATAHASHCOLLECTION_HPP

#include <QHash>
#include <vtkDICOMDataElement.h>
#include <vtkDICOMTag.h>

#include "DicomTagStdHashSpecialization.hpp"

namespace cadsi_lib::dicom {
    class DicomMetaDataHashCollection {
    public:
        virtual ~DicomMetaDataHashCollection() = default;

        [[nodiscard]] QHash<vtkDICOMTag, vtkDICOMDataElement> getMetaCollection() const;
        [[nodiscard]] vtkDICOMDataElement getMeta(const vtkDICOMTag& tag) const;
        void setMeta(const vtkDICOMDataElement& data);
        void setMeta(vtkDICOMDataElement&& data);
        void setMeta(const vtkDICOMTag& tag, const vtkDICOMDataElement& data);
        void setMeta(const vtkDICOMTag& tag, vtkDICOMDataElement&& data);
        void setMeta(const vtkDICOMTag& tag, const vtkDICOMValue& val);
        void setMeta(const vtkDICOMTag& tag, vtkDICOMValue&& val);

        void reserveMetaCollection(qsizetype size);
    private:
        QHash<vtkDICOMTag, vtkDICOMDataElement> _meta_collection;
    };
}
#endif    //CADSI_DICOMMETADATAHASHCOLLECTION_HPP
