//
// Created by nyanbanan on 05.05.2024.
//

#include "cadsi_lib/volumes/VolumeImageTransformations.hpp"

namespace cadsi_lib::volumes {
    void VolumeImageTransformations::smoothInplace(vtkImageData* image, double sigma, double r) {
        image->DeepCopy(smooth(image, sigma, r));
    }

    vtkImageData* VolumeImageTransformations::smooth(vtkImageData* image, double sigma, double r) {
        vtkNew<vtkImageGaussianSmooth> smooth;
        smooth->SetInputData(image);
        smooth->SetDimensionality(3);
        smooth->SetRadiusFactor(r);
        smooth->SetStandardDeviation(sigma);
        smooth->Update();

        return smooth->GetOutput();
    }

    void VolumeImageTransformations::denoiseInplace(vtkImageData* image,
                                                    double factor,
                                                    double threshold) {
        image->DeepCopy(denoise(image, factor, threshold));
    }

    vtkImageData* VolumeImageTransformations::denoise(vtkImageData* image,
                                                      double factor,
                                                      double threshold) {
        vtkNew<vtkImageAnisotropicDiffusion2D> denoise;
        denoise->SetInputData(image);
        denoise->SetDiffusionFactor(factor);
        denoise->SetDiffusionThreshold(threshold);
        denoise->Update();

        return denoise->GetOutput();
    }

    void VolumeImageTransformations::enhanceInplace(vtkImageData* image) {
        image->DeepCopy(enhance(image));
    }

    vtkImageData* VolumeImageTransformations::enhance(vtkImageData* image) {
        // Обработку будем выполнять в формате double
        vtkNew<vtkImageCast> cast;
        cast->SetInputData(image);
        cast->SetOutputScalarTypeToDouble();
        cast->Update();

        // Считаем лаплассиан
        vtkNew<vtkImageLaplacian> laplacian;
        laplacian->SetInputData(cast->GetOutput());
        laplacian->SetDimensionality(3);
        laplacian->Update();

        // Вычитаем лаплассиан из изображения
        vtkNew<vtkImageMathematics> enhance;
        enhance->SetInputData(0, cast->GetOutput());
        enhance->SetInputData(1, laplacian->GetOutput());
        enhance->SetOperationToSubtract();
        enhance->Update();

        return enhance->GetOutput();
    }

    void VolumeImageTransformations::flipInplace(vtkImageData* image,
                                                 VolumeImageTransformations::FlipAxis axis) {
        image->DeepCopy(flip(image, axis));
    }

    vtkImageData* VolumeImageTransformations::flip(vtkImageData* image,
                                                   VolumeImageTransformations::FlipAxis axis) {
        vtkNew<vtkImageFlip> flip;
        flip->SetFilteredAxis(static_cast<int>(axis));
        flip->SetInputData(image);
        flip->Update();
        return flip->GetOutput();
    }
}    //namespace cadsi_lib::volumes
