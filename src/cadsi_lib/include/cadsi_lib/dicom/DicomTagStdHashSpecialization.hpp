//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMTAGSTDHASHSPECIALIZATION_HPP
#define CADSI_DICOMTAGSTDHASHSPECIALIZATION_HPP

#include <vtkDICOMTag.h>

namespace std {
    template <> struct hash<vtkDICOMTag>
    {
        size_t operator()(const vtkDICOMTag & tag) const
        {
            return tag.ComputeHash();
        }
    };
}
#endif    //CADSI_DICOMTAGSTDHASHSPECIALIZATION_HPP
