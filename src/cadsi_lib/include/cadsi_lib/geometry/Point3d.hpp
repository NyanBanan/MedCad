//
// Created by nyanbanan on 09.04.2024.
//

#ifndef CADSI_POINT3D_HPP
#define CADSI_POINT3D_HPP

#include <vtkVector.h>
#include <vtkMath.h>

namespace cadsi_lib::geometry {
    class Point3d {
    public:
        explicit Point3d(double x = 0, double y = 0, double z = 0);
        explicit Point3d(const vtkVector3d& data);
        explicit Point3d(vtkVector3d&& data);

        [[nodiscard]] double getX() const;
        void setX(double x);
        [[nodiscard]] double getY() const;
        void setY(double y);
        [[nodiscard]] double getZ() const;
        void setZ(double z);
        [[nodiscard]] const double* getData() const;

        static double euclidianDistance(const Point3d &point1, const Point3d &point2);

        [[nodiscard]] double euclidianDistance(const Point3d &point) const;

    private:
        vtkVector3d _data;
    };
}
#endif    //CADSI_POINT3D_HPP
