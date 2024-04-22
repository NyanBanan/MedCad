//
// Created by nyanbanan on 24.02.2024.
//

#include "cadsi_lib/color_maps/providers/YamlColorMapsProvider.hpp"

namespace cadsi_lib::color_maps::providers {

    QMap<QString, QList<vtkColor3d>> YamlColorMapsProvider::allColorMaps() {
        return _all_maps;
    }

    QList<QString> YamlColorMapsProvider::colorMapsNames() {
        return _all_maps.keys();
    }

    QList<vtkColor3d> YamlColorMapsProvider::colorMap(QString color_map_name) {
        return _all_maps.value(color_map_name);
    }

    OperationStatus YamlColorMapsProvider::deserialize(const YAML::Node& root_node) {
        if (!root_node.IsMap()) {
            return {false, PARSE_ERROR, "root node have wrong format"};
        }
        for (const auto& map_data : root_node) {
            auto val = map_data.second;
            if (!val.IsMap()) {
                return {false, PARSE_ERROR, "color node have wrong format"};
            }
            if (!val["name"]) {
                return {false, PARSE_ERROR, "color node dont have name key"};
            }
            QString name = QString::fromUtf8(val["name"].as<std::string>());
            QList<vtkColor3d>& colors = _all_maps[name];
            if (!val["colors"]) {
                return {false, PARSE_ERROR, "color node dont have colors key"};
            }
            for (auto&& color_data : val["colors"]) {
                if (color_data.size() != 3) {
                    return {false, PARSE_ERROR, std::format("color sequence node {} have wrong size", name.toStdString())};
                }
                try {
                    colors.emplace_back(color_data[0].as<double>(),
                                        color_data[1].as<double>(),
                                        color_data[2].as<double>());
                } catch (YAML::Exception& e) {
                    return {false,
                            PARSE_ERROR,
                            std::format("color sequence node {} parse exception: {}", name.toStdString(), e.what())};
                }
            }
        }
        return {true};
    }

    size_t YamlColorMapsProvider::size() {
        return _all_maps.size();
    }
}    //namespace cadsi_lib::providers::yaml
