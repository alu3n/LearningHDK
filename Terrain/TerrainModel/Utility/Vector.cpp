//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#include "Vector.hpp"

Vector3i::Vector3i(int x, int y, int z) {
    X = x;
    Y = y;
    Z = z;
}

Vector3i operator+(const Vector3i & A, const Vector3i & B){
    return {A.X+B.X,A.Y+B.Y,A.Z+B.Z};
}

Vector3i operator-(const Vector3i & A, const Vector3i & B){
    return {A.X-B.X,A.Y-B.Y,A.Z-B.Z};
}

Vector3i operator*(int a, const Vector3i & A){
    return {a*A.X,a*A.Y,a*A.Z};
}

Vector3f::Vector3f(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

Vector3f operator+(const Vector3f & A, const Vector3f & B){
    return {A.X+B.X,A.Y+B.Y,A.Z+B.Z};
}

Vector3f operator-(const Vector3f & A, const Vector3f & B){
    return {A.X-B.X,A.Y-B.Y,A.Z-B.Z};
}

Vector3f operator*(float a, const Vector3f & A){
    return {a*A.X,a*A.Y,a*A.Z};
}
