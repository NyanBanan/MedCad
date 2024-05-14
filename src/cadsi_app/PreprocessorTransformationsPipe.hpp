//
// Created by nyanbanan on 14.05.2024.
//

#ifndef CADSI_PREPROCESSORTRANSFORMATIONSPIPE_HPP
#define CADSI_PREPROCESSORTRANSFORMATIONSPIPE_HPP

#include <vtkImageAlgorithm.h>
#include <vtkImageAnisotropicDiffusion2D.h>
#include <vtkImageCast.h>
#include <vtkImageFlip.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageLaplacian.h>
#include <vtkImageMathematics.h>
#include <vtkNew.h>
//TODO: Try to rewrite it to the final data instead of pipes
class PreprocessorTransformationsPipe {
public:
    enum FlipAxis {
        X,
        Y,
        Z
    };

    PreprocessorTransformationsPipe();
    void setInputConnection(vtkAlgorithmOutput* input);
    vtkAlgorithmOutput* getOutputConnection();

    void smooth(double sigma, double r);
    void denoise(double factor, double threshold);
    void enhance();
    //TODO: Ask how it should work, the whole coordinate system is being flipped now, so it doesn't work the way it does in python
    void flip(FlipAxis axis);

private:
    vtkImageAlgorithm* _first_alg;
    vtkImageAlgorithm* _last_alg;

    vtkNew<vtkImageGaussianSmooth> _smooth;
    vtkNew<vtkImageAnisotropicDiffusion2D> _denoise;
    vtkNew<vtkImageCast> _cast;
    vtkNew<vtkImageLaplacian> _laplacian;
    vtkNew<vtkImageMathematics> _enhance;
    vtkNew<vtkImageFlip> _flip;
};

#endif    //CADSI_PREPROCESSORTRANSFORMATIONSPIPE_HPP
