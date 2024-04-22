//
// Created by nyanbanan on 21.04.2024.
//

#include "cadsi_lib/volumes/providers/GlobalVolumeProvider.hpp"

namespace cadsi_lib::volumes::providers {
    void GlobalVolumeProvider::setGlobalVolumesProvider(cadsi_lib::volumes::providers::VolumesProvider* provider) {
        _volume_provider.reset(provider);
    }

    QWeakPointer<VolumesProvider> GlobalVolumeProvider::getGlobalVolumesProvider() {
        return _volume_provider.toWeakRef();
    }
}    //namespace cadsi_lib::volumes::providers
