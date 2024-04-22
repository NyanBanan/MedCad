add_executable(example_ParseYmlColorsFiles
        ${CMAKE_CURRENT_LIST_DIR}/example_ParseYmlColorsFiles.cpp)

target_link_libraries(example_ParseYmlColorsFiles PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(example_ParseYmlColorsFiles)
endif ()

#target_include_directories(tst_YamlColorsProvider PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)