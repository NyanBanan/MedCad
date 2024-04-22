//
// Created by nyanbanan on 14.04.2024.
//

#ifndef CADSI_DICOMIMAGEMETADATATABLEMODELOBJECT_HPP
#define CADSI_DICOMIMAGEMETADATATABLEMODELOBJECT_HPP

#include <sstream>
#include <QString>
#include <vtkDICOMDataElement.h>
#include <vtkDICOMDictionary.h>


    class DICOMImageMetaDataTableModelObject {
    public:
        void setTag(const QString& tag);
        QString getTag() const;
        void setName(const QString& name);
        QString getName() const;
        void setVal(const QString& val);
        QString getVal() const;
        void setVR(const QString& vr);
        QString getVR() const;

        static DICOMImageMetaDataTableModelObject fromDicomDataElement(const vtkDICOMDataElement& data);
        static DICOMImageMetaDataTableModelObject fromDicomDataElement(vtkDICOMDataElement&& data);

    private:
        QString _tag;
        QString _name;
        QString _val;
        QString _vr;
    };

#endif    //CADSI_DICOMIMAGEMETADATATABLEMODELOBJECT_HPP