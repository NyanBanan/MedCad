//
// Created by nyanbanan on 21.04.2024.
//

#ifndef CADSI_GLOBALVOLUMEPROVIDER_HPP
#define CADSI_GLOBALVOLUMEPROVIDER_HPP

#include <qsharedpointer.h>

#include "VolumesProvider.hpp"

namespace cadsi_lib::volumes::providers {
    class GlobalVolumeProvider {
    public:
        static void setGlobalVolumesProvider(VolumesProvider* provider);
        static QWeakPointer<VolumesProvider> getGlobalVolumesProvider();
    private:
        static inline QSharedPointer<VolumesProvider> _volume_provider = nullptr;
    };
}
#endif    //CADSI_GLOBALVOLUMEPROVIDER_HPP
