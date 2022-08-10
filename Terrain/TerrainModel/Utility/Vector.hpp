//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#ifndef TERRAINMODEL_VECTOR_HPP
#define TERRAINMODEL_VECTOR_HPP

struct Vector3i{
    int X;
    int Y;
    int Z;
    Vector3i(int,int,int);
};

Vector3i operator+(const Vector3i &, const Vector3i &);
Vector3i operator-(const Vector3i &, const Vector3i &);
Vector3i operator*(int, const Vector3i &);

struct Vector3f{
    float X;
    float Y;
    float Z;
    Vector3f(float,float,float);
};

Vector3f operator+(const Vector3f &, const Vector3f &);
Vector3f operator-(const Vector3f &, const Vector3f &);
Vector3f operator*(float, const Vector3f &);

#endif //TERRAINMODEL_VECTOR_HPP
