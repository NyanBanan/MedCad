//
// Created by nyanbanan on 24.02.2024.
//

#ifndef CADSI_YAMLCOLORSPROVIDER_HPP
#define CADSI_YAMLCOLORSPROVIDER_HPP

#include <QRandomGenerator>
#include <ranges>

#include "cadsi_lib/yaml/YamlDeserializable.hpp"
#include "cadsi_lib/colors/providers/ColorsProvider.hpp"

namespace cadsi_lib::colors::providers {
    /*!
	\brief Class for work with colors declared in yaml
        */
    class YamlColorsProvider : public ColorsProvider,
                               cadsi_lib::yaml::YamlDeserializable {
    public:
        QMap<QString, vtkColor3d> allColors() override;
        /*!
	    \warning If the color with specific name not contains in collection, return default init object (0,0,0 color)
                                        */
        vtkColor3d color(QString name) override;
        QList<QString> colorNames() override;
        vtkColor3d randomColor() override;
        size_t size() override;

        OperationStatus deserialize(const YAML::Node& root_node) override;

    private:
        QMap<QString, vtkColor3d> _all_colors;
    };
}    //namespace cadsi_lib::global_providers::yaml

#endif    //CADSI_YAMLCOLORSPROVIDER_HPP
