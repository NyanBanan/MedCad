//
// Created by nyanbanan on 01.05.2024.
//

#include "Preprocessor.hpp"

#include <vtkDICOMCTRectifier.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMReader.h>

Preprocessor::Preprocessor(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    connect(_ui.colormap, &ColorMap::error, &_error_win, &ErrorMessageBox::showMessage);

    connect(this, &Preprocessor::lutChanged, _ui.colormap, &ColorMap::lutChanged);
    connect(this, &Preprocessor::lutChanged, _ui.planeview, &PlaneView::setLut);
    connect(_ui.imageOrientationComboBox, &QComboBox::currentIndexChanged, _ui.planeview, &PlaneView::setOrientationFromInt);

    std::ranges::for_each(QList{"SAGITTAL", "CORONAL", "AXIAL"}, [this](auto orientation) {
        _ui.imageOrientationComboBox->addItem(orientation);
    });

    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto names = global_color_maps_provider.toStrongRef()->colorMapsNames();
        setColorMapsNames(names);
    }

    _ui.splitter->setStretchFactor(0,1);
    _ui.splitter->setStretchFactor(1,0);
}

void Preprocessor::on_colorMapsComboBox_currentTextChanged(const QString& text) {
    auto global_color_maps_provider =
        cadsi_lib::color_maps::providers::GlobalColorMapsProvider::getGlobalColorMapsProvider();
    if (global_color_maps_provider) {
        auto lut = global_color_maps_provider.toStrongRef()->getLUT(text);
        emit lutChanged(lut);
    } else {
        _error_win.showMessage("global color provider not initialized");
    }
}

void Preprocessor::setColorMapsNames(const QList<QString>& names) {
    std::ranges::for_each(names, [this](auto name) {
        _ui.colorMapsComboBox->addItem(name);
    });
    _ui.colormap->setColorMapNames(names);
}

void Preprocessor::loadImage(vtkStringArray* image_file_names) {
    vtkNew<vtkDICOMReader> series_data_reader;

    series_data_reader->SetFileNames(image_file_names);
    series_data_reader->SetMemoryRowOrderToFileNative();
    series_data_reader->Update();

    //    vtkAlgorithmOutput* portToDisplay = series_data_reader->GetOutputPort();
    //    vtkMatrix4x4* matrix = series_data_reader->GetPatientMatrix();
    //
    //    vtkDICOMMetaData* meta = series_data_reader->GetMetaData();
    //    vtkNew<vtkDICOMCTRectifier> rect;
    //    if (meta->Get(DC::Modality).Matches("CT")) {
    //        rect->SetVolumeMatrix(matrix);
    //        rect->SetInputConnection(portToDisplay);
    //        rect->Update();
    //        portToDisplay = rect->GetOutputPort();
    //    }
    _ui.planeview->loadImage(series_data_reader->GetOutput());
}
