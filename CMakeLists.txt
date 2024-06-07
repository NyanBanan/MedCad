cmake_minimum_required(VERSION 3.5)
project(cadsi)

set(CMAKE_CXX_STANDARD 20)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt-6.6.3-debug\\lib\\cmake")
    set(VTK_DIR "C:\\Program Files (x86)\\VTK-debug\\lib\\cmake")

    message(STATUS "BUILD TYPE DEBUG")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt-6.6.3\\lib\\cmake")
    set(VTK_DIR "C:\\Program Files (x86)\\VTK\\lib\\cmake")
    message(STATUS "BUILD TYPE RELEASE")
else ()
    message(FATAL_ERROR "Basically support only release and debug builds")
endif ()

cmake_policy(SET CMP0071 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test Qml Quick Sql)

#Uncomment and use if QT_LIBRARIES are not working
#set(${Qt6_LIBRARIES} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::Qml Qt6::Quick)

find_package(VTK REQUIRED HINTS ${VTK_DIR})

qt_add_executable(cadsi src/cadsi_app/main.cpp resources/resources.qrc
        src/cadsi_app/ui_files/patientcard.ui
        src/cadsi_app/ui_files/slicemetadata.ui
        src/cadsi_app/PatientCard.cpp
        src/cadsi_app/SliceMetadata.cpp
        src/cadsi_app/dicom/DICOMDatabaseDialog.cpp
        src/cadsi_app/dicom/DICOMDatabaseDialog.hpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModel.cpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModel.hpp
        src/cadsi_app/dicom/DICOMSliceMetaDataObject.cpp
        src/cadsi_app/dicom/DICOMSliceMetaDataObject.hpp
        src/cadsi_app/dicom/models/DICOMPatientTableModel.cpp
        src/cadsi_app/dicom/models/DICOMPatientTableModel.hpp
        src/cadsi_app/dicom/DICOMFromFilesToSqlMapper.cpp
        src/cadsi_app/dicom/DICOMFromFilesToSqlMapper.hpp
        src/cadsi_app/dicom/CadsiLibDicomDeclareMetatype.hpp
        src/cadsi_app/dicom/DICOMSeriesListWidgetItem.cpp
        src/cadsi_app/dicom/DICOMSeriesListWidgetItem.hpp
        src/cadsi_app/GlobalSettingsConfigurator.cpp
        src/cadsi_app/GlobalSettingsConfigurator.hpp
        src/cadsi_app/dicom/DICOMScanDialog.cpp
        src/cadsi_app/dicom/DICOMScanDialog.hpp
        src/cadsi_app/dicom/models/DICOMData.cpp
        src/cadsi_app/dicom/models/DICOMData.hpp
        src/cadsi_app/dicom/models/DICOMSeriesListModel.cpp
        src/cadsi_app/dicom/models/DICOMSeriesListModel.hpp
        src/cadsi_app/dicom/models/DICOMModel.cpp
        src/cadsi_app/dicom/models/DICOMModel.hpp
        src/cadsi_app/dicom/models/DICOMSliceTableModel.cpp
        src/cadsi_app/dicom/models/DICOMSliceTableModel.hpp
        src/cadsi_app/ErrorMessageBox.cpp
        src/cadsi_app/ErrorMessageBox.hpp
        src/cadsi_app/Preprocessor.cpp
        src/cadsi_app/DensityWindowSliderWidget.cpp
        src/cadsi_app/DensityWindowSliderWidget.hpp
        src/cadsi_app/ScalarBarWidget.cpp
        src/cadsi_app/ScalarBarWidget.hpp
        src/cadsi_app/PlaneView.cpp
        src/cadsi_app/PlaneView.hpp
        src/cadsi_app/ImageObject.cpp
        src/cadsi_app/ImageObject.hpp
        src/cadsi_app/ColorMap.cpp
        src/cadsi_app/ColorMap.hpp
        src/cadsi_app/dicom/DICOMPlaneViewer.cpp
        src/cadsi_app/dicom/DICOMPlaneViewer.hpp
        src/cadsi_app/PreprocessorTransformationsPipe.cpp
        src/cadsi_app/PreprocessorTransformationsPipe.hpp
)

if (NOT DEFINED CMAKE_UTILS_FILE)
    set(CMAKE_UTILS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/UtilFunctions.cmake")
endif ()

add_subdirectory(src/cadsi_lib)

target_link_libraries(cadsi PRIVATE ${QT_LIBRARIES} ${VTK_LIBRARIES} yaml-cpp::yaml-cpp cadsi_lib)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_UTILS_FILE})
    set(JPEG_REQUIRED TRUE)
    set(SQLITE_REQUIRED TRUE)
    copy_required_dlls(cadsi)
    unset(SQLITE_REQUIRED)
    unset(JPEG_REQUIRED)
endif ()

#Copy default settings data to build directory
add_custom_command(TARGET cadsi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/src/cadsi_lib/data $<TARGET_FILE_DIR:cadsi>/settings
        COMMAND_EXPAND_LISTS
)

vtk_module_autoinit(TARGETS cadsi MODULES ${VTK_LIBRARIES})

target_include_directories(cadsi PRIVATE src)