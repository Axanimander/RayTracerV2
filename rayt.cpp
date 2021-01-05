#include "rayt.h"


Vec3 random_in_unit_sphere(){
    while(true){
        auto p = randomv(-1,1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}
Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}
Vec3 refract(const Vec3 &uv, const Vec3 &n, double etai_over_etat){
    auto cos_theta = fmin(dot(-uv,n), 1.0);
    Vec3 r_perp = etai_over_etat * (uv + cos_theta*n);
    Vec3 r_par = -sqrt(fabs(1.0 - r_perp.length_squared())) * n;
    return r_perp + r_par;
}