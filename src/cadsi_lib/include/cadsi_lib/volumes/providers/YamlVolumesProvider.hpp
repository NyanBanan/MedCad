//
// Created by nyanbanan on 05.04.2024.
//

#ifndef CADSI_YAMLVOLUMESPROVIDER_HPP
#define CADSI_YAMLVOLUMESPROVIDER_HPP

#include <QMap>

#include "cadsi_lib/yaml/YamlDeserializable.hpp"
#include "cadsi_lib/volumes/providers/VolumesProvider.hpp"

namespace cadsi_lib::volumes::providers {
    /*!
	\brief Class for work with volume maps declared in yaml
        */
    class YamlVolumesProvider : public VolumesProvider,
                                public cadsi_lib::yaml::YamlDeserializable {
    public:
        /*!
	    \warning If the parameters with specific modality and tissue not contains in collection, return default init object
                                        */
        VolumesRenderParams getVolumeRenderParams(VolumesRenderParams::Modality modality,
                                                  VolumesRenderParams::Tissue tissue) override;

        OperationStatus deserialize(const YAML::Node& root_node) override;
        size_t size() override;

        QMap<QPair<VolumesRenderParams::Modality, VolumesRenderParams::Tissue>, VolumesRenderParams>
            getAllVolumesRenderParams();
    private:
        OperationStatus checkTissueNodeKeys(const YAML::Node& tissue_node);

        QMap<QPair<VolumesRenderParams::Modality, VolumesRenderParams::Tissue>, VolumesRenderParams> _all_volumes_render_params{};
    };

}    // namespace cadsi_lib::providers::yaml

#endif    //CADSI_YAMLVOLUMESPROVIDER_HPP
