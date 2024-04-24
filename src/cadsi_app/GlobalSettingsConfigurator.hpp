//
// Created by nyanbanan on 24.04.2024.
//

#ifndef CADSI_GLOBALSETTINGSCONFIGURATOR_HPP
#define CADSI_GLOBALSETTINGSCONFIGURATOR_HPP

#include <QFileInfo>
#include <QString>
#include <cadsi_lib/OperationStatus.hpp>
#include <cadsi_lib/Result.hpp>
#include <cadsi_lib/color_maps/providers/GlobalColorMapsProvider.hpp>
#include <cadsi_lib/color_maps/providers/YamlColorMapsProvider.hpp>
#include <cadsi_lib/colors/providers/GlobalColorsProvider.hpp>
#include <cadsi_lib/colors/providers/YamlColorsProvider.hpp>
#include <cadsi_lib/file_data/providers/YamlFileDataProvider.hpp>
#include <cadsi_lib/volumes/providers/GlobalVolumeProvider.hpp>
#include <cadsi_lib/volumes/providers/YamlVolumesProvider.hpp>

class GlobalSettingsConfigurator {
public:
    static cadsi_lib::OperationStatus setColorDataFile(const QString& colorDataFile);
    static cadsi_lib::OperationStatus setColorMapsDataFile(const QString& colorMapsDataFile);
    static cadsi_lib::OperationStatus setVolumesDataFile(const QString& volumesDataFile);

private:
    static cadsi_lib::OperationStatus checkFile(const QFileInfo& file_info);

    static inline QString _color_data_file;
    static inline QString _color_maps_data_file;
    static inline QString _volumes_data_file;
};

#endif    //CADSI_GLOBALSETTINGSCONFIGURATOR_HPP
