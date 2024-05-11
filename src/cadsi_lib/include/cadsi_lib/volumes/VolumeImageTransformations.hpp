//
// Created by nyanbanan on 05.05.2024.
//

#ifndef CADSI_VOLUMEIMAGETRANSFORMATIONS_HPP
#define CADSI_VOLUMEIMAGETRANSFORMATIONS_HPP

#include <vtkImageAnisotropicDiffusion2D.h>
#include <vtkImageCast.h>
#include <vtkImageFlip.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageLaplacian.h>
#include <vtkImageMathematics.h>

#include "cadsi_lib/volumes/VolumeImage.hpp"

namespace cadsi_lib::volumes {
    class VolumeImageTransformations {
    public:
        enum FlipAxis {
            X,
            Y,
            Z
        };

        VolumeImageTransformations() = delete;

        static void smoothInplace(vtkImageData* image, double sigma, double r);
        static vtkImageData* smooth(vtkImageData* image, double sigma, double r);

        static void denoiseInplace(vtkImageData* image, double factor, double threshold);
        static vtkImageData* denoise(vtkImageData* image, double factor, double threshold);

        static void enhanceInplace(vtkImageData* image);
        static vtkImageData* enhance(vtkImageData* image);

        static void flipInplace(vtkImageData* image, VolumeImageTransformations::FlipAxis axis);
        static vtkImageData* flip(vtkImageData* image, VolumeImageTransformations::FlipAxis axis);
    };
}    //namespace cadsi_lib::volumes
#endif    //CADSI_VOLUMEIMAGETRANSFORMATIONS_HPP
