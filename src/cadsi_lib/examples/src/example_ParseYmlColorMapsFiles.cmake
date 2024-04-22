add_executable(example_ParseYmlColorMapsFiles
        ${CMAKE_CURRENT_LIST_DIR}/example_ParseYmlColorMapsFiles.cpp)

target_link_libraries(example_ParseYmlColorMapsFiles PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(example_ParseYmlColorMapsFiles)
endif ()

#target_include_directories(tst_YamlColorsProvider PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)