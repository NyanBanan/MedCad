add_executable(tst_YamlColorsProvider
        ${CMAKE_CURRENT_LIST_DIR}/tst_YamlColorsProvider.cpp)

add_test(NAME tst_YamlColorsProvider COMMAND tst_YamlColorsProvider)

target_link_libraries(tst_YamlColorsProvider PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(tst_YamlColorsProvider)
endif ()

#target_include_directories(tst_YamlColorsProvider PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)