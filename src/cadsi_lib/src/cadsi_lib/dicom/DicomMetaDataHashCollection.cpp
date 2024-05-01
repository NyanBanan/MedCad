//
// Created by nyanbanan on 14.04.2024.
//

#include "cadsi_lib/dicom/DicomMetaDataHashCollection.hpp"

namespace cadsi_lib::dicom {
    const QHash<vtkDICOMTag, cadsiDicomDataElement>& DicomMetaDataHashCollection::getMetaCollection() const {
        return _meta_collection;
    }

    cadsiDicomDataElement DicomMetaDataHashCollection::getMeta(const vtkDICOMTag& tag) const {
        if (!_meta_collection.contains(tag)) {
            return {};
        }
        return _meta_collection[tag];
    }

    void DicomMetaDataHashCollection::setMeta(const cadsiDicomDataElement& data) {
        _meta_collection[data.getDictEntry().GetTag()] = data;
    }

    void DicomMetaDataHashCollection::setMeta(cadsiDicomDataElement&& data) {
        _meta_collection[data.getDictEntry().GetTag()] = data;
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMDictEntry& dictEntry, const vtkDICOMValue& value) {
        _meta_collection[dictEntry.GetTag()] = {dictEntry, value};
    }

    void DicomMetaDataHashCollection::reserveMetaCollection(qsizetype size) {
        _meta_collection.reserve(size);
    }
}    //namespace cadsi_lib::dicom
