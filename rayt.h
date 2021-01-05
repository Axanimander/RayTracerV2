#ifndef RAYT_H

#define RAYT_H


#include <cmath>
#include <limits>
#include <memory>
#include <random>
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


inline double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
}

inline double random_double(){
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max){
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
#include "ray.h"
#include "vec3.h"
inline static Vec3 randomv(){
    return Vec3(random_double(),random_double(),random_double());
}
inline static Vec3 randomv(double min, double max){
    return Vec3(random_double(min, max),random_double(min, max),random_double(min, max));
}
Vec3 random_in_unit_sphere();
Vec3 random_unit_vector();
Vec3 random_in_unit_disk();
Vec3 refract(const Vec3 &uv, const Vec3 &n, double etai_over_etat);
#endif