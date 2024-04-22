//
// Created by nyanbanan on 08.04.2024.
//

#ifndef CADSI_PLANE_HPP
#define CADSI_PLANE_HPP

#include <vtkPlane.h>
#include <vtkSmartPointer.h>

#include "Vector3d.hpp"

namespace cadsi_lib::geometry {
    class Plane : public vtkPlane{
    public:
        void SetOrigin(const Point3d& origin);
        void SetOrigin(const double origin[3]) override;
        void SetOrigin(double x, double y, double z) override;
        double* GetOrigin() override;
        void GetOrigin(double out[3]) override;

        void SetNormal(const Point3d& normal);
        void SetNormal(const double normal[3]) override;
        void SetNormal(double x, double y, double z) override;
        double* GetNormal() override;
        void GetNormal(double out[3]) override;

        static Plane* New();
        static vtkSmartPointer<vtkPlane> getXYPlane(const Point3d& normal = Point3d{0, 0, 0});
        static vtkSmartPointer<vtkPlane> getXZPlane(const Point3d& normal = Point3d{0, 0, 0});
        static vtkSmartPointer<vtkPlane> getYZPlane(const Point3d& normal = Point3d{0, 0, 0});
    };
}    //namespace Geometry

#endif    //CADSI_PLANE_HPP
