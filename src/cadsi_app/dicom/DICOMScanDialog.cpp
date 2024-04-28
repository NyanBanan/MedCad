//
// Created by nyanbanan on 26.04.2024.
//

#include "DICOMScanDialog.hpp"

DICOMScanDialog::DICOMScanDialog(QDialog* parent) : QDialog(parent) {
    _ui.setupUi(this);
}

void DICOMScanDialog::on_fileDialogPushButton_pressed() {
    auto dir = QFileDialog::getExistingDirectory(this, "Открыть", QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty()) {
        _ui.dirPathLineEdit->setText(dir);
    }
}

void DICOMScanDialog::on_buttonBox_accepted() {
    auto depth = 1;
    auto dir = _ui.dirPathLineEdit->text();
    auto deep_search = _ui.deepSearchCheckBox->isChecked();
    emit scanDirSelected(deep_search, dir);
}
