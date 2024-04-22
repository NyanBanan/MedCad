//
// Created by nyanbanan on 21.04.2024.
//

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QStringDecoder>
#include <QWindow>
#include <cadsi_lib/dicom/PreviewImage.hpp>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>
#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>
#include <cadsi_lib/volumes/providers/YamlVolumesProvider.hpp>
#include <vtkDICOMCTRectifier.h>

#include "cadsi_lib/file_data/providers/YamlFileDataProvider.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "usage: example_PreviewImageLookup \'path to dicom directory\'" << std::endl;
        return -1;
    }

    //Get YAML data from file
    cadsi_lib::file_data::providers::YamlFileDataProvider file_data;
    auto volumes_node_load_res = file_data.getFileData("../data/volume.yml");
    if (!volumes_node_load_res.status.success) {
        auto status = volumes_node_load_res.status;
        std::cout << "Get YAML data from file error: " << status.error_message << std::endl;
        return -1;
    }
    auto* volumes_provider = new cadsi_lib::volumes::providers::YamlVolumesProvider;
    auto volumes_load_res = volumes_provider->deserialize(volumes_node_load_res.data);
    if (!volumes_load_res.success) {
        std::cout << "Load volumes data from YAML error: " << volumes_load_res.error_message << std::endl;
        return -1;
    }
    std::cout << std::endl;

    //We are installing a global provider for automatic configuration of volumetric objects used in the construction of previews
    cadsi_lib::volumes::providers::GlobalVolumeProvider::setGlobalVolumesProvider(volumes_provider);

    //Windows paths with russian symbols might cause problems. Dir may be recognized as not existing. That's why I decode input
    auto to_utf8 = QStringDecoder(QStringDecoder::System);
    QFileInfo path{to_utf8(argv[1])};

    vtkNew<vtkDICOMDirectory> dicomdir;
    dicomdir->RequirePixelDataOn();
    dicomdir->SetDirectoryName(path.absoluteFilePath().toStdString().c_str());
    dicomdir->Update();

    // find the series with the largest number of files
    int m = dicomdir->GetNumberOfStudies();
    int seriesIdx = 0;
    int kmax = 0;
    for (int i = 0; i < m; i++)
    {
        int fj = dicomdir->GetFirstSeriesForStudy(i);
        int lj = dicomdir->GetLastSeriesForStudy(i);
        for (int j = fj; j <= lj; j++)
        {
            int k = dicomdir->GetFileNamesForSeries(j)->GetNumberOfValues();
            if (k > kmax)
            {
                kmax = k;
                seriesIdx = j;
            }
        }
    }

    // exit if no files found
    if (kmax == 0)
    {
        std::cout<<"No PixelData to display!"<<std::endl;
        return -1;
    }

    vtkNew<vtkDICOMReader> series_data_reader;
    auto files = dicomdir->GetFileNamesForSeries(seriesIdx);
    files->Print(std::cout);
    series_data_reader->SetFileNames(files);
    series_data_reader->SetMemoryRowOrderToFileNative();
    series_data_reader->Update();

    vtkAlgorithmOutput* portToDisplay = series_data_reader->GetOutputPort();
    vtkMatrix4x4* matrix = series_data_reader->GetPatientMatrix();

    vtkDICOMMetaData* meta = series_data_reader->GetMetaData();
    vtkNew<vtkDICOMCTRectifier> rect;
    if (meta->Get(DC::Modality).Matches("CT")) {
        rect->SetVolumeMatrix(matrix);
        rect->SetInputConnection(portToDisplay);
        rect->Update();
        portToDisplay = rect->GetOutputPort();
        matrix = rect->GetRectifiedMatrix();
    }

    auto image_data = cadsi_lib::dicom::PreviewImage::generatePreviewImage(matrix, portToDisplay);

    auto qimage = cadsi_lib::dicom::PreviewImage::vtkImageDataToQImage(image_data);

    QApplication app{argc, argv};
    QMainWindow window;
    QLabel label;
    QPixmap pixmap;
    pixmap.convertFromImage(qimage);
    label.setPixmap(pixmap);
    label.resize(label.pixmap().size());

    window.setCentralWidget(&label);
    window.show();

    return app.exec();
}
