//
// Created by nyanbanan on 09.04.2024.
//

#include "cadsi_lib/geometry/Vector3d.hpp"

namespace cadsi_lib::geometry {
    Vector3d::Vector3d(double x, double y, double z) : _point(x, y, z) {}

    Vector3d::Vector3d(const Point3d& point): _point(point) {}

    Vector3d::Vector3d(Point3d&& point): _point(point) {}

    void Vector3d::setPoint(const Point3d& point) {
        _point = point;
    }

    void Vector3d::setPoint(Point3d&& point) {
        _point = point;
    }

    const Point3d& Vector3d::getPoint() const {
        return _point;
    }

    Vector3d Vector3d::operator+ (const Vector3d& rgh) const {
        double add_res[3];
        vtkMath::Add(getPoint().getData(), rgh.getPoint().getData(), add_res);
        return Vector3d{add_res[0], add_res[1], add_res[2]};
    }

    Vector3d Vector3d::operator- (const Vector3d& rgh) const {
        double sub_res[3];
        vtkMath::Subtract(getPoint().getData(), rgh.getPoint().getData(), sub_res);
        return Vector3d{sub_res[0], sub_res[1], sub_res[2]};
    }

    Vector3d Vector3d::crossMult(const Vector3d& rgh) const {
        double cross_res[3];
        vtkMath::Cross(getPoint().getData(), rgh.getPoint().getData(), cross_res);
        return Vector3d{cross_res[0], cross_res[1], cross_res[2]};
    }

    double Vector3d::scalarMult(const Vector3d& rgh) const {
        return vtkMath::Dot(getPoint().getData(), rgh.getPoint().getData());
    }

    double Vector3d::getNorm() const {
        return vtkMath::Norm(getPoint().getData());
    }

    Vector3d Vector3d::getNormalized() const {
        double res_data[3];
        auto data_for_normalize = getPoint().getData();
        res_data[0] = data_for_normalize[0];
        res_data[1] = data_for_normalize[1];
        res_data[2] = data_for_normalize[2];
        vtkMath::Normalize(res_data);
        return Vector3d{res_data[0], res_data[1], res_data[2]};
    }

}    //namespace cadsi_lib::geometry
