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

DICOMSliceMetaDataObject DICOMSliceMetaDataObject::fromDicomDataElement(const vtkDICOMDataElement& data) {
    DICOMSliceMetaDataObject obj;
    auto tag = data.GetTag();
    std::stringstream tag_to_str;
    tag_to_str << tag;
    obj.setTag(QString::fromStdString(tag_to_str.str()));

    auto dict_entr = vtkDICOMDictionary::FindDictEntry(tag);
    if (dict_entr.IsValid()) {
        obj.setName(dict_entr.GetName());
    }

    obj.setVal(QString::fromStdString(data.GetValue().AsString()));

    obj.setVR(data.GetVR().GetText());

    return obj;
}

DICOMSliceMetaDataObject DICOMSliceMetaDataObject::fromDicomDataElement(vtkDICOMDataElement&& data) {
    DICOMSliceMetaDataObject obj;
    auto tag = data.GetTag();
    std::stringstream tag_to_str;
    tag_to_str << tag;
    obj.setTag(QString::fromStdString(tag_to_str.str()));

    auto dict_entr = vtkDICOMDictionary::FindDictEntry(tag);
    if (dict_entr.IsValid()) {
        obj.setName(dict_entr.GetName());
    }

    obj.setVal(QString::fromStdString(data.GetValue().AsString()));

    obj.setVR(data.GetVR().GetText());

    return obj;
}
