//
// Created by nyanbanan on 24.04.2024.
//

#include "GlobalSettingsConfigurator.hpp"

cadsi_lib::OperationStatus GlobalSettingsConfigurator::setColorDataFile(const QString& colorDataFile) {
    if (_color_data_file != colorDataFile) {
        QFileInfo file_info(colorDataFile);
        auto file_check_res = checkFile(file_info);
        if (!file_check_res.success) {
            return file_check_res;
        }
        auto extension = file_info.completeSuffix();
        if (extension == "yml") {
            cadsi_lib::file_data::providers::YamlFileDataProvider yml_data_provider;
            auto yml_data_res = yml_data_provider.getFileData(colorDataFile.toStdString());
            if (!yml_data_res.status.success) {
                return yml_data_res.status;
            }

            auto yml_colors_provider = new cadsi_lib::colors::providers::YamlColorsProvider;

            auto deserialize_res = yml_colors_provider->deserialize(yml_data_res.data);
            if (!deserialize_res.success) {
                return deserialize_res;
            }

            cadsi_lib::colors::providers::GlobalColorsProvider::setGlobalColorsProvider(yml_colors_provider);

            _color_data_file = colorDataFile;
        } else {
            return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT, "supported extensions: yml"};
        }
    }
    return {true};
}

cadsi_lib::OperationStatus GlobalSettingsConfigurator::setColorMapsDataFile(const QString& colorMapsDataFile) {
    if (_color_maps_data_file != colorMapsDataFile) {
        QFileInfo file_info(colorMapsDataFile);
        auto file_check_res = checkFile(file_info);
        if (!file_check_res.success) {
            return file_check_res;
        }
        auto extension = file_info.completeSuffix();
        if (extension == "yml") {
            cadsi_lib::file_data::providers::YamlFileDataProvider yml_data_provider;
            auto yml_data_res = yml_data_provider.getFileData(colorMapsDataFile.toStdString());
            if (!yml_data_res.status.success) {
                return yml_data_res.status;
            }

            auto yml_color_maps_provider = new cadsi_lib::color_maps::providers::YamlColorMapsProvider;

            auto deserialize_res = yml_color_maps_provider->deserialize(yml_data_res.data);
            if (!deserialize_res.success) {
                return deserialize_res;
            }

            cadsi_lib::color_maps::providers::GlobalColorMapsProvider::setGlobalColorMapsProvider(yml_color_maps_provider);

            _color_maps_data_file = colorMapsDataFile;
        } else {
            return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT, "supported extensions: yml"};
        }
    }
    return {true};
}

cadsi_lib::OperationStatus GlobalSettingsConfigurator::setVolumesDataFile(const QString& volumesDataFile) {
    if (_volumes_data_file != volumesDataFile) {
        QFileInfo file_info(volumesDataFile);
        auto file_check_res = checkFile(file_info);
        if (!file_check_res.success) {
            return file_check_res;
        }
        auto extension = file_info.completeSuffix();
        if (extension == "yml") {
            cadsi_lib::file_data::providers::YamlFileDataProvider yml_data_provider;
            auto yml_data_res = yml_data_provider.getFileData(volumesDataFile.toStdString());
            if (!yml_data_res.status.success) {
                return yml_data_res.status;
            }

            auto yml_volumes_provider = new cadsi_lib::volumes::providers::YamlVolumesProvider;

            auto deserialize_res = yml_volumes_provider->deserialize(yml_data_res.data);
            if (!deserialize_res.success) {
                return deserialize_res;
            }

            cadsi_lib::volumes::providers::GlobalVolumeProvider::setGlobalVolumesProvider(yml_volumes_provider);

            _volumes_data_file = volumesDataFile;
        } else {
            return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT, "supported extensions: yml"};
        }
    }
    return {true};
}

cadsi_lib::OperationStatus GlobalSettingsConfigurator::checkFile(const QFileInfo& file_info) {
    if (!file_info.exists()) {
        return {false, cadsi_lib::file_data::ErrorCodes::FILE_NOT_EXIST, "file not exist"};
    } else if (!file_info.isFile()) {
        return {false, cadsi_lib::file_data::ErrorCodes::WRONG_FILE_FORMAT, "must be a file"};
    }
    return {true};
}
