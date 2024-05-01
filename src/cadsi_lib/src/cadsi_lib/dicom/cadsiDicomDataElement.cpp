//
// Created by nyanbanan on 01.05.2024.
//

#include "cadsi_lib/dicom/cadsiDicomDataElement.hpp"

namespace cadsi_lib::dicom {

    cadsiDicomDataElement::cadsiDicomDataElement(const vtkDICOMDictEntry& dictEntry, const vtkDICOMValue& value)
        : _dict_entry(dictEntry),
          _value(value) {}

    const vtkDICOMDictEntry& cadsiDicomDataElement::getDictEntry() const {
        return _dict_entry;
    }

    void cadsiDicomDataElement::setDictEntry(const vtkDICOMDictEntry& dictEntry) {
        _dict_entry = dictEntry;
    }

    const vtkDICOMValue& cadsiDicomDataElement::getValue() const {
        return _value;
    }

    void cadsiDicomDataElement::setValue(const vtkDICOMValue& value) {
        _value = value;
    }
}    //namespace cadsi_lib::dicom
