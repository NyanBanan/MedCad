#Function for copy dynamic dependencies to project
#Set additional environment variables (for example, JPEG_REQUIRED) before calling this function and delete them after if you need these plugins
function(copy_required_dlls target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
            COMMAND_EXPAND_LISTS
    )
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${target}>/plugins/platforms/")
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${target}>/plugins/platforms/")
    endif ()
    if (JPEG_REQUIRED)
        if (EXISTS "${QT_INSTALL_PATH}/plugins/imageformats/qjpeg${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${target}>/plugins/imageformats/")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/imageformats/qjpeg${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target}>/plugins/imageformats/")
        endif ()
    endif ()
    if (SQLITE_REQUIRED)
        if (EXISTS "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlite${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${target}>/plugins/sqldrivers/")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/sqldrivers/qsqlite${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target}>/plugins/sqldrivers/")
        endif ()
    endif ()
endfunction()

function(fetch_dependencies dep_name repository tag)
    #commands to download and add yaml-cpp to project
    include(FetchContent)

    FetchContent_Declare(
            ${dep_name}
            GIT_REPOSITORY ${repository}
            GIT_TAG ${tag}
    )
    FetchContent_GetProperties(${dep_name})

    if (NOT ${dep_name}_POPULATED)
        message(STATUS "Fetching ${dep_name}...")
        FetchContent_Populate(${dep_name})
        add_subdirectory(${${dep_name}_SOURCE_DIR} ${${dep_name}_BINARY_DIR})
    endif ()
endfunction()