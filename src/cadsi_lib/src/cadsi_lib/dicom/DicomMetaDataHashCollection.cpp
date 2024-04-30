//
// Created by nyanbanan on 14.04.2024.
//

#include "cadsi_lib/dicom/DicomMetaDataHashCollection.hpp"

namespace cadsi_lib::dicom {
    const QHash<vtkDICOMTag, vtkDICOMDataElement>& DicomMetaDataHashCollection::getMetaCollection() const {
        return _meta_collection;
    }

    vtkDICOMDataElement DicomMetaDataHashCollection::getMeta(const vtkDICOMTag& tag) const {
        if (!_meta_collection.contains(tag)) {
            return {};
        }
        return _meta_collection[tag];
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMDataElement& data) {
        _meta_collection[data.GetTag()] = data;
    }

    void DicomMetaDataHashCollection::setMeta(vtkDICOMDataElement&& data) {
        _meta_collection[data.GetTag()] = data;
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMTag& tag, const vtkDICOMDataElement& data) {
        _meta_collection[tag] = data;
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMTag& tag, vtkDICOMDataElement&& data) {
        _meta_collection[tag] = data;
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMTag& tag, const vtkDICOMValue& val) {
        _meta_collection[tag] = {tag,val};
    }

    void DicomMetaDataHashCollection::setMeta(const vtkDICOMTag& tag, vtkDICOMValue&& val) {
        _meta_collection[tag] = {tag,val};
    }

    void DicomMetaDataHashCollection::reserveMetaCollection(qsizetype size) {
        _meta_collection.reserve(size);
    }
}    //namespace casdi_lib::dicom
