//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMSLICEMETADATAOBJECT_HPP
#define CADSI_DICOMSLICEMETADATAOBJECT_HPP

#include <QString>
#include <sstream>

#include "cadsi_lib/dicom/cadsiDicomDataElement.hpp"

class DICOMSliceMetaDataObject {
public:
    void setTag(const QString& tag);
    QString getTag() const;
    void setName(const QString& name);
    QString getName() const;
    void setVal(const QString& val);
    QString getVal() const;
    void setVR(const QString& vr);
    QString getVR() const;

    static DICOMSliceMetaDataObject fromCadsiDicomDataElement(const cadsi_lib::dicom::cadsiDicomDataElement& data);
    static DICOMSliceMetaDataObject fromCadsiDicomDataElement(cadsi_lib::dicom::cadsiDicomDataElement&& data);

private:
    QString _tag;
    QString _name;
    QString _val;
    QString _vr;
};

#endif    //CADSI_DICOMSLICEMETADATAOBJECT_HPP
