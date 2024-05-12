//
// Created by nyanbanan on 12.05.2024.
//

#include "cadsi_lib/dicom/providers/DicomImageDataProvider.hpp"

namespace cadsi_lib::dicom::providers {
    OperationStatus DicomImageDataProvider::parseDicomFiles(vtkStringArray* files) {
        _reader->SetFileNames(files);
        _reader->SetMemoryRowOrderToFileNative();
        _reader->UpdateInformation();

        vtkDICOMMetaData* meta = _reader->GetMetaData();

        // check whether data has a _palette
        bool hasPalette = false;
        if (meta->Get(DC::PhotometricInterpretation).Matches("PALETTE?COLOR")
            || meta->Get(DC::PixelPresentation).Matches("COLOR") || meta->Get(DC::PixelPresentation).Matches("MIXED")
            || meta->Get(DC::PixelPresentation).Matches("TRUE_COLOR")) {
            hasPalette = true;
            // _palette maps stored values, not slope/intercept rescaled values
            _reader->AutoRescaleOff();
        }

        // update the data
        _reader->Update();

        if (_reader->GetErrorCode() != vtkErrorCode::NoError) {
            return {false, _reader->GetErrorCode()};
        }

        // get the output port to connect to the display pipeline
        _output = _reader->GetOutputPort();
        _patient_matrix = _reader->GetPatientMatrix();

        if (hasPalette) {
            _palette->SetInputConnection(_reader->GetOutputPort());
            _palette->Update();
            _output = _palette->GetOutputPort();
        }

        if (meta->Get(DC::Modality).Matches("CT")) {
            _rect->SetVolumeMatrix(_reader->GetPatientMatrix());
            _rect->SetInputConnection(_output);
            _rect->Update();
            _output = _rect->GetOutputPort();
            _patient_matrix = _rect->GetRectifiedMatrix();
        }
        return {true};
    }

    vtkAlgorithmOutput* DicomImageDataProvider::getOutputPort() {
        return _output;
    }

    vtkMatrix4x4* DicomImageDataProvider::getPatientMatrix() {
        return _patient_matrix;
    }

    vtkDICOMMetaData* DicomImageDataProvider::getMetaData() {
        return _reader->GetMetaData();
    }
}    //namespace cadsi_lib::dicom::providers
