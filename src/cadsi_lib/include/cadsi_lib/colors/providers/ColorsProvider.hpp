//
// Created by nyanbanan on 21.02.2024.
//

#ifndef CADSI_COLORSPROVIDER_HPP
#define CADSI_COLORSPROVIDER_HPP

#include <QList>
#include <QMap>
#include <QRgb>
#include <vtkColor.h>

namespace cadsi_lib::colors::providers {
    class ColorsProvider {
    public:
        virtual ~ColorsProvider() = default;

        virtual QMap<QString, vtkColor3d> allColors() = 0;
        virtual QList<QString> colorNames() = 0;
        virtual vtkColor3d color(QString name) = 0;
        virtual vtkColor3d randomColor() = 0;
        virtual size_t size() = 0;
    };
}    //namespace cadsi_lib

#endif    //CADSI_COLORSPROVIDER_HPP
