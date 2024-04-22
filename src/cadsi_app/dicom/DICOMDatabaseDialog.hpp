//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_DICOMDATABASEDIALOG_HPP
#define CADSI_DICOMDATABASEDIALOG_HPP

#include <QDialog>

#include <cadsi_lib/dicom/providers/FileDataDicomProvider.hpp>
#include <cadsi_lib/dicom/SqliteDicomDataMapper.hpp>

#include "DICOMImageMetaDataTableModel.hpp"
#include "DICOMPatientMetaDataTableModel.hpp"
#include "DICOMPatientMetaDataTableDelegate.hpp"

#include "../ui_files/ui_dicomdatabasedialog.h"

    class DICOMDatabaseDialog : public QDialog {
        Q_OBJECT
    public:
        DICOMDatabaseDialog(QWidget* parent = nullptr);

    private:
        Ui::DICOMDatabaseDialog _ui;
    };

#endif    //CADSI_DICOMDATABASEDIALOG_HPP
