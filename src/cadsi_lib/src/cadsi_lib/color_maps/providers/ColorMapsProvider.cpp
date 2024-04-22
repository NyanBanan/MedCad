//
// Created by nyanbanan on 24.02.2024.
//

#include "cadsi_lib/color_maps/providers/ColorMapsProvider.hpp"

namespace cadsi_lib::color_maps::providers {
    vtkSmartPointer<vtkLookupTable> ColorMapsProvider::getLUT(QString color_map_name,
                                                              uint num_colors,
                                                              int min_value,
                                                              int max_value) {
        return getLUT(colorMap(color_map_name));
    }

    vtkSmartPointer<vtkLookupTable> ColorMapsProvider::getLUT(QList<vtkColor3d> color_map,
                                                              uint num_colors,
                                                              int min_value,
                                                              int max_value) {
        vtkNew<vtkColorTransferFunction> ctf;
        ctf->SetColorSpaceToDiverging();

        //We add colors from the color map
        double delta = (max_value - min_value) / double(color_map.size() - 1);
        double scalar_val = min_value;
        for (auto&& ind : std::ranges::views::iota(0, color_map.size() - 1)) {
            auto color = color_map[ind];
            ctf->AddRGBPoint(scalar_val, color.GetRed(), color.GetGreen(), color.GetBlue());
            scalar_val += delta;
        }
        auto last_color = color_map[color_map.size()];
        ctf->AddRGBPoint(max_value, last_color.GetRed(), last_color.GetGreen(), last_color.GetBlue());

        //Get interpolated colors
        QList<vtkColor3d> inter_colors;
        auto steps_num = num_colors - 1;
        double val = min_value;
        double val_step = (max_value - min_value) / double(steps_num);
        for (auto&& ind : std::ranges::views::iota(uint(0), steps_num)) {
            auto inter_color = ctf->GetColor(val);
            inter_colors.emplace_back(inter_color[0], inter_color[1], inter_color[2]);
            val += val_step;
        }
        auto inter_color = ctf->GetColor(val);
        inter_colors.emplace_back(inter_color[0], inter_color[1], inter_color[2]);

        //Construct LUT
        vtkNew<vtkLookupTable> lut;
        lut->SetNumberOfTableValues(num_colors);
        lut->SetTableRange(min_value, max_value);
        lut->Build();

        auto ind = 0;
        for (auto&& color : inter_colors) {
            lut->SetTableValue(ind, color.GetRed(), color.GetGreen(), color.GetBlue());
            ++ind;
        }
        return lut;
    }
}    //namespace cadsi_lib::global_providers
