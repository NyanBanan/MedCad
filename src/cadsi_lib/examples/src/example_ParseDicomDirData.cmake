add_executable(example_ParseDicomFileData
        ${CMAKE_CURRENT_LIST_DIR}/example_ParseDicomDirData.cpp)

target_link_libraries(example_ParseDicomFileData PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(example_ParseDicomFileData)
endif ()