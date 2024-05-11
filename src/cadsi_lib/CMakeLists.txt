cmake_minimum_required(VERSION 3.5)
project(cadsi)

if (NOT DEFINED CMAKE_UTILS_FILE)
    set(CMAKE_UTILS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/UtilFunctions.cmake")
endif ()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test Qml Quick Sql)
#Uncomment and use if QT_LIBRARIES are not working
#set(${Qt6_LIBRARIES} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::Qml Qt6::Quick Qt6::Sql)
find_package(VTK REQUIRED)

add_library(cadsi_lib
        include/cadsi_lib/OperationStatus.hpp
        include/cadsi_lib/colors/providers/ColorsProvider.hpp
        include/cadsi_lib/color_maps/providers/ColorMapsProvider.hpp
        include/cadsi_lib/volumes/providers/VolumesProvider.hpp
        src/cadsi_lib/color_maps/providers/ColorMapsProvider.cpp
        src/cadsi_lib/volumes/providers/VolumesProvider.cpp
        src/cadsi_lib/colors/providers/YamlColorsProvider.cpp
        src/cadsi_lib/color_maps/providers/YamlColorMapsProvider.cpp
        src/cadsi_lib/volumes/providers/YamlVolumesProvider.cpp
        include/cadsi_lib/volumes/providers/YamlVolumesProvider.hpp
        include/cadsi_lib/Result.hpp
        src/cadsi_lib/logs/CadsiLogger.cpp
        include/cadsi_lib/logs/CadsiLogger.hpp
        include/cadsi_lib/file_data/providers/FileDataProvider.hpp
        src/cadsi_lib/file_data/providers/YamlFileDataProvider.cpp
        include/cadsi_lib/file_data/providers/YamlFileDataProvider.hpp
        src/cadsi_lib/geometry/Plane.cpp
        include/cadsi_lib/geometry/Plane.hpp
        src/cadsi_lib/geometry/Vector3d.cpp
        include/cadsi_lib/geometry/Vector3d.hpp
        src/cadsi_lib/geometry/Point3d.cpp
        include/cadsi_lib/geometry/Point3d.hpp
        include/cadsi_lib/geometry/Vector3d.hpp
        include/cadsi_lib/geometry/Point3d.hpp
        src/cadsi_lib/geometry/Point3d.cpp
        include/cadsi_lib/geometry/Plane.hpp
        include/cadsi_lib/dicom/providers/DicomProvider.hpp
        include/cadsi_lib/dicom/writers/DicomWriter.hpp
        src/cadsi_lib/dicom/providers/FileDataDicomProvider.cpp
        include/cadsi_lib/dicom/providers/FileDataDicomProvider.hpp
        src/cadsi_lib/dicom/DicomImage.cpp
        include/cadsi_lib/dicom/DicomImage.hpp
        src/cadsi_lib/dicom/DicomSeries.cpp
        include/cadsi_lib/dicom/DicomSeries.hpp
        src/cadsi_lib/dicom/DicomPatient.cpp
        include/cadsi_lib/dicom/DicomPatient.hpp
        include/cadsi_lib/file_data/FileDataErrors.hpp
        include/cadsi_lib/dicom/DicomTagStdHashSpecialization.hpp
        src/cadsi_lib/dicom/DicomMetaDataHashCollection.cpp
        include/cadsi_lib/dicom/DicomMetaDataHashCollection.hpp
        src/cadsi_lib/dicom/DicomDataBase.cpp
        include/cadsi_lib/dicom/DicomDataBase.hpp
        src/cadsi_lib/dicom/SqliteDicomDataBase.cpp
        include/cadsi_lib/dicom/SqliteDicomDataBase.hpp
        src/cadsi_lib/dicom/SqliteDicomDataMapper.cpp
        include/cadsi_lib/dicom/SqliteDicomDataMapper.hpp
        src/cadsi_lib/geometry/Mesh.cpp
        include/cadsi_lib/volumes/VolumeRenderParams.hpp
        src/cadsi_lib/volumes/VolumeRenderParams.cpp
        include/cadsi_lib/volumes/VolumeErrorCodes.hpp
        src/cadsi_lib/volumes/VolumeImage.cpp
        include/cadsi_lib/volumes/VolumeImage.hpp
        src/cadsi_lib/volumes/VolumeObject.cpp
        include/cadsi_lib/volumes/VolumeObject.hpp
        src/cadsi_lib/dicom/PreviewImage.cpp
        include/cadsi_lib/dicom/PreviewImage.hpp
        src/cadsi_lib/volumes/providers/GlobalVolumeProvider.cpp
        include/cadsi_lib/volumes/providers/GlobalVolumeProvider.hpp
        src/cadsi_lib/dicom/DicomSqlTablesInspector.cpp
        include/cadsi_lib/dicom/DicomSqlTablesInspector.hpp
        src/cadsi_lib/colors/providers/GlobalColorsProvider.cpp
        include/cadsi_lib/colors/providers/GlobalColorsProvider.hpp
        src/cadsi_lib/color_maps/providers/GlobalColorMapsProvider.cpp
        include/cadsi_lib/color_maps/providers/GlobalColorMapsProvider.hpp
        src/cadsi_lib/dicom/cadsiDicomDataElement.cpp
        include/cadsi_lib/dicom/cadsiDicomDataElement.hpp
        src/cadsi_lib/volumes/VolumeImageTransformations.cpp
        include/cadsi_lib/volumes/VolumeImageTransformations.hpp
)

include(${CMAKE_UTILS_FILE})

fetch_dependencies(yaml-cpp https://github.com/jbeder/yaml-cpp.git 0.8.0)
fetch_dependencies(spdlog https://github.com/gabime/spdlog.git v1.13.0)

target_link_libraries(cadsi_lib PRIVATE ${QT_LIBRARIES} ${VTK_LIBRARIES} yaml-cpp::yaml-cpp spdlog::spdlog)
target_include_directories(cadsi_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

set(ENABLE_TESTING TRUE)
if (ENABLE_TESTING)
    enable_testing(true)
    add_subdirectory(tests)
endif ()

set(BUILD_EXAMPLES TRUE)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

#Copy default lib data to build directory
add_custom_command(TARGET cadsi_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data $<TARGET_FILE_DIR:cadsi_lib>/data
        COMMAND_EXPAND_LISTS
)

vtk_module_autoinit(TARGETS cadsi_lib MODULES ${VTK_LIBRARIES})