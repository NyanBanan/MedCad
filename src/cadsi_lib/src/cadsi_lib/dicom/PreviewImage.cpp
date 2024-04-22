//
// Created by nyanbanan on 21.04.2024.
//

#include "cadsi_lib/dicom/PreviewImage.hpp"

namespace cadsi_lib::dicom {
    vtkSmartPointer<vtkImageData> PreviewImage::generatePreviewImage(vtkMatrix4x4* patient_matrix,
                                                                     vtkAlgorithmOutput* data_input) {
        vtkNew<vtkRenderer> renderer;
        vtkNew<vtkRenderWindow> render_win;
        render_win->SetOffScreenRendering(1);
        render_win->AddRenderer(renderer);
        render_win->SetSize(512, 512);

        vtkNew<volumes::VolumeObject> actor;
        actor->GetMapper()->SetInputConnection(data_input);
        actor->SetUserMatrix(patient_matrix);
        actor->RotateX(-90);
        actor->SetPosition(0, 30, -300);

        auto camera = renderer->GetActiveCamera();
        camera->SetViewUp(actor->GetPosition());

        renderer->AddActor(actor);

        render_win->Render();

        vtkNew<vtkWindowToImageFilter> win_to_image;
        win_to_image->SetInput(render_win);
        win_to_image->Update();

        renderer->RemoveActor(actor);

        return win_to_image->GetOutput();
    }

    QImage PreviewImage::vtkImageDataToQImage(vtkImageData* image_data) {
        if (!image_data || !image_data->GetPointData() || !image_data->GetPointData()->GetScalars()
            || image_data->GetScalarType() != VTK_UNSIGNED_CHAR) {
            return {};
        }
        int width = image_data->GetDimensions()[0];
        int height = image_data->GetDimensions()[1];
        vtkIdType numberOfScalarComponents = image_data->GetNumberOfScalarComponents();
        QImage image;
        if (numberOfScalarComponents == 3) {
            image = QImage(width, height, QImage::Format_RGB888);
        } else if (numberOfScalarComponents == 4) {
            image = QImage(width, height, QImage::Format_RGBA8888);
        }
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        else if (numberOfScalarComponents == 1) {
            image = QImage(width, height, QImage::Format_Grayscale8);
        }
#endif
        else {
            // unsupported pixel format
            return {};
        }

        unsigned char* qtImageBuffer = image.bits();
        memcpy(qtImageBuffer,
               image_data->GetPointData()->GetScalars()->GetVoidPointer(0),
               numberOfScalarComponents * width * height);

        // Qt image is upside-down compared to VTK, so return mirrored image
        return image.mirrored();
    }
}    //namespace cadsi_lib::dicom
