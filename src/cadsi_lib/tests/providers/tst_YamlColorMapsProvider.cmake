add_executable(tst_YamlColorMapsProvider
        ${CMAKE_CURRENT_LIST_DIR}/tst_YamlColorMapsProvider.cpp)

add_test(NAME tst_YamlColorMapsProvider COMMAND tst_YamlColorMapsProvider)

target_link_libraries(tst_YamlColorMapsProvider PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(tst_YamlColorMapsProvider)
endif ()
#target_include_directories(tst_YamlColorMapsProvider PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)