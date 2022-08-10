//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_TERRAINAGENT_HPP
#define TERRAIN_TERRAINAGENT_HPP

#include "Water.hpp"

enum class CellType{
    AG,
    UG
};

struct UnderGroundCell{
public:
    UnderGroundCell(Water water, NutrientPack nutrientPack, size_t iD);
    unsigned int ID;
    Water W;
    NutrientPack NP;
};

struct AboveGroundCell{
    AboveGroundCell(Water water, size_t iD);
    unsigned int ID;
    Water W;
};

#endif //TERRAIN_TERRAINAGENT_HPP
