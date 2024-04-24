//
// Created by nyanbanan on 24.04.2024.
//

#include "cadsi_lib/colors/providers/GlobalColorsProvider.hpp"

namespace cadsi_lib::colors::providers {

    void GlobalColorsProvider::setGlobalColorsProvider(ColorsProvider* provider) {
        _colors_provider.reset(provider);
    }

    QWeakPointer<ColorsProvider> GlobalColorsProvider::getGlobalColorsProvider() {
        return _colors_provider.toWeakRef();
    }
}    //namespace cadsi_lib::colors::providers
