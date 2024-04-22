//
// Created by nyanbanan on 05.04.2024.
//

#include "cadsi_lib/volumes/providers/YamlVolumesProvider.hpp"

namespace cadsi_lib::volumes::providers {

    VolumesRenderParams YamlVolumesProvider::getVolumeRenderParams(VolumesRenderParams::Modality modality,
                                                                   VolumesRenderParams::Tissue tissue) {
        return _all_volumes_render_params.value({modality, tissue});
    }

    OperationStatus YamlVolumesProvider::deserialize(const YAML::Node& root_node) {
        if (!root_node.IsMap()) {
            return {false, PARSE_ERROR, "root node have wrong format"};
        }
        for (const auto& modality_node : root_node) {
            if (!modality_node.second.IsMap()) {
                return {false, PARSE_ERROR, std::format("{} node is not a map", modality_node.first.as<std::string>())};
            }
            for (const auto& tissue_node : modality_node.second) {
                if (!tissue_node.second.IsMap()) {
                    return {false, PARSE_ERROR, std::format("{} node is not a map", tissue_node.first.as<std::string>())};
                }
                auto tissue_node_v = tissue_node.second;

                auto check_result = checkTissueNodeKeys(tissue_node_v);
                if (!check_result.success) {
                    return check_result;
                }

                VolumesRenderParams params;

                auto tissue_str = tissue_node_v["tissue"].as<std::string>();
                auto tissue_cast_res = VolumesRenderParams::tissueFromString(tissue_str);
                if (!tissue_cast_res.status.success) {
                    return {false, PARSE_ERROR, std::format("tissue {} doesnt exist", tissue_str)};
                }
                params._tissue = tissue_cast_res.data;

                auto modality_str = tissue_node_v["modality"].as<std::string>();
                auto modality_cast_res = VolumesRenderParams::modalityFromString(modality_str);
                if (!modality_cast_res.status.success) {
                    return {false, PARSE_ERROR, std::format("modality {} doesnt exist", modality_str)};
                }
                params._modality = modality_cast_res.data;

                for (auto volume_color : tissue_node_v["color"]) {
                    if (volume_color.size() != 6) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) volume color have wrong size",
                                            tissue_str,
                                            modality_str)};
                    }
                    try {
                        params._volume_color.emplaceBack(volume_color[0].as<double>(),

                                                         volume_color[1].as<double>(),
                                                         volume_color[2].as<double>(),
                                                         volume_color[3].as<double>(),
                                                         volume_color[4].as<double>(),
                                                         volume_color[5].as<double>());
                    } catch (YAML::Exception& e) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) volume color parse exception: {}",
                                            tissue_str,
                                            modality_str,
                                            e.what())};
                    }
                }

                for (auto gradient_opacity : tissue_node_v["gradient_opacity"]) {
                    if (gradient_opacity.size() != 2) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) gradient_opacity have wrong size",
                                            tissue_str,
                                            modality_str)};
                    }
                    try {
                        params._gradient_opacity.emplaceBack(gradient_opacity[0].as<double>(),
                                                             gradient_opacity[1].as<double>());
                    } catch (YAML::Exception& e) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) gradient_opacity parse exception: {}",
                                            tissue_str,
                                            modality_str,
                                            e.what())};
                    }
                }

                for (auto scalar_opacity : tissue_node_v["scalar_opacity"]) {
                    if (scalar_opacity.size() != 4) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) scalar_opacity have wrong size",
                                            tissue_str,
                                            modality_str)};
                    }
                    try {
                        params._scalar_opacity.emplaceBack(scalar_opacity[0].as<double>(),
                                                           scalar_opacity[1].as<double>(),
                                                           scalar_opacity[2].as<double>(),
                                                           scalar_opacity[3].as<double>());
                    } catch (YAML::Exception& e) {
                        return {false,
                                PARSE_ERROR,
                                std::format("(tissue: {} modality: {}) scalar_opacity parse exception: {}",
                                            tissue_str,
                                            modality_str,
                                            e.what())};
                    }
                }
                try {
                    params._ambient = tissue_node_v["ambient"].as<double>();
                    params._diffuse = tissue_node_v["diffuse"].as<double>();
                    params._specular = tissue_node_v["specular"].as<double>();
                } catch (YAML::Exception& e) {
                    return {false,
                            PARSE_ERROR,
                            std::format("(tissue: {} modality: {}) ambient, diffuse or specular parse exception: {}",
                                        tissue_str,
                                        modality_str,
                                        e.what())};
                }

                _all_volumes_render_params.insert({params._modality, params._tissue}, params);
            }
        }
        return {true};
    }

    OperationStatus YamlVolumesProvider::checkTissueNodeKeys(const YAML::Node& tissue_node) {
        if (!tissue_node["ambient"]) {
            return {false, PARSE_ERROR, "tissue node dont have ambient key"};
        }
        if (!tissue_node["color"]) {
            return {false, PARSE_ERROR, "tissue node dont have color key"};
        }
        if (!tissue_node["diffuse"]) {
            return {false, PARSE_ERROR, "tissue node dont have diffuse key"};
        }
        if (!tissue_node["gradient_opacity"]) {
            return {false, PARSE_ERROR, "tissue node dont have gradient_opacity key"};
        }
        if (!tissue_node["modality"]) {
            return {false, PARSE_ERROR, "tissue node dont have modality key"};
        }
        if (!tissue_node["scalar_opacity"]) {
            return {false, PARSE_ERROR, "tissue node dont have scalar_opacity key"};
        }
        if (!tissue_node["specular"]) {
            return {false, PARSE_ERROR, "tissue node dont have specular key"};
        }
        if (!tissue_node["tissue"]) {
            return {false, PARSE_ERROR, "tissue node dont have tissue key"};
        }
        return {true};
    }

    QMap<QPair<VolumesRenderParams::Modality, VolumesRenderParams::Tissue>, VolumesRenderParams>
        YamlVolumesProvider::getAllVolumesRenderParams() {
        return _all_volumes_render_params;
    }

    size_t YamlVolumesProvider::size() {
        return _all_volumes_render_params.size();
    }
}    //namespace cadsi_lib::volumes::providers
