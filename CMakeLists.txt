cmake_minimum_required(VERSION 3.5)
project(cadsi)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt-6.6.3-debug\\lib\\cmake")

cmake_policy(SET CMP0071 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test Qml Quick)
find_package(VTK REQUIRED)

qt_add_executable(cadsi src/main.cpp resources/resources.qrc
        src/cadsi_app/ui_files/patientcard.ui
        src/cadsi_app/ui_files/slicemetadata.ui
        src/cadsi_app/PatientCard.cpp
        src/cadsi_app/SliceMetadata.cpp
        src/cadsi_app/dicom/DICOMDatabaseDialog.cpp
        src/cadsi_app/dicom/DICOMDatabaseDialog.hpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModel.cpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModel.hpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModelObject.cpp
        src/cadsi_app/dicom/DICOMImageMetaDataTableModelObject.hpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableModel.cpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableModel.hpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableModelObject.cpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableModelObject.hpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableDelegate.cpp
        src/cadsi_app/dicom/DICOMPatientMetaDataTableDelegate.hpp)

if(NOT DEFINED CMAKE_UTILS_FILE)
    set(CMAKE_UTILS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/UtilFunctions.cmake")
endif ()

#
#qt_add_qml_module(cadsi
#VERSION 1.0
#URI Module
#RESOURCE_PREFIX /
#        SOURCES
#        src/Test.cpp
#QML_FILES
#src/main.qml)

add_subdirectory(src/cadsi_lib)

target_link_libraries(cadsi PRIVATE ${QT_LIBRARIES} ${VTK_LIBRARIES} cadsi_lib)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_UTILS_FILE})
    set(JPEG_REQUIRED TRUE)
    copy_required_dlls(cadsi)
    unset(JPEG_REQUIRED)
endif ()

vtk_module_autoinit(TARGETS cadsi MODULES ${VTK_LIBRARIES})

target_include_directories(cadsi PRIVATE src)