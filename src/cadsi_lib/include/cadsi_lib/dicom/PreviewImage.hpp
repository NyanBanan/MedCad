//
// Created by nyanbanan on 21.04.2024.
//

#ifndef CADSI_PREVIEWIMAGE_HPP
#define CADSI_PREVIEWIMAGE_HPP

#include <QImage>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkDICOMReader.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkWindowToImageFilter.h>

#include "cadsi_lib/volumes/VolumeObject.hpp"

namespace cadsi_lib::dicom {
    class PreviewImage {
    public:
        static vtkSmartPointer<vtkImageData> generatePreviewImage(vtkMatrix4x4* patient_matrix,
                                                                  vtkAlgorithmOutput* data_input);
        static QImage vtkImageDataToQImage(vtkImageData* image_data);
    };
}
#endif    //CADSI_PREVIEWIMAGE_HPP
