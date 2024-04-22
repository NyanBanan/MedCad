add_executable(example_PreviewImageLookup
        ${CMAKE_CURRENT_LIST_DIR}/example_PreviewImageLookup.cpp)

target_link_libraries(example_PreviewImageLookup PRIVATE ${DEFAULT_TEST_LIBS} yaml-cpp::yaml-cpp)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    copy_required_dlls(example_PreviewImageLookup)
endif ()