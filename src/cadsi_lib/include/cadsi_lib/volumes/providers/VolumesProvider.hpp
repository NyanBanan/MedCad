//
// Created by nyanbanan on 21.02.2024.
//

#ifndef CADSI_VOLUMESPROVIDER_HPP
#define CADSI_VOLUMESPROVIDER_HPP

#include <QList>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>

#include "cadsi_lib/Result.hpp"
#include "cadsi_lib/volumes/VolumeErrorCodes.hpp"
#include "cadsi_lib/volumes/VolumeRenderParams.hpp"

namespace cadsi_lib::volumes::providers {
    class VolumesProvider {
    public:
        virtual ~VolumesProvider() = default;

        vtkSmartPointer<vtkVolumeProperty> volumeRenderPreset(VolumesRenderParams::Modality modality,
                                                              VolumesRenderParams::Tissue tissue);
        virtual VolumesRenderParams getVolumeRenderParams(VolumesRenderParams::Modality modality,
                                                          VolumesRenderParams::Tissue tissue) = 0;
        virtual size_t size() = 0;
    };
}    //namespace cadsi_lib::volumes::providers

#endif    //CADSI_VOLUMESPROVIDER_HPP
