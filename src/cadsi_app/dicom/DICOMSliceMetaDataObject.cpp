//
// Created by nyanbanan on 14.04.2024.
//

#include "DICOMSliceMetaDataObject.hpp"

void DICOMSliceMetaDataObject::setTag(const QString& tag) {
    _tag = tag;
}

QString DICOMSliceMetaDataObject::getTag() const {
    return _tag;
}

void DICOMSliceMetaDataObject::setName(const QString& name) {
    _name = name;
}

QString DICOMSliceMetaDataObject::getName() const {
    return _name;
}

void DICOMSliceMetaDataObject::setVal(const QString& val) {
    _val = val;
}

QString DICOMSliceMetaDataObject::getVal() const {
    return _val;
}

void DICOMSliceMetaDataObject::setVR(const QString& vr) {
    _vr = vr;
}

QString DICOMSliceMetaDataObject::getVR() const {
    return _vr;
}

DICOMSliceMetaDataObject DICOMSliceMetaDataObject::fromCadsiDicomDataElement(
    const cadsi_lib::dicom::cadsiDicomDataElement& data) {
    DICOMSliceMetaDataObject obj;
    auto dict_entry = data.getDictEntry();
    auto tag = dict_entry.GetTag();
    std::stringstream tag_to_str;
    tag_to_str << tag;
    obj.setTag(QString::fromStdString(tag_to_str.str()));

    obj.setName(dict_entry.GetName());

    obj.setVal(QString::fromStdString(data.getValue().AsString()));

    obj.setVR(dict_entry.GetVR().GetText());

    return obj;
}

DICOMSliceMetaDataObject DICOMSliceMetaDataObject::fromCadsiDicomDataElement(cadsi_lib::dicom::cadsiDicomDataElement&& data) {
    DICOMSliceMetaDataObject obj;
    auto dict_entry = data.getDictEntry();
    auto tag = dict_entry.GetTag();
    std::stringstream tag_to_str;
    tag_to_str << tag;
    obj.setTag(QString::fromStdString(tag_to_str.str()));

    obj.setName(dict_entry.GetName());

    obj.setVal(QString::fromStdString(data.getValue().AsString()));

    obj.setVR(dict_entry.GetVR().GetText());

    return obj;
}
