//
// Created by nyanbanan on 09.04.2024.
//

#include "SliceMetadata.hpp"

SliceMetadata::SliceMetadata(QWidget* parent) : QWidget(parent) {
    _ui.setupUi(this);
}

void SliceMetadata::setData(const cadsi_lib::dicom::DicomSeries& series,
                            const QList<cadsi_lib::dicom::DicomImage>& slices) {
    auto shared_meta = series.getMetaCollection();
    std::ranges::for_each(shared_meta, [this](const auto& elem) {
        _shared_meta.push_back(DICOMImageMetaDataTableModelObject::fromDicomDataElement(elem));
    });

    for (const auto& slice : slices) {
        _slices_paths.push_back(slice.getImageFilePath());

        auto slice_meta = slice.getMetaCollection();
        auto& slices_meta_objects = _slices_meta.emplaceBack();

        std::ranges::for_each(slice_meta, [&slices_meta_objects](const auto& elem) {
            slices_meta_objects.push_back(DICOMImageMetaDataTableModelObject::fromDicomDataElement(elem));
        });
    }
}

void SliceMetadata::setCurrSlice(int id) {
    if (id < 0 || id > _slices_meta.size()) {
        return;
    }
    _ui.filePathLabel->setText(_slices_paths.value(id));

}
