//
// Created by nyanbanan on 24.04.2024.
//

#include "cadsi_lib/color_maps/providers/GlobalColorMapsProvider.hpp"

namespace cadsi_lib::color_maps::providers {

    void GlobalColorMapsProvider::setGlobalColorMapsProvider(ColorMapsProvider* provider) {
        _color_maps_provider.reset(provider);
    }

    QWeakPointer<ColorMapsProvider> GlobalColorMapsProvider::getGlobalColorMapsProvider() {
        return _color_maps_provider.toWeakRef();
    }
}    //namespace cadsi_lib::color_maps::providers
