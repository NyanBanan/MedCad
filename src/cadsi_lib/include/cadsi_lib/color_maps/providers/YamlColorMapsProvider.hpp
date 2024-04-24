//
// Created by nyanbanan on 24.02.2024.
//

#ifndef CADSI_YAMLCOLORMAPSPROVIDER_HPP
#define CADSI_YAMLCOLORMAPSPROVIDER_HPP

#include "cadsi_lib/yaml/YamlDeserializable.hpp"
#include "cadsi_lib/color_maps/providers/ColorMapsProvider.hpp"

namespace cadsi_lib::color_maps::providers {
    /*!
	\brief Class for work with color maps declared in yaml
        */
    class YamlColorMapsProvider : public ColorMapsProvider,
                                  public cadsi_lib::yaml::YamlDeserializable {
    public:
        QMap<QString, QList<vtkColor3d>> allColorMaps() override;
        QList<QString> colorMapsNames() override;
        /*!
	    \warning If the color map with specific name not contains in collection, return default init object (Empty QList)
                                        */
        QList<vtkColor3d> colorMap(QString color_map_name) override;
        size_t size() override;

        OperationStatus deserialize(const YAML::Node& root_node) override;

    private:
        QMap<QString, QList<vtkColor3d>> _all_maps{};
    };
}    //namespace cadsi_lib::providers::yaml
#endif    //CADSI_YAMLCOLORMAPSPROVIDER_HPP
