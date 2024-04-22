//
// Created by nyanbanan on 24.02.2024.
//

#include <QTest>
#include <cadsi_lib/colors/providers/YamlColorsProvider.hpp>

class tst_YamlColorsProvider : public QObject {
    Q_OBJECT
private slots:
    void deserialize_data();
    void deserialize();
};

QTEST_MAIN(tst_YamlColorsProvider)
#include "tst_YamlColorsProvider.moc"

using VolumeMap = QMap<QString, vtkColor3d>;

void tst_YamlColorsProvider::deserialize_data() {
    QTest::addColumn<YAML::Node>("yaml");
    QTest::addColumn<VolumeMap>("result");
    QTest::addColumn<bool>("successes");

    auto simple_test_yaml = YAML::Load("red: [1.0, 0, 0]\ngreen: [0, 1.0, 0]\nblue: [0, 0, 1.0]");
    VolumeMap simple_test_data{{"red", {1, 0, 0}}, {"green", {0, 1, 0}}, {"blue", {0, 0, 1}}};

    QTest::newRow("simple_test") << simple_test_yaml << simple_test_data << true;

    auto russian_yaml = YAML::Load("красный: [1.0, 0, 0]\nзеленый: [0, 1.0, 0]\nголубой: [0, 0, 1.0]");
    VolumeMap russian_data{{"красный", {1, 0, 0}}, {"зеленый", {0, 1, 0}}, {"голубой", {0, 0, 1}}};

    QTest::newRow("russian") << russian_yaml << russian_data << true;

    auto complex_colors_yaml = YAML::Load("peacock: [0.2, 0.631, 0.788]\nroyalblue: [0.031, 0.298, 0.62]\nwheat: "
                                          "[0.961, 0.871, 0.702]");
    VolumeMap complex_colors_data{{"peacock", {0.2, 0.631, 0.788}},
                                 {"royalblue", {0.031, 0.298, 0.62}},
                                 {"wheat", {0.961, 0.871, 0.702}}};

    QTest::newRow("complex_colors") << complex_colors_yaml << complex_colors_data << true;

    auto wrong_colors_sequence_yaml = YAML::Load("peacock: [0.2, 0.631]\nroyalblue: [0.031, 0.298, 0.62, 0.7]\nwheat: "
                                          "[0.961, 0.871, 0.702]");

    QTest::newRow("wrong_colors_sequence") << wrong_colors_sequence_yaml << VolumeMap{} << false;

    auto wrong_yaml_format_yaml = YAML::Load("testerror:\n peacock: [0.2, 0.631]\nroyalblue: [0.031, 0.298, 0.62, 0.7]\nwheat: "
                                                 "[0.961, 0.871, 0.702]");

    QTest::newRow("wrong_yaml_format") << wrong_yaml_format_yaml << VolumeMap{} << false;

    auto wrong_yaml_format_yaml2 = YAML::Load("peacock: [0.2, 0.631]\ntesterror:\n royalblue: [0.031, 0.298, 0.62, 0.7]\nwheat: "
                                             "[0.961, 0.871, 0.702]");

    QTest::newRow("wrong_yaml_format2") << wrong_yaml_format_yaml2 << VolumeMap{} << false;

    auto wrong_yaml_str_instead_of_double_yaml = YAML::Load("red: [str, 0, 0]\ngreen: [0, 1.0, 0]\nblue: [0, 0, 1.0]");

    QTest::newRow("wrong_yaml_str_instead_of_double") << wrong_yaml_str_instead_of_double_yaml << VolumeMap{} << false;
}

void tst_YamlColorsProvider::deserialize() {
    QFETCH(YAML::Node, yaml);
    QFETCH(VolumeMap, result);
    QFETCH(bool, successes);

    cadsi_lib::colors::providers::YamlColorsProvider ycp;
    auto res = ycp.deserialize(yaml);

    QCOMPARE(res.success, successes);
    if (successes) {
        QCOMPARE(ycp.allColors(), result);
    }
}
