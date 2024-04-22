//
// Created by nyanbanan on 21.04.2024.
//

#include "cadsi_lib/volumes/VolumeObject.hpp"

namespace cadsi_lib::volumes {

    VolumeObject* VolumeObject::New(VolumesRenderParams::Modality modality, VolumesRenderParams::Tissue tissue) {
        return new VolumeObject(modality, tissue);
    }

    VolumeObject::VolumeObject(VolumesRenderParams::Modality modality, VolumesRenderParams::Tissue tissue) {
        vtkNew<vtkGPUVolumeRayCastMapper> mapper;
        mapper->SetBlendModeToComposite();
        SetMapper(mapper);
        auto volume_properties_provider = providers::GlobalVolumeProvider::getGlobalVolumesProvider().toStrongRef();
        if (!volume_properties_provider.isNull()) {
            auto property = volume_properties_provider->volumeRenderPreset(modality, tissue);
            vtkVolume::SetProperty(property);
        }
    }
}    //namespace cadsi_lib::volumes
