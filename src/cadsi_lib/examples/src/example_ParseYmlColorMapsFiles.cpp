//
// Created by nyanbanan on 07.04.2024.
//

#include <cadsi_lib/color_maps/providers/YamlColorMapsProvider.hpp>
#include <cadsi_lib/file_data/providers/YamlFileDataProvider.hpp>
#include <iostream>

void printColorMap(std::string_view name, QList<vtkColor3d> color_map){
    std::cout << std::format("{}:", name) << std::endl;
    for (auto color : color_map) {
        std::cout << std::format("[{}, {}, {}]", color[0], color[1], color[2]) << std::endl;
    }
}

int main(int argc, char* argv[]) {
    //Get YAML data from file
    cadsi_lib::file_data::providers::YamlFileDataProvider file_data;
    auto color_maps_node_load_res = file_data.getFileData("../data/colormaps.yml");
    if (!color_maps_node_load_res.status.success) {
        auto status = color_maps_node_load_res.status;
        std::cout << "Get YAML data from file error: " << status.error_message << std::endl;
        return -1;
    }
    cadsi_lib::color_maps::providers::YamlColorMapsProvider color_maps;
    auto color_maps_load_res = color_maps.deserialize(color_maps_node_load_res.data);
    if (!color_maps_load_res.success) {
        std::cout << "Load color maps data from YAML error: " << color_maps_load_res.error_message << std::endl;
        return -1;
    }
    std::cout << std::endl;

    //All color maps names collection
    auto all_colors_names = color_maps.colorMapsNames();
    std::cout << "Color maps:" << std::endl;
    for (unsigned long long i = 0; i < color_maps.size(); ++i) {
        auto name = all_colors_names.value(qsizetype(i));
        //Getting color map by name
        auto color_map = color_maps.colorMap(name);
        printColorMap(name.toStdString(), color_map);
    }
    std::cout << std::endl;
    //Also can get all color maps collection in 1 QMap
    auto all_colors = color_maps.allColorMaps();
    std::cout << "Color maps from qmap:" << std::endl;
    for (auto iter = all_colors.cbegin(); iter != all_colors.cend(); ++iter) {
        const auto& name = iter.key();
        const auto& color_map = iter.value();
        printColorMap(name.toStdString(), color_map);
    }
    std::cout << std::endl;
    //TODO: Add getLUT examples in future

    //If the color map with specific name not contains in collection, return default init object (Empty QList)
    std::cout << "If the color map with specific name not contains in collection, return default init object (Empty QList): ";
    auto default_color_map = color_maps.colorMap("Reaves");
    printColorMap("Default color map", default_color_map);
}