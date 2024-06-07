//
// Created by nyanbanan on 26.04.2024.
//

#ifndef CADSI_DICOMSCANDIALOG_HPP
#define CADSI_DICOMSCANDIALOG_HPP

#include <QDialog>
#include <QFileDialog>

#include "../ui_files/ui_dicomscandialog.h"

class DICOMScanDialog : public QDialog {
    Q_OBJECT
public:
    DICOMScanDialog(QDialog* parent = nullptr);
signals:
    void scanDirSelected(bool deep_search, const QString& dir_path);
public slots:
    void on_fileDialogPushButton_pressed();
    void on_buttonBox_accepted();

private:
    Ui::DICOMScanDialog _ui;
};

#endif    //CADSI_DICOMSCANDIALOG_HPP
