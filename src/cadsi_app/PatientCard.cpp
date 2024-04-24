//
// Created by nyanbanan on 09.04.2024.
//

#include "PatientCard.hpp"

PatientCard::PatientCard(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    _ui.goNextButton->setEnabled(false);
    _ui.photoLabel->setPixmap(QPixmap(":/icons/photo.jpg").scaled(200, 200, Qt::KeepAspectRatio));
    _ui.previewLabel->setPixmap(QPixmap(":/icons/photo.jpg").scaled(300, 300, Qt::KeepAspectRatio));
}

void PatientCard::on_changePhotoButton_pressed() {
    auto photo_file_name = QFileDialog::getOpenFileName(this,
                                                        "Выбор фотографии пациента",
                                                        "",
                                                        "JPEG (*.JPEG *.jpeg *.JPG *.jpg *.JPE *.jpe *JFIF *.jfif);; "
                                                        "PNG (*.PNG *.png)");
    if (!photo_file_name.isEmpty()) {
        QPixmap photo(photo_file_name);
        _ui.photoLabel->setPixmap(photo.scaled(200, 200, Qt::KeepAspectRatio));
    }
}

void PatientCard::on_birthdateDateTimeEdit_dateChanged(QDate born) {
    auto today = QDate::currentDate();
    auto age = today.year() - born.year() - ((today.month(), today.day()) < (born.month(), born.day()));
    _ui.ageLineEdit->setText(QString::number(age));
}

void PatientCard::on_dicomPushButton_pressed() {
    if (_dicom_dialog == nullptr) {
        _dicom_dialog = new DICOMDatabaseDialog(this);
    }
    _dicom_dialog->show();
}
