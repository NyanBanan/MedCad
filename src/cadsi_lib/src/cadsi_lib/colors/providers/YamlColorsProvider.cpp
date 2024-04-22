//
// Created by nyanbanan on 24.02.2024.
//

#include "cadsi_lib/colors/providers/YamlColorsProvider.hpp"

namespace cadsi_lib::colors::providers {
    QMap<QString, vtkColor3d> YamlColorsProvider::allColors() {
        return _all_colors;
    }

    vtkColor3d YamlColorsProvider::color(QString name) {
        return _all_colors.value(name);
    }

    QList<QString> YamlColorsProvider::colorNames() {
        return _all_colors.keys();
    }

    vtkColor3d YamlColorsProvider::randomColor() {
        if(size() == 0){
            return {0, 0, 0};
        }
        auto iter = _all_colors.begin();
        auto num = QRandomGenerator::global()->bounded(size());
        std::ranges::advance(iter, int(num), _all_colors.end());
        return iter.value();
    }

    size_t YamlColorsProvider::size() {
        return _all_colors.size();
    }

    OperationStatus YamlColorsProvider::deserialize(const YAML::Node& root_node) {
        if (!root_node.IsMap()) {
            return {false, PARSE_ERROR, "root node have wrong format"};
        }
        for (const auto& color_data : root_node) {
            QString name = QString::fromUtf8(color_data.first.as<std::string>());
            auto color = color_data.second;
            if (!color.IsSequence()) {
                return {false, PARSE_ERROR, std::format("color node {} have wrong format", name.toStdString())};
            }
            if (color.size() != 3) {
                return {false, PARSE_ERROR, std::format("color sequence node {} have wrong size", name.toStdString())};
            }
            try {
                vtkColor3d rgb_color{color[0].as<double>(), color[1].as<double>(), color[2].as<double>()};
                _all_colors[name] = rgb_color;
            } catch (YAML::Exception& e) {
                return {false,
                        PARSE_ERROR,
                        std::format("color sequence node {} parse exception: {}",
                                    name.toStdString(),
                                    e.what())};
            }
        }
        return {true};
    }
}    //namespace cadsi_lib::providers::yaml
