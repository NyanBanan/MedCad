//
// Created by nyanbanan on 27.02.2024.
//

#ifndef CADSI_YAMLDESERIALIZABLE_HPP
#define CADSI_YAMLDESERIALIZABLE_HPP

#include <filesystem>
#include <yaml-cpp/yaml.h>

#include "cadsi_lib/OperationStatus.hpp"

namespace cadsi_lib::yaml {
    /*!
         \brief Interface that adds data deserializing from yaml node
            */
    class YamlDeserializable {
    public:
        /*!
         \brief Error codes for return in OperationStatus::error_code
            */
        enum ErrorCodes {
            PARSE_ERROR = 405
        };
        virtual ~YamlDeserializable() = default;

        virtual OperationStatus deserialize(const YAML::Node& root_node) = 0;
    };

}
#endif    //CADSI_YAMLDESERIALIZABLE_HPP
