//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_VECTOR3D_HPP
#define CADSI_VECTOR3D_HPP

#include "Point3d.hpp"

namespace cadsi_lib::geometry {
    /*!
         \brief Class describing a three-dimensional vector with coordinates (0,0,0) and point(x,y,z) based on vtk::Math functions
            */
    class Vector3d {
    public:
        explicit Vector3d(double x = 0, double y = 0, double z = 0);
        explicit Vector3d(const Point3d& point);
        explicit Vector3d(Point3d&& point);

        [[nodiscard]] const Point3d& getPoint() const;
        void setPoint(const Point3d& point);
        void setPoint(Point3d&& point);

        Vector3d operator+ (const Vector3d& rgh) const;
        Vector3d operator- (const Vector3d& rgh) const;
        [[nodiscard]] Vector3d crossMult(const Vector3d& rgh) const;
        [[nodiscard]] double scalarMult(const Vector3d& rgh) const;
        [[nodiscard]] double getNorm() const;
        [[nodiscard]] Vector3d getNormalized() const;

    private:
        Point3d _point;
    };

}    //namespace cadsi_lib::geometry

#endif    //CADSI_VECTOR3D_HPP
