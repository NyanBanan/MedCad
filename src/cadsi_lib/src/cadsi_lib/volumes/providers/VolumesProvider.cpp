//
// Created by nyanbanan on 21.02.2024.
//

#include <format>

#include "cadsi_lib/volumes/providers/VolumesProvider.hpp"
#include "cadsi_lib/Result.hpp"

namespace cadsi_lib::volumes::providers {
    vtkSmartPointer<vtkVolumeProperty> VolumesProvider::volumeRenderPreset(VolumesRenderParams::Modality modality,
                                                                           VolumesRenderParams::Tissue tissue) {
        auto params = getVolumeRenderParams(modality, tissue);

        vtkNew<vtkColorTransferFunction> color_func;
        for (auto&& [x, r, g, b, midpoint, sharpness] : params._volume_color) {
            color_func->AddRGBPoint(x, r, g, b, midpoint, sharpness);
        }

        vtkNew<vtkPiecewiseFunction> scalar_opacity_func;
        for (auto&& [x, y, midpoint, sharpness] : params._scalar_opacity) {
            scalar_opacity_func->AddPoint(x, y, midpoint, sharpness);
        }

        vtkNew<vtkPiecewiseFunction> gradient_opacity_func;
        for (auto&& [x, y] : params._gradient_opacity) {
            gradient_opacity_func->AddPoint(x, y);
        }

        vtkNew<vtkVolumeProperty> volume_property;
        volume_property->SetColor(color_func);
        volume_property->SetScalarOpacity(scalar_opacity_func);
        volume_property->SetGradientOpacity(gradient_opacity_func);

        volume_property->SetInterpolationTypeToLinear();
        volume_property->ShadeOn();
        volume_property->SetAmbient(params._ambient);
        volume_property->SetDiffuse(params._diffuse);
        volume_property->SetSpecular(params._specular);

        return volume_property;
    }
}    //namespace cadsi_lib::providers
