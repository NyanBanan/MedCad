//
// Created by nyanbanan on 13.04.2024.
//

#ifndef CADSI_FILEDATAERRORS_HPP
#define CADSI_FILEDATAERRORS_HPP
namespace cadsi_lib::file_data {
    /*!
         \brief Error codes for return in Result::error_code
            */
    enum ErrorCodes {
        WRONG_FILE_FORMAT = 303,
        FILE_NOT_EXIST = 404,
        BAD_FILE,
        PARSE_ERROR
    };
}
#endif    //CADSI_FILEDATAERRORS_HPP
