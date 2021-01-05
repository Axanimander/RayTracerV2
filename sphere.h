#ifndef SPHERE_H

#define SPHERE_H

#include "hittable.h"
#include "rayt.h"

class sphere : public hittable{
    public:
        sphere() {}
        sphere(Point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r),  mat_ptr(m) {};

        virtual bool hit( const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        Point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};


#endif