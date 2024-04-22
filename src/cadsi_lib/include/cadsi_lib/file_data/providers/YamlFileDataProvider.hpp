//
// Created by nyanbanan on 07.04.2024.
//

#ifndef CADSI_YAMLFILEDATAPROVIDER_HPP
#define CADSI_YAMLFILEDATAPROVIDER_HPP

#include <filesystem>
#include <yaml-cpp/yaml.h>

#include "cadsi_lib/Result.hpp"
#include "cadsi_lib/file_data/providers/FileDataProvider.hpp"

namespace cadsi_lib::file_data::providers {
    /*!
	\brief Class for load data from file to YAML::Node for further parsing
        */
    class YamlFileDataProvider : public FileDataProvider<YAML::Node> {
    public:
        Result<YAML::Node> getFileData(std::string_view file_path) override;
    };
}

#endif    //CADSI_YAMLFILEDATAPROVIDER_HPP
