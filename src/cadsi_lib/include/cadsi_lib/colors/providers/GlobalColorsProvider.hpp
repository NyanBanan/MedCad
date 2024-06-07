//
// Created by nyanbanan on 24.04.2024.
//

#ifndef CADSI_GLOBALCOLORSPROVIDER_HPP
#define CADSI_GLOBALCOLORSPROVIDER_HPP

#include <QWeakPointer>

#include "ColorsProvider.hpp"

namespace cadsi_lib::colors::providers {
    class GlobalColorsProvider {
    public:
        static void setGlobalColorsProvider(ColorsProvider* provider);
        static QWeakPointer<ColorsProvider> getGlobalColorsProvider();

    private:
        static inline QSharedPointer<ColorsProvider> _colors_provider = nullptr;
    };
}    //namespace cadsi_lib::colors::providers
#endif    //CADSI_GLOBALCOLORSPROVIDER_HPP
