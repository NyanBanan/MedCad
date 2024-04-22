//
// Created by nyanbanan on 21.04.2024.
//

#ifndef CADSI_VOLUMEIMAGE_HPP
#define CADSI_VOLUMEIMAGE_HPP

#include <QFileInfo>
#include <vtkImageData.h>
#include <vtkXMLImageDataReader.h>
#include <vtkXMLImageDataWriter.h>

#include "VolumeRenderParams.hpp"
#include "cadsi_lib/file_data/FileDataErrors.hpp"

namespace cadsi_lib::volumes {
    class VolumeImage : public vtkImageData {
    public:
        OperationStatus load(const QString& file_name);
        OperationStatus load(vtkImageData* data);
        OperationStatus save(const QString& file_name);

    private:
        volumes::VolumesRenderParams::Modality _modality;
    };
}    //namespace cadsi_lib
#endif    //CADSI_VOLUMEIMAGE_HPP
