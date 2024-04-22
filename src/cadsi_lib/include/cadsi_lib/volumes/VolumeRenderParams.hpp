//
// Created by nyanbanan on 21.04.2024.
//

#ifndef CADSI_VOLUMERENDERPARAMS_HPP
#define CADSI_VOLUMERENDERPARAMS_HPP

#include <format>
#include <QList>

#include "cadsi_lib/Result.hpp"
#include "VolumeErrorCodes.hpp"

namespace cadsi_lib::volumes {
    struct VolumesRenderParams {
        enum Modality {
            CT,
            MRI
        };

        enum Tissue {
            BONE,
            MUSCLE,
            SKIN
        };

        struct VolumeColorParams {
            double x;
            double r;
            double g;
            double b;
            double midpoint;
            double sharpness;
            bool operator== (const VolumeColorParams& b) const = default;
        };

        struct GradientOpacity {
            double x;
            double y;
            bool operator== (const GradientOpacity& b) const = default;
        };

        struct ScalarOpacity {
            double x;
            double y;
            double midpoint;
            double sharpness;
            bool operator== (const ScalarOpacity& b) const = default;
        };

        bool operator== (const VolumesRenderParams& b) const = default;

        double _ambient{0.0};
        QList<VolumeColorParams> _volume_color;
        double _diffuse{0.0};
        QList<GradientOpacity> _gradient_opacity;
        Modality _modality{};
        QList<ScalarOpacity> _scalar_opacity;
        double _specular{0.0};
        Tissue _tissue{};

        static Result<VolumesRenderParams::Tissue> tissueFromString(const std::string& tissue);
        static Result<VolumesRenderParams::Modality> modalityFromString(const std::string& modality);
    };
}    //namespace cadsi_lib::volumes
#endif    //CADSI_VOLUMERENDERPARAMS_HPP
