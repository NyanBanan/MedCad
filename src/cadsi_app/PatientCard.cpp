//
// Created by nyanbanan on 09.04.2024.
//

#include "PatientCard.hpp"

PatientCard::PatientCard(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);

    _ui.goNextButton->setEnabled(false);
    _ui.photoLabel->setPixmap(QPixmap(":/icons/photo.jpg").scaled(200, 200, Qt::KeepAspectRatio));
    _ui.previewLabel->setPixmap(QPixmap(":/icons/photo.jpg").scaled(300, 300, Qt::KeepAspectRatio));

    _ui.widgetSlices->setModel(&_slices_model);

    _dicom_data.reset(new DICOMData);

    _slices_model.setDicomData(_dicom_data);
    }

void PatientCard::onDicomLoaded(int patient_id, int series_id) {
    _slices_model.setPatientInd(patient_id);
    _slices_model.setSeriesInd(series_id);

    auto preview_image = _dicom_data->getSeries(patient_id, series_id).getPreview().scaled(300, 300);

    _ui.previewLabel->setPixmap(QPixmap::fromImage(preview_image));

    preprocessor = new Preprocessor;
    auto& images_list = _dicom_data->getSeries(patient_id, series_id).getImages();

    vtkNew<vtkStringArray> image_file_names;
    std::ranges::for_each(images_list, [&image_file_names](const auto& image_name) {
        image_file_names->InsertNextValue(image_name.getImageFilePath().toStdString());
    });

    cadsi_lib::dicom::providers::DicomImageDataProvider provider;

    auto parse_res = provider.parseDicomFiles(image_file_names);

    if (!parse_res.success) {
        showErrorMessage(QString("Ошибка обработки изображений. Код ошибки: %1").arg(parse_res.error_code));
    }

    preprocessor->loadImage(provider.getOutputPort());

    _ui.goNextButton->setEnabled(true);
}

void PatientCard::showErrorMessage(const QString& error_message) {
    _error_win.showMessage(error_message);
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
        _dicom_dialog->setDICOMSharedData(_dicom_data);

        connect(_dicom_dialog, &DICOMDatabaseDialog::dicomLoaded, this, &PatientCard::onDicomLoaded);
        connect(_dicom_dialog, &DICOMDatabaseDialog::error, this, &PatientCard::showErrorMessage);
    }
    _dicom_dialog->show();
}

void PatientCard::on_goNextButton_pressed() {
    preprocessor->show();
}
