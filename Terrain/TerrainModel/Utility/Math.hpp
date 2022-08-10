//
// Created by Vojtěch Pröschl on 09.08.2022.
//

#ifndef TERRAINMODEL_MATH_HPP
#define TERRAINMODEL_MATH_HPP

template<typename T>
T min(const T & t1, const T & t2){
    return t1 < t2 ? t1 : t2;
}

template<typename T>
T max(const T & t1, const T & t2){
    return t1 > t2 ? t1 : t2;
}

#endif //TERRAINMODEL_MATH_HPP
