add_executable(example_FilesystemAndSqlDicom
        ${CMAKE_CURRENT_LIST_DIR}/example_FilesystemAndSqlDicom.cpp)

target_link_libraries(example_FilesystemAndSqlDicom PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(SQLITE_REQUIRED TRUE)
    copy_required_dlls(example_FilesystemAndSqlDicom)
    unset(SQLITE_REQUIRED)
endif ()