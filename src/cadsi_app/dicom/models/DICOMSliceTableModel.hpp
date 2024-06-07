//
// Created by nyanbanan on 28.04.2024.
//

#ifndef CADSI_DICOMSLICETABLEMODEL_HPP
#define CADSI_DICOMSLICETABLEMODEL_HPP

#include <QAbstractTableModel>
#include <vtkDICOMDictionary.h>

#include "../DICOMSliceMetaDataObject.hpp"
#include "DICOMModel.hpp"

class DICOMSliceTableModel : public DICOMModel {
    Q_OBJECT
public:
    enum SliceColumnRoles {
        FIRST_ROLE = Qt::UserRole,    //required for column counting, dont use them
        TAG_ROLE,
        ATTRIBUTE_ROLE,
        VAL_ROLE,
        VR_ROLE,
        LAST_ROLE    //required for column counting, dont use them
    };

    enum SliceDataRoles {
        CURR_FILE_NAME_ROLE = LAST_ROLE + 1,
        NUM_OF_SLICES_ROLE
    };

    DICOMSliceTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setPatientInd(int patient_ind);
    void setSeriesInd(int series_ind);
    void setSliceInd(int slice_ind);

signals:
    void currSeriesIndChanged(int new_ind);
    void currSliceIndChanged();

private:
    int _curr_patient_ind{-1};
    int _curr_series_ind{-1};
    int _curr_slice_ind{-1};
    QList<DICOMSliceMetaDataObject> _slice_data;

    void handleDicomDataChanged(const QList<cadsi_lib::dicom::DicomPatient>& old_data,
                                const QList<cadsi_lib::dicom::DicomPatient>& new_data) override;
};

#endif    //CADSI_DICOMSLICETABLEMODEL_HPP
