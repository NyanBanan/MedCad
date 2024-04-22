//
// Created by nyanbanan on 06.04.2024.
//

#ifndef CADSI_RESULT_HPP
#define CADSI_RESULT_HPP

#include <concepts>
#include <string>
#include "OperationStatus.hpp"

namespace cadsi_lib {
    template<typename T>
    requires std::movable<T> || std::is_trivial_v<T>
    struct [[nodiscard("Return value for check operation success")]] Result {
        OperationStatus status{};
        [[msvc::no_unique_address]] T data;
    };
}
#endif    //CADSI_RESULT_HPP
