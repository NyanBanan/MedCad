//
// Created by nyanbanan on 12.05.2024.
//

#ifndef CADSI_DICOMIMAGEDATAPROVIDER_HPP
#define CADSI_DICOMIMAGEDATAPROVIDER_HPP

#include <vtkDICOMApplyPalette.h>
#include <vtkDICOMCTRectifier.h>
#include <vtkDICOMDirectory.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMReader.h>
#include <vtkErrorCode.h>
#include <vtkImageData.h>
#include <vtkImageReslice.h>
#include <vtkNew.h>

#include "cadsi_lib/OperationStatus.hpp"

namespace cadsi_lib::dicom::providers {
    class DicomImageDataProvider {
    public:
        OperationStatus parseDicomFiles(vtkStringArray* files);
        vtkAlgorithmOutput* getOutputPort();
        vtkMatrix4x4* getPatientMatrix();
        vtkDICOMMetaData* getMetaData();

    private:
        vtkNew<vtkDICOMReader> _reader;
        vtkNew<vtkDICOMCTRectifier> _rect;
        vtkNew<vtkDICOMApplyPalette> _palette;
        vtkAlgorithmOutput* _output{nullptr};
        vtkMatrix4x4* _patient_matrix{nullptr};
    };
}    //namespace cadsi_lib::dicom::providers
#endif    //CADSI_DICOMIMAGEDATAPROVIDER_HPP
