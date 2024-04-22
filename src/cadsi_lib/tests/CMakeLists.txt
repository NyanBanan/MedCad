set(DEFAULT_TEST_LIBS ${QT_LIBRARIES} Qt6::Test ${VTK_LIBRARIES} cadsi_lib)

include(providers/tst_YamlColorMapsProvider.cmake)
include(providers/tst_YamlColorsProvider.cmake)
include(providers/tst_YamlVolumesProvider.cmake)