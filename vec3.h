#ifndef VEC3_H

#define VEC3_H

#include <math.h>
#include <iostream>


class Vec3{
    public:
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }
        Vec3() : e{0,0,0} {};
        Vec3(double x, double y, double z) : e{x, y, z} {};
        
        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }
        
        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }
        bool near_zero() const {
            const auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }
         Vec3 operator-() const { return Vec3(-e[0],-e[1],-e[2]); }
        double length(){ return sqrt(length_squared()); }
        double length_squared(){return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
        double e[3];
       
};

//Utility Functions for Vec3
inline Vec3 operator-(const Vec3& L, const Vec3& R){
    return Vec3(L.e[0] - R.e[0], L.e[1] - R.e[1], L.e[2] - R.e[2]);
}


inline Vec3 operator+(const Vec3& L, const Vec3& R){
    return Vec3(L.e[0] + R.e[0], L.e[1] + R.e[1], L.e[2] + R.e[2]);
}

inline Vec3 operator*(const Vec3 &L, const Vec3 &R){
    return Vec3(L.e[0] * R.e[0], L.e[1] * R.e[1], L.e[2] * R.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v){
    return Vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

inline Vec3 operator*(const Vec3& v,const double& t){
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t){
    return (1/t) * v;
}

inline double dot(const Vec3& L, const Vec3 R){
    return (L.e[0] * R.e[0]) + (L.e[1] * R.e[1]) + (L.e[2] * R.e[2]);
}

inline Vec3 cross(const Vec3& L, const Vec3 &R){
    return Vec3(L.e[1] * R.e[2] - L.e[2] * R.e[1],
                L.e[2] * R.e[0] - L.e[0] * R.e[2],
                L.e[0] * R.e[1] - L.e[1] * R.e[0]);
}


inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v){
    out << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return out;
}
inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}



using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color
#endif