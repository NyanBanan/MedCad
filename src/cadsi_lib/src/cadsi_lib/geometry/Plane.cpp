//
// Created by nyanbanan on 08.04.2024.
//

#include "cadsi_lib/geometry/Plane.hpp"

namespace cadsi_lib::geometry {
    Plane* Plane::New() {
        return new Plane;
    }

    void Plane::SetOrigin(const Point3d& origin) {
        vtkPlane::SetOrigin(origin.getData());
    }

    void Plane::SetOrigin(const double* origin) {
        vtkPlane::SetOrigin(origin);
    }

    void Plane::SetOrigin(double x, double y, double z) {
        vtkPlane::SetOrigin(x, y, z);
    }

    double* Plane::GetOrigin() {
        return vtkPlane::GetOrigin();
    }

    void Plane::GetOrigin(double* out) {
        vtkPlane::GetOrigin(out);
    }

    void Plane::SetNormal(const double* normal) {
        vtkPlane::SetNormal(normal);
    }


    void Plane::SetNormal(double x, double y, double z) {
        vtkPlane::SetNormal(x, y, z);
    }

    void Plane::SetNormal(const Point3d& normal) {
        vtkPlane::SetNormal(normal.getX(), normal.getY(), normal.getZ());
    }

    double* Plane::GetNormal() {
        return vtkPlane::GetNormal();
    }

    void Plane::GetNormal(double* out) {
        vtkPlane::GetNormal(out);
    }

    vtkSmartPointer<vtkPlane> Plane::getXYPlane(const Point3d& normal) {
        vtkNew<vtkPlane> plane;

        plane->SetOrigin(0, 0, 1);
        plane->SetNormal(normal.getX(), normal.getY(), normal.getZ());
        return plane;
    }

    vtkSmartPointer<vtkPlane> Plane::getXZPlane(const Point3d& normal) {
        vtkNew<vtkPlane> plane;

        plane->SetOrigin(1, 0, 0);
        plane->SetNormal(normal.getX(), normal.getY(), normal.getZ());
        return plane;
    }

    vtkSmartPointer<vtkPlane> Plane::getYZPlane(const Point3d& normal) {
        vtkNew<vtkPlane> plane;

        plane->SetOrigin(0, 1, 0);
        plane->SetNormal(normal.getX(), normal.getY(), normal.getZ());
        return plane;
    }
}    //namespace Geometry
