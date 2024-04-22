set(DEFAULT_TEST_LIBS ${QT_LIBRARIES} Qt6::Test ${VTK_LIBRARIES} cadsi_lib)

include(src/example_ParseYmlColorsFiles.cmake)
include(src/example_ParseYmlColorMapsFiles.cmake)
include(src/example_ParseYmlVolumesFiles.cmake)
include(src/example_ParseDicomDirData.cmake)
include(src/example_SqliteDicom.cmake)
include(src/example_FilesystemAndSqlDicom.cmake)
include(src/example_PreviewImageLookup.cmake)

