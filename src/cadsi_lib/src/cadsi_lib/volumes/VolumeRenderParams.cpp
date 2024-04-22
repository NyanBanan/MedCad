//
// Created by nyanbanan on 21.04.2024.
//

#include "cadsi_lib/volumes/VolumeRenderParams.hpp"

namespace cadsi_lib::volumes {

    Result<VolumesRenderParams::Tissue> VolumesRenderParams::tissueFromString(const std::string& tissue) {
        using Tissue = VolumesRenderParams::Tissue;
        static const std::unordered_map<std::string, Tissue> table = {{"bone", Tissue::BONE},
                                                                      {"muscle", Tissue::MUSCLE},
                                                                      {"skin", Tissue::SKIN}};
        auto it = table.find(tissue);
        if (it != table.end()) {
            return {.status{.success = true}, .data = it->second};
        } else {
            return {.status{.success = false,
                            .error_code = ErrorCodes::WRONG_TISSUE_STRING,
                            .error_message = std::format("{} is not a tissue", tissue)}};
        }
    }

    Result<VolumesRenderParams::Modality> volumes::VolumesRenderParams::modalityFromString(const std::string& modality) {
        using Modality = VolumesRenderParams::Modality;
        static const std::unordered_map<std::string, Modality> table = {{"ct", Modality::CT}, {"mri", Modality::MRI}};
        auto it = table.find(modality);
        if (it != table.end()) {
            return {.status{.success = true}, .data = it->second};
        } else {
            return {.status{.success = false,
                            .error_code = ErrorCodes::WRONG_MODALITY_STRING,
                            .error_message = std::format("{} is not a modality", modality)}};
        }
    }
}    //namespace cadsi_lib::volumes
