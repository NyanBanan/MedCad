add_executable(example_SqliteDicom
        ${CMAKE_CURRENT_LIST_DIR}/example_SqliteDicom.cpp)

target_link_libraries(example_SqliteDicom PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(SQLITE_REQUIRED TRUE)
    copy_required_dlls(example_SqliteDicom)
    unset(SQLITE_REQUIRED)
endif ()