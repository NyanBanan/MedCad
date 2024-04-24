//
// Created by nyanbanan on 24.04.2024.
//

#ifndef CADSI_GLOBALCOLORMAPSPROVIDER_HPP
#define CADSI_GLOBALCOLORMAPSPROVIDER_HPP

#include <QSharedPointer>

#include "cadsi_lib/color_maps/providers/ColorMapsProvider.hpp"

namespace cadsi_lib::color_maps::providers {
    class GlobalColorMapsProvider {
    public:
        GlobalColorMapsProvider() = delete;
        
        static void setGlobalColorMapsProvider(ColorMapsProvider* provider);
        static QWeakPointer<ColorMapsProvider> getGlobalColorMapsProvider();

    private:
        static inline QSharedPointer<ColorMapsProvider> _color_maps_provider = nullptr;
    };
}    //namespace cadsi_lib::color_maps::providers
#endif    //CADSI_GLOBALCOLORMAPSPROVIDER_HPP
