//
// Created by nyanbanan on 07.04.2024.
//

#include <cadsi_lib/colors/providers/YamlColorsProvider.hpp>
#include <cadsi_lib/file_data/providers/YamlFileDataProvider.hpp>
#include <iostream>

void printColor(std::string_view name, const vtkColor3d& vtk_color){
    std::cout << std::format("{}: [{}, {}, {}]", name, vtk_color[0], vtk_color[1], vtk_color[2])  << std::endl;
}

int main(int argc, char* argv[]) {
    //Get YAML data from file
    cadsi_lib::file_data::providers::YamlFileDataProvider file_data;
    auto colors_node_load_res = file_data.getFileData("../data/colors.yml");
    if (!colors_node_load_res.status.success) {
        auto status = colors_node_load_res.status;
        std::cout << "Get YAML data from file error: " << status.error_message << std::endl;
        return -1;
    }
    cadsi_lib::colors::providers::YamlColorsProvider colors;
    auto colors_load_res = colors.deserialize(colors_node_load_res.data);
    if (!colors_load_res.success){
        std::cout << "Load colors data from YAML error: " << colors_load_res.error_message << std::endl;
        return -1;
    }
    std::cout << std::endl;

    //All color names collection
    auto all_colors_names = colors.colorNames();
    std::cout << "Colors:"  << std::endl;
    for(unsigned long long i = 0; i < colors.size(); ++i){
        auto name = all_colors_names.value(qsizetype(i));
        //Getting color by name
        auto vtk_color = colors.color(name);
        printColor(name.toStdString(), vtk_color);
    }
    std::cout << std::endl;
    //Also can get all colors collection in 1 QMap
    auto all_colors = colors.allColors();
    std::cout <<"Colors from qmap:" << std::endl;
    for(auto iter = all_colors.cbegin(); iter!=all_colors.cend() ;++iter){
        const auto& name = iter.key();
        auto vtk_color = iter.value();
        printColor(name.toStdString(), vtk_color);
    }
    std::cout << std::endl;
    //Random color
    auto vtk_color = colors.randomColor();
    printColor("Random element", vtk_color);

    //If the color with specific name not contains in collection, return default init object
    std::cout << "If the color with specific name not contains in collection, return default init object: ";
    auto default_color = colors.color("Reaves");
    printColor("Default color", default_color);
}
