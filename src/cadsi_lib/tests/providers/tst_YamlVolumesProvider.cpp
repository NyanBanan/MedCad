//
// Created by nyanbanan on 06.04.2024.
//

#include <QTest>
#include <cadsi_lib/volumes/providers/YamlVolumesProvider.hpp>

class tst_YamlVolumesProvider : public QObject {
    Q_OBJECT
private slots:
    void deserialize_data();
    void deserialize();
};

QTEST_MAIN(tst_YamlVolumesProvider)
#include "tst_YamlVolumesProvider.moc"

using VolumesRenderParams = cadsi_lib::volumes::VolumesRenderParams;
using Modality = VolumesRenderParams::Modality;
using Tissue = VolumesRenderParams::Tissue;
using VolumeMap = QMap<std::pair<Modality, Tissue>, VolumesRenderParams>;

void tst_YamlVolumesProvider::deserialize_data() {
    QTest::addColumn<YAML::Node>("yaml");
    QTest::addColumn<VolumeMap>("result");
    QTest::addColumn<bool>("successes");

    auto simple_test_yaml = YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                                       "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                                       "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                                       "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                                       "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                                       "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                                       "specular: 0.2\n    tissue: bone\n  muscle:\n    ambient: 0.4\n    color:\n    "
                                       "- [-2048, 0, 0, 0, 0.5, 0.0]\n    - [-155, 0.55, 0.25, 0.15, 0.5, 0.92]\n    - "
                                       "[217, 0.88, 0.6, 0.29, 0.33, 0.45]\n    - [420, 1, 0.94, 0.95, 0.5, 0.0]\n    "
                                       "- [2048, 0.83, 0.66, 1, 0.5, 0.0]\n    diffuse: 0.6\n    gradient_opacity:\n   "
                                       " - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: ct\n    "
                                       "scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-155, 0, 0.5, 0.92]\n    - "
                                       "[217, 0.68, 0.33, 0.45]\n    - [420, 0.83, 0.5, 0.0]\n    - [2048, 0.8, 0.5, "
                                       "0.0]\n    specular: 0.2\n    tissue: muscle\n  skin:\n    ambient: 0.4\n    "
                                       "color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n    - [-1000, 0.62, 0.36, 0.18, 0.5, "
                                       "0.0]\n    - [-500, 0.88, 0.6, 0.29, 0.33, 0.45]\n    - [2048, 0.83, 0.66, 1, "
                                       "0.5, 0.0]\n    diffuse: 0.6\n    gradient_opacity:\n    - [0, 0.0]\n    - [90, "
                                       "0.5]\n    - [100, 1.0]\n    modality: ct\n    scalar_opacity:\n    - [-2048, "
                                       "0, 0.5, 0.0]\n    - [-1000, 0, 0.5, 0.0]\n    - [-500, 1.0, 0.33, 0.45]\n    - "
                                       "[2048, 1.0, 0.5, 0.0]\n    specular: 0.2\n    tissue: skin");
    VolumeMap simple_test_data{

        {{Modality::CT, Tissue::BONE},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-16, 0.73, 0.25, 0.3, 0.49, 0.61},
                            {641, 0.9, 0.82, 0.56, 0.5, 0.0},
                            {2048, 1, 1, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0}, {-16, 0, 0.49, 0.61}, {641, 0.72, 0.5, 0.0}, {2048, 0.71, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::BONE}},
        {{Modality::CT, Tissue::MUSCLE},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-155, 0.55, 0.25, 0.15, 0.5, 0.92},
                            {217, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {420, 1, 0.94, 0.95, 0.5, 0.0},
                            {2048, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0},
                              {-155, 0, 0.5, 0.92},
                              {217, 0.68, 0.33, 0.45},
                              {420, 0.83, 0.5, 0.0},
                              {2048, 0.8, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::MUSCLE}},
        {{Modality::CT, Tissue::SKIN},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-1000, 0.62, 0.36, 0.18, 0.5, 0.0},
                            {-500, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {2048, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0}, {-1000, 0, 0.5, 0.0}, {-500, 1.0, 0.33, 0.45}, {2048, 1.0, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::SKIN}}};

    QTest::newRow("simple_test") << simple_test_yaml << simple_test_data << true;

    auto complex_test_yaml = YAML::Load(
        "ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n    - [-16, 0.73, 0.25, 0.3, "
        "0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, 0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
        "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: ct\n    scalar_opacity:\n "
        "   - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, 0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, "
        "0.0]\n    specular: 0.2\n    tissue: bone\n  muscle:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, "
        "0.5, 0.0]\n    - [-155, 0.55, 0.25, 0.15, 0.5, 0.92]\n    - [217, 0.88, 0.6, 0.29, 0.33, 0.45]\n    - [420, "
        "1, 0.94, 0.95, 0.5, 0.0]\n    - [2048, 0.83, 0.66, 1, 0.5, 0.0]\n    diffuse: 0.6\n    gradient_opacity:\n    "
        "- [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, "
        "0.0]\n    - [-155, 0, 0.5, 0.92]\n    - [217, 0.68, 0.33, 0.45]\n    - [420, 0.83, 0.5, 0.0]\n    - [2048, "
        "0.8, 0.5, 0.0]\n    specular: 0.2\n    tissue: muscle\n  skin:\n    ambient: 0.4\n    color:\n    - [-2048, "
        "0, 0, 0, 0.5, 0.0]\n    - [-1000, 0.62, 0.36, 0.18, 0.5, 0.0]\n    - [-500, 0.88, 0.6, 0.29, 0.33, 0.45]\n    "
        "- [2048, 0.83, 0.66, 1, 0.5, 0.0]\n    diffuse: 0.6\n    gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n "
        "   - [100, 1.0]\n    modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-1000, 0, 0.5, "
        "0.0]\n    - [-500, 1.0, 0.33, 0.45]\n    - [2048, 1.0, 0.5, 0.0]\n    specular: 0.2\n    tissue: skin\nmri:\n "
        " bone:\n    ambient: 0.4\n    color:\n    - [0, 0, 0, 0, 0.5, 0.0]\n    - [500, 0.73, 0.25, 0.3, 0.49, "
        "0.61]\n    - [1000, 0.9, 0.82, 0.56, 0.5, 0.0]\n    - [1150, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
        "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: mri\n    "
        "scalar_opacity:\n    - [0, 0, 0.5, 0.0]\n    - [500, 0, 0.49, 0.61]\n    - [1000, 0.72, 0.5, 0.0]\n    - "
        "[1150, 0.71, 0.5, 0.0]\n    specular: 0.2\n    tissue: bone\n  muscle:\n    ambient: 0.4\n    color:\n    - "
        "[0, 0, 0, 0, 0.5, 0.0]\n    - [250, 0.55, 0.25, 0.15, 0.5, 0.92]\n    - [500, 0.88, 0.6, 0.29, 0.33, 0.45]\n  "
        "  - [1000, 1, 0.94, 0.95, 0.5, 0.0]\n    - [1150, 0.83, 0.66, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
        "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: mri\n    "
        "scalar_opacity:\n    - [0, 0, 0.5, 0.0]\n    - [250, 0, 0.5, 0.92]\n    - [500, 0.68, 0.33, 0.45]\n    - "
        "[1000, 0.83, 0.5, 0.0]\n    - [1150, 0.8, 0.5, 0.0]\n    specular: 0.2\n    tissue: muscle\n  skin:\n    "
        "ambient: 0.4\n    color:\n    - [0, 0, 0, 0, 0.5, 0.0]\n    - [500, 0.62, 0.36, 0.18, 0.5, 0.0]\n    - [1000, "
        "0.88, 0.6, 0.29, 0.33, 0.45]\n    - [1150, 0.83, 0.66, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
        "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    modality: mri\n    "
        "scalar_opacity:\n    - [0, 0, 0.5, 0.0]\n    - [500, 0, 0.5, 0.0]\n    - [1000, 1.0, 0.33, 0.45]\n    - "
        "[1150, 1.0, 0.5, 0.0]\n    specular: 0.2\n    tissue: skin");

    VolumeMap complex_test_data{
        {{Modality::MRI, Tissue::BONE},
         {._ambient = 0.4,
          ._volume_color = {{0, 0, 0, 0, 0.5, 0.0},
                            {500, 0.73, 0.25, 0.3, 0.49, 0.61},
                            {1000, 0.9, 0.82, 0.56, 0.5, 0.0},
                            {1150, 1, 1, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::MRI,
          ._scalar_opacity = {{0, 0, 0.5, 0.0}, {500, 0, 0.49, 0.61}, {1000, 0.72, 0.5, 0.0}, {1150, 0.71, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::BONE}},
        {{Modality::MRI, Tissue::MUSCLE},
         {._ambient = 0.4,
          ._volume_color = {{0, 0, 0, 0, 0.5, 0.0},
                            {250, 0.55, 0.25, 0.15, 0.5, 0.92},
                            {500, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {1000, 1, 0.94, 0.95, 0.5, 0.0},
                            {1150, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::MRI,
          ._scalar_opacity = {{0, 0, 0.5, 0.0},
                              {250, 0, 0.5, 0.92},
                              {500, 0.68, 0.33, 0.45},
                              {1000, 0.83, 0.5, 0.0},
                              {1150, 0.8, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::MUSCLE}},
        {{Modality::MRI, Tissue::SKIN},
         {._ambient = 0.4,
          ._volume_color = {{0, 0, 0, 0, 0.5, 0.0},
                            {500, 0.62, 0.36, 0.18, 0.5, 0.0},
                            {1000, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {1150, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::MRI,
          ._scalar_opacity = {{0, 0, 0.5, 0.0}, {500, 0, 0.5, 0.0}, {1000, 1.0, 0.33, 0.45}, {1150, 1.0, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::SKIN}},
        {{Modality::CT, Tissue::BONE},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-16, 0.73, 0.25, 0.3, 0.49, 0.61},
                            {641, 0.9, 0.82, 0.56, 0.5, 0.0},
                            {2048, 1, 1, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0}, {-16, 0, 0.49, 0.61}, {641, 0.72, 0.5, 0.0}, {2048, 0.71, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::BONE}},
        {{Modality::CT, Tissue::MUSCLE},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-155, 0.55, 0.25, 0.15, 0.5, 0.92},
                            {217, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {420, 1, 0.94, 0.95, 0.5, 0.0},
                            {2048, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0},
                              {-155, 0, 0.5, 0.92},
                              {217, 0.68, 0.33, 0.45},
                              {420, 0.83, 0.5, 0.0},
                              {2048, 0.8, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::MUSCLE}},
        {{Modality::CT, Tissue::SKIN},
         {._ambient = 0.4,
          ._volume_color = {{-2048, 0, 0, 0, 0.5, 0.0},
                            {-1000, 0.62, 0.36, 0.18, 0.5, 0.0},
                            {-500, 0.88, 0.6, 0.29, 0.33, 0.45},
                            {2048, 0.83, 0.66, 1, 0.5, 0.0}},
          ._diffuse = 0.6,
          ._gradient_opacity = {{0, 0.0}, {90, 0.5}, {100, 1.0}},
          ._modality = Modality::CT,
          ._scalar_opacity = {{-2048, 0, 0.5, 0.0}, {-1000, 0, 0.5, 0.0}, {-500, 1.0, 0.33, 0.45}, {2048, 1.0, 0.5, 0.0}},
          ._specular = 0.2,
          ._tissue = Tissue::SKIN}}};

    QTest::newRow("complex_test") << complex_test_yaml << complex_test_data << true;

    auto wrong_color_sequence_size_yaml =
        /*in this string*/ YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048]\n "
                                      "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                                      "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                                      "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                                      "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                                      "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                                      "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_color_sequence_size") << wrong_color_sequence_size_yaml << VolumeMap{} << false;

    auto wrong_gradient_sequence_size_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                   /*in this string*/ "gradient_opacity:\n    - [0, 0.0, 1.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_gradient_sequence_size") << wrong_gradient_sequence_size_yaml << VolumeMap{} << false;

    auto wrong_scalar_sequence_size_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                   "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   /*in this string*/ "modality: ct\n    scalar_opacity:\n    - [-2048]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_scalar_sequence_size") << wrong_scalar_sequence_size_yaml << VolumeMap{} << false;

    auto wrong_color_sequence_str_instead_of_double_yaml =
        YAML::Load(/*in this string*/ "ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, str, 0, 0, 0.5, "
                                      "0.0]\n "
                                      "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                                      "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                                      "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                                      "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                                      "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                                      "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_color_sequence_str_instead_of_double")
        << wrong_color_sequence_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_gradient_sequence_str_instead_of_double_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                   /*in this string*/ "gradient_opacity:\n    - [0, str]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_gradient_sequence_str_instead_of_double")
        << wrong_gradient_sequence_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_scalar_sequence_str_instead_of_double_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                   "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   /*in this string*/ "modality: ct\n    scalar_opacity:\n    - [-2048, 0, str, 0.0]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_scalar_sequence_str_instead_of_double")
        << wrong_scalar_sequence_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_ambient_str_instead_of_double_yaml =
        YAML::Load(/*In this string*/ "ct:\n  bone:\n    ambient: str\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                                      "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                                      "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                                      "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                                      /*in this string*/ "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, "
                                      "0.0]\n    - "
                                      "[-16, 0, "
                                      "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                                      "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_ambient_str_instead_of_double")
        << wrong_ambient_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_diffuse_str_instead_of_double_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   /*in this string*/ "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: str\n    "
                   "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   "specular: 0.2\n    tissue: bone\n");

    QTest::newRow("wrong_diffuse_str_instead_of_double")
        << wrong_diffuse_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_specular_str_instead_of_double_yaml =
        YAML::Load("ct:\n  bone:\n    ambient: 0.4\n    color:\n    - [-2048, 0, 0, 0, 0.5, 0.0]\n "
                   "   - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, 0.9, 0.82, 0.56, 0.5, "
                   "0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: 0.6\n    "
                   "gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, 1.0]\n    "
                   "modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    - [-16, 0, "
                   "0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, 0.0]\n    "
                   /*in this string*/ "specular: str\n    tissue: bone\n");

    QTest::newRow("wrong_specular_str_instead_of_double")
        << wrong_specular_str_instead_of_double_yaml << VolumeMap{} << false;

    auto wrong_format_yaml =
        YAML::Load(/*in this string*/ "ct:\n  bone:\n    testerror:\n      ambient: 0.4\n    color:\n    - [-2048, "
                                      "0, 0, 0, 0.5, 0.0]\n    - [-16, 0.73, 0.25, 0.3, 0.49, 0.61]\n    - [641, "
                                      "0.9, 0.82, 0.56, 0.5, 0.0]\n    - [2048, 1, 1, 1, 0.5, 0.0]\n    diffuse: "
                                      "0.6\n    gradient_opacity:\n    - [0, 0.0]\n    - [90, 0.5]\n    - [100, "
                                      "1.0]\n    modality: ct\n    scalar_opacity:\n    - [-2048, 0, 0.5, 0.0]\n    "
                                      "- [-16, 0, 0.49, 0.61]\n    - [641, 0.72, 0.5, 0.0]\n    - [2048, 0.71, 0.5, "
                                      "0.0]\n    specular: 0.2\n    tissue: bone");

    QTest::newRow("wrong_format") << wrong_format_yaml << VolumeMap{} << false;

    auto wrong_format2_yaml = YAML::Load(/*in this string*/ "ct:\n  testerror:\n    bone:\n      ambient: 0.4\n      "
                                                            "color:\n      - [-2048, 0, 0, 0, 0.5, 0.0]\n      - [-16, "
                                                            "0.73, 0.25, 0.3, 0.49, 0.61]\n      - [641, 0.9, 0.82, "
                                                            "0.56, 0.5, 0.0]\n      - [2048, 1, 1, 1, 0.5, 0.0]\n      "
                                                            "diffuse: 0.6\n      gradient_opacity:\n      - [0, 0.0]\n "
                                                            "     - [90, 0.5]\n      - [100, 1.0]\n      modality: "
                                                            "ct\n      scalar_opacity:\n      - [-2048, 0, 0.5, 0.0]\n "
                                                            "     - [-16, 0, 0.49, 0.61]\n      - [641, 0.72, 0.5, "
                                                            "0.0]\n      - [2048, 0.71, 0.5, 0.0]\n      specular: "
                                                            "0.2\n      tissue: bone");

    QTest::newRow("wrong_format2") << wrong_format2_yaml << VolumeMap{} << false;
}

void tst_YamlVolumesProvider::deserialize() {
    QFETCH(YAML::Node, yaml);
    QFETCH(VolumeMap, result);
    QFETCH(bool, successes);

    cadsi_lib::volumes::providers::YamlVolumesProvider ycp;
    auto res = ycp.deserialize(yaml);

    QCOMPARE(res.success, successes);
    if (successes) {
        QCOMPARE(ycp.getAllVolumesRenderParams(), result);
    }
}

//TODO: Add volumeRenderPreset tests in future
