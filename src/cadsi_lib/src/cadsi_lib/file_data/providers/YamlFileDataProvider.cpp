//
// Created by nyanbanan on 07.04.2024.
//

#include "cadsi_lib/file_data/providers/YamlFileDataProvider.hpp"

#include "cadsi_lib/Result.hpp"

namespace cadsi_lib::file_data::providers {
    Result<YAML::Node> YamlFileDataProvider::getFileData(std::string_view file_path) {
        std::filesystem::path path{file_path};
        if (!exists(path)) {
            return {false, FILE_NOT_EXIST};
        }
        if (path.extension() != ".yml") {
            return {false, WRONG_FILE_FORMAT};
        }
        try {
            auto data = YAML::LoadFile(path.string());
            return {true, 0, "", data};
        } catch (YAML::BadFile& exc) {
            return {false, BAD_FILE, exc.what()};
        } catch (YAML::ParserException& exc) {
            return {false, PARSE_ERROR, exc.what()};
        }
    }
}    //namespace cadsi_lib::providers::yaml
