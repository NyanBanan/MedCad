//
// Created by nyanbanan on 27.02.2024.
//
#include <QTest>
#include <cadsi_lib/color_maps/providers/YamlColorMapsProvider.hpp>

class tst_YamlColorMapsProvider : public QObject {
    Q_OBJECT
private slots:
    void deserialize_data();
    void deserialize();
};

QTEST_MAIN(tst_YamlColorMapsProvider)
#include "tst_YamlColorMapsProvider.moc"

using ColorMaps = QMap<QString, QList<vtkColor3d>>;

void tst_YamlColorMapsProvider::deserialize_data() {
    QTest::addColumn<YAML::Node>("yaml");
    QTest::addColumn<ColorMaps>("result");
    QTest::addColumn<bool>("successes");

    auto simple_test_yaml = YAML::Load("grayscale:\n colors: \n - [0.0, 0.0, 0.0]\n - [1.0, 1.0, 1.0]\n name: "
                                       "Grayscale");
    ColorMaps simple_test_data{{"Grayscale", {{0, 0, 0}, {1, 1, 1}}}};

    QTest::newRow("simple_test") << simple_test_yaml << simple_test_data << true;

    auto many_elements_test_yaml = YAML::Load("grayscale:\n  colors:\n  - [0.0, 0.0, 0.0]\n  - [1.0, 1.0, 1.0]\n  "
                                              "name: Grayscale\nblues:\n  colors:\n  - [0.231, 0.408, 0.671]\n  - "
                                              "[0.11, 0.584, 0.804]\n  - [0.306, 0.851, 0.918]\n  - [0.451, 0.604, "
                                              "0.835]\n  - [0.259, 0.239, 0.663]\n  - [0.314, 0.329, 0.529]\n  - "
                                              "[0.063, 0.165, 0.322]\n  name: Blues");
    ColorMaps many_elements_test_data{{"Grayscale", {{0, 0, 0}, {1, 1, 1}}},
                                      {"Blues",
                                       {{0.231, 0.408, 0.671},
                                        {0.11, 0.584, 0.804},
                                        {0.306, 0.851, 0.918},
                                        {0.451, 0.604, 0.835},
                                        {0.259, 0.239, 0.663},
                                        {0.314, 0.329, 0.529},
                                        {0.063, 0.165, 0.322}}}};

    QTest::newRow("many_elements_test") << many_elements_test_yaml << many_elements_test_data << true;

    auto russian_yaml = YAML::Load("серый:\n colors: \n - [0.0, 0.0, 0.0]\n - [1.0, 1.0, 1.0]\n name: Серый");
    ColorMaps russian_data{{"Серый", {{0, 0, 0}, {1, 1, 1}}}};

    QTest::newRow("russian") << russian_yaml << russian_data << true;

    auto wrong_sequence_yaml = YAML::Load("серый:\n colors: \n - [0.0, 0.0]\n - [1.0, 1.0, 1.0]\n name: Серый");

    QTest::newRow("wrong_sequence") << wrong_sequence_yaml << ColorMaps{} << false;

    auto wrong_yaml_keys_yaml = YAML::Load("серый:\n cols: \n - [0.0, 0.0, 0.0]\n - [1.0, 1.0, 1.0]\n na: Серый");

    QTest::newRow("wrong_yaml_keys") << wrong_yaml_keys_yaml << ColorMaps{} << false;

    auto wrong_yaml_format_yaml = YAML::Load("grayscale:\n  testerror:\n    colors:\n    - [0.0, 0.0, 0.0]\n    - [1.0, 1.0, 1.0]\n    name: Grayscale");

    QTest::newRow("wrong_yaml_format") << wrong_yaml_format_yaml << ColorMaps{} << false;

    auto wrong_yaml_str_instead_of_double_yaml = YAML::Load("grayscale:\n colors: \n - [str, 0.0, 0.0]\n - [1.0, 1.0, 1.0]\n name: "
                                                            "Grayscale");

    QTest::newRow("wrong_yaml_str_instead_of_double") << wrong_yaml_str_instead_of_double_yaml << ColorMaps{} << false;
}

void tst_YamlColorMapsProvider::deserialize() {
    QFETCH(YAML::Node, yaml);
    QFETCH(ColorMaps, result);
    QFETCH(bool, successes);

    cadsi_lib::color_maps::providers::YamlColorMapsProvider ycmp;
    auto res = ycmp.deserialize(yaml);

    QCOMPARE(res.success, successes);
    if (successes) {
        QCOMPARE(ycmp.allColorMaps(), result);
    }
}
//TODO: Add getLUT tests in future

