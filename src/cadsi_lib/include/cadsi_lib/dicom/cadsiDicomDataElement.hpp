//
// Created by nyanbanan on 01.05.2024.
//

#ifndef CADSI_CADSIDICOMDATAELEMENT_HPP
#define CADSI_CADSIDICOMDATAELEMENT_HPP

#include <vtkDICOMDataElement.h>
#include <vtkDICOMDictionary.h>
#include <vtkDICOMValue.h>

namespace cadsi_lib::dicom {
    class cadsiDicomDataElement {
    public:
        cadsiDicomDataElement(const vtkDICOMDictEntry& dictEntry, const vtkDICOMValue& value);
        cadsiDicomDataElement() = default;
        [[nodiscard]] const vtkDICOMDictEntry& getDictEntry() const;
        void setDictEntry(const vtkDICOMDictEntry& dictEntry);
        [[nodiscard]] const vtkDICOMValue& getValue() const;
        void setValue(const vtkDICOMValue& value);

    private:
        vtkDICOMDictEntry _dict_entry;
        vtkDICOMValue _value;
    };
}    //namespace cadsi_lib::dicom
#endif    //CADSI_CADSIDICOMDATAELEMENT_HPP
