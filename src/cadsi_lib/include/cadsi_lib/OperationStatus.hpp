//
// Created by nyanbanan on 24.02.2024.
//

#ifndef CADSI_OPERATIONSTATUS_HPP
#define CADSI_OPERATIONSTATUS_HPP

#include <string>

namespace cadsi_lib {
    struct [[nodiscard("Return value for check operation success")]] OperationStatus {
        bool success{false};
        [[msvc::no_unique_address]] unsigned int error_code{0};
        [[msvc::no_unique_address]] std::string error_message{};
    };
}    //namespace cadsi_lib

#endif    //CADSI_OPERATIONSTATUS_HPP
