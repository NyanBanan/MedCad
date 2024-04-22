//
// Created by nyanbanan on 09.04.2024.
//

#include "cadsi_lib/geometry/Point3d.hpp"

namespace cadsi_lib::geometry {

    Point3d::Point3d(double x, double y, double z) : _data(x, y, z) {}

    Point3d::Point3d(const vtkVector3d& data) : _data(data) {}

    Point3d::Point3d(vtkVector3d&& data) : _data(data) {}

    double Point3d::getX() const {
        return _data.GetX();
    }

    void Point3d::setX(double x) {
        _data.SetX(x);
    }

    double Point3d::getY() const {
        return _data.GetY();
    }

    void Point3d::setY(double y) {
        _data.SetX(y);
    }

    double Point3d::getZ() const {
        return _data.GetZ();
    }

    void Point3d::setZ(double z) {
        _data.SetX(z);
    }

    const double* Point3d::getData() const {
        return _data.GetData();
    }

    double Point3d::euclidianDistance(const Point3d& point) const {
        return vtkMath::Distance2BetweenPoints(_data.GetData(), point.getData());
    }

    double Point3d::euclidianDistance(const Point3d& point1, const Point3d& point2) {
        return point1.euclidianDistance(point2);
    }
}    //namespace cadsi_lib::geometry
