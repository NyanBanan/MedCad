//
// Created by nyanbanan on 14.05.2024.
//

#include "PreprocessorTransformationsPipe.hpp"

PreprocessorTransformationsPipe::PreprocessorTransformationsPipe() {
    _first_alg = _smooth;

    _denoise->SetInputConnection(_smooth->GetOutputPort());
    _cast->SetInputConnection(_denoise->GetOutputPort());
    _laplacian->SetInputConnection(_cast->GetOutputPort());
    _enhance->SetInputConnection(0, _cast->GetOutputPort());
    _enhance->SetInputConnection(1, _laplacian->GetOutputPort());
    _flip->SetInputConnection(_enhance->GetOutputPort());

    _last_alg = _flip;
}

void PreprocessorTransformationsPipe::setInputConnection(vtkAlgorithmOutput* input) {
    _first_alg->SetInputConnection(input);
}

vtkAlgorithmOutput* PreprocessorTransformationsPipe::getOutputConnection() {
    return _last_alg->GetOutputPort();
}

void PreprocessorTransformationsPipe::smooth(double sigma, double r) {
    _smooth->SetDimensionality(3);
    _smooth->SetRadiusFactor(r);
    _smooth->SetStandardDeviation(sigma);
}

void PreprocessorTransformationsPipe::denoise(double factor, double threshold) {
    _denoise->SetDiffusionFactor(factor);
    _denoise->SetDiffusionThreshold(threshold);
}

void PreprocessorTransformationsPipe::enhance() {
    _cast->SetOutputScalarTypeToDouble();

    // Считаем лаплассиан
    _laplacian->SetDimensionality(3);

    // Вычитаем лаплассиан из изображения
    _enhance->SetOperationToSubtract();
}

void PreprocessorTransformationsPipe::flip(PreprocessorTransformationsPipe::FlipAxis axis) {
    _flip->SetFilteredAxis(static_cast<int>(axis));
}
