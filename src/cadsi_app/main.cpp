#include <QApplication>
#include <QMainWindow>
#include <QQmlApplicationEngine>

#include "ErrorMessageBox.hpp"
#include "GlobalSettingsConfigurator.hpp"
#include "PatientCard.hpp"

int main(int argc, char* argv[]) {
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication app{argc, argv};
    QMainWindow window;

    ErrorMessageBox err_mes;
    auto colors_res = GlobalSettingsConfigurator::setColorDataFile("./settings/colors.yml");
    if (!colors_res.success) {
        err_mes.showMessage(QString::fromStdString(colors_res.error_message));
        return QApplication::exec();
    }
    auto color_maps_res = GlobalSettingsConfigurator::setColorMapsDataFile("./settings/colormaps.yml");
    if (!color_maps_res.success) {
        err_mes.showMessage(QString::fromStdString(color_maps_res.error_message));
        return QApplication::exec();
    }
    auto volumes_res = GlobalSettingsConfigurator::setVolumesDataFile("./settings/volume.yml");
    if (!volumes_res.success) {
        err_mes.showMessage(QString::fromStdString(volumes_res.error_message));
        return QApplication::exec();
    }

    PatientCard pc;
    window.setCentralWidget(&pc);
    window.show();

    return QApplication::exec();
}
