//
// Created by nyanbanan on 07.04.2024.
//

#include <cadsi_lib/file_data/providers/YamlFileDataProvider.hpp>
#include <cadsi_lib/volumes/providers/YamlVolumesProvider.hpp>
#include <iostream>

using VolumeRenderParams = cadsi_lib::volumes::VolumesRenderParams;

void printVolumeRenderParams(const VolumeRenderParams& volume_render_params) {
    std::cout << std::format("Tissue: {},\nModality: {}\nAmbient: {}\nDiffuse: {}\nSpecular: {}",
                             int(volume_render_params._tissue),
                             int(volume_render_params._modality),
                             volume_render_params._ambient,
                             volume_render_params._diffuse,
                             volume_render_params._specular)
              << std::endl;
    std::cout << "Volume color" << std::endl;
    for (auto color : volume_render_params._volume_color) {
        std::cout << std::format(" - [{},{},{},{},{},{}]", color.x, color.r, color.g, color.b, color.midpoint, color.sharpness)
                  << std::endl;
    }
    std::cout << std::endl << "Gradient opacity" << std::endl;
    for (auto gradient : volume_render_params._gradient_opacity) {
        std::cout << std::format(" - [{},{}]", gradient.x, gradient.y) << std::endl;
    }
    std::cout << std::endl << "Scalar opacity" << std::endl;
    for (auto scalar : volume_render_params._scalar_opacity) {
        std::cout << std::format(" - [{},{},{},{}]", scalar.x, scalar.y, scalar.midpoint, scalar.sharpness) << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    //Get YAML data from file
    cadsi_lib::file_data::providers::YamlFileDataProvider file_data;
    auto volumes_node_load_res = file_data.getFileData("../data/volume.yml");
    if (!volumes_node_load_res.status.success) {
        auto status = volumes_node_load_res.status;
        std::cout << "Get YAML data from file error: " << status.error_message << std::endl;
        return -1;
    }
    cadsi_lib::volumes::providers::YamlVolumesProvider volumes;
    auto volumes_load_res = volumes.deserialize(volumes_node_load_res.data);
    if (!volumes_load_res.success) {
        std::cout << "Load volumes data from YAML error: " << volumes_load_res.error_message << std::endl;
        return -1;
    }
    std::cout << std::endl;

    //Can get volume render params by modality and tissue
    std::cout << "Volume params:" << std::endl;
    for (auto modality : {VolumeRenderParams::Modality::CT, VolumeRenderParams::Modality::MRI}) {
        for (auto tissue :
             {VolumeRenderParams::Tissue::MUSCLE, VolumeRenderParams::Tissue::BONE, VolumeRenderParams::Tissue::SKIN}) {
            auto volume_render_params = volumes.getVolumeRenderParams(modality, tissue);
            printVolumeRenderParams(volume_render_params);
        }
    }
    std::cout << std::endl;
    //Also can get all volumes collection in 1 QMap
    auto all_volumes = volumes.getAllVolumesRenderParams();
    std::cout << "Volumes from qmap:" << std::endl;
    for (auto iter = all_volumes.cbegin(); iter != all_volumes.cend(); ++iter) {
        const auto& modality_tissue = iter.key();
        const auto& volume_render_params = iter.value();
        printVolumeRenderParams(volume_render_params);
    }
    std::cout << std::endl;
    //TODO: Add volumeRenderPreset examples in future
}
