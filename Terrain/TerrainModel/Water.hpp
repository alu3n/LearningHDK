//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_WATER_HPP
#define TERRAIN_WATER_HPP

#include "Nutrients.hpp"

struct Water{
    float Volume;
    NutrientPack NP;
    Water(float,NutrientPack);
    std::vector<NutrientType> WaterType();

};

//Again equality for type
bool operator==(Water, Water);

Water operator+(Water,Water);
Water operator-(Water,Water);
Water operator*(float,Water);
std::ostream & operator<<(std::ostream &, Water);

#endif //TERRAIN_WATER_HPP
