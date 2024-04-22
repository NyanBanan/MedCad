//
// Created by nyanbanan on 07.04.2024.
//

#ifndef CADSI_FILEDATAPROVIDER_HPP
#define CADSI_FILEDATAPROVIDER_HPP

#include <string>
#include "../FileDataErrors.hpp"

namespace cadsi_lib::file_data::providers {
    template<typename T>
    class FileDataProvider {
    public:
        virtual ~FileDataProvider() = default;

        virtual Result<T> getFileData(std::string_view file_path) = 0;
    };
}

#endif    //CADSI_FILEDATAPROVIDER_HPP
