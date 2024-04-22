//
// Created by nyanbanan on 21.02.2024.
//

#ifndef CADSI_COLORMAPSPROVIDER_HPP
#define CADSI_COLORMAPSPROVIDER_HPP

#include <ranges>
#include <QString>
#include <QList>
#include <QMap>
#include <vtkColor.h>
#include <vtkLookupTable.h>
#include <vtkColorTransferFunction.h>

namespace cadsi_lib::color_maps::providers {
    class ColorMapsProvider {
    public:
        virtual ~ColorMapsProvider() = default;

        virtual QMap<QString, QList<vtkColor3d>> allColorMaps() = 0;
        virtual QList<QString> colorMapsNames() = 0;

        /*!brief LUT для цветовой карты. Используется интерполяция для получения lut в заданном диапазоне,
            с заданным числом цветов.

            \param color_map_name: название цветовой карты
            \param num_colors: количество элементов в создаваемой lut
            \param min_value: начальное значение диапазона
            \param max_value: конечное значение диапазона
              */
        vtkSmartPointer<vtkLookupTable> getLUT(QString color_map_name, uint num_colors = 256, int min_value = -2048, int max_value = 2048);
        /*!brief LUT для цветовой карты. Используется интерполяция для получения lut в заданном диапазоне,
            с заданным числом цветов.

        \param color_map: цветовая карты
            \param num_colors: количество элементов в создаваемой lut
            \param min_value: начальное значение диапазона
            \param max_value: конечное значение диапазона
                                */
        vtkSmartPointer<vtkLookupTable> getLUT(QList<vtkColor3d> color_map, uint num_colors = 256, int min_value = -2048, int max_value = 2048);
        virtual QList<vtkColor3d> colorMap(QString color_map_name) = 0;
        virtual size_t size() = 0;
    };
}    //namespace cadsi_lib

#endif    //CADSI_COLORMAPSPROVIDER_HPP
