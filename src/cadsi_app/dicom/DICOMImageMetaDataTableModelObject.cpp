//
// Created by nyanbanan on 14.04.2024.
//

#include "DICOMImageMetaDataTableModelObject.hpp"

void DICOMImageMetaDataTableModelObject::setTag(const QString& tag) {
    _tag = tag;
}

QString DICOMImageMetaDataTableModelObject::getTag() const {
    return _tag;
}

void DICOMImageMetaDataTableModelObject::setName(const QString& name) {
    _name = name;
}

QString DICOMImageMetaDataTableModelObject::getName() const {
    return _name;
}

void DICOMImageMetaDataTableModelObject::setVal(const QString& val) {
    _val = val;
}

QString DICOMImageMetaDataTableModelObject::getVal() const {
    return _val;
}

void DICOMImageMetaDataTableModelObject::setVR(const QString& vr) {
    _vr = vr;
}

QString DICOMImageMetaDataTableModelObject::getVR() const {
    return _vr;
}

DICOMImageMetaDataTableModelObject DICOMImageMetaDataTableModelObject::fromDicomDataElement(const vtkDICOMDataElement& data) {
    DICOMImageMetaDataTableModelObject obj;
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

DICOMImageMetaDataTableModelObject DICOMImageMetaDataTableModelObject::fromDicomDataElement(vtkDICOMDataElement&& data) {
    DICOMImageMetaDataTableModelObject obj;
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
