//
// Created by nyanbanan on 21.04.2024.
//

#ifndef CADSI_VOLUMEOBJECT_HPP
#define CADSI_VOLUMEOBJECT_HPP

#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>

#include "VolumeImage.hpp"
#include "providers/GlobalVolumeProvider.hpp"

namespace cadsi_lib::volumes {
    class VolumeObject: public vtkVolume{
    public:
        static VolumeObject* New(VolumesRenderParams::Modality modality = VolumesRenderParams::CT, VolumesRenderParams::Tissue tissue = VolumesRenderParams::BONE);
        explicit VolumeObject(VolumesRenderParams::Modality modality = VolumesRenderParams::CT, VolumesRenderParams::Tissue tissue = VolumesRenderParams::BONE);
    };
}
#endif    //CADSI_VOLUMEOBJECT_HPP
