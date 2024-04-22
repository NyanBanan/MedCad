add_executable(tst_YamlVolumesProvider
        ${CMAKE_CURRENT_LIST_DIR}/tst_YamlVolumesProvider.cpp)

add_test(NAME tst_YamlVolumesProvider COMMAND tst_YamlVolumesProvider)

target_link_libraries(tst_YamlVolumesProvider PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(tst_YamlVolumesProvider)
endif ()

#target_include_directories(tst_YamlColorsProvider PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)