//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_TERRAINAGENT_HPP
#define TERRAIN_TERRAINAGENT_HPP

#include "Water.hpp"
#include "TerrainFormation.hpp"

enum class CellType{
    AG,
    UG
};

class UnderGroundCell{
public:
    UnderGroundCell(Water W, NutrientPack NP);
    void Tick(const TerrainFormation & terrainFormation, unsigned int simulationStep);
    unsigned int ID;
private:
    Water W;
    NutrientPack NP;
};

class AboveGroundCell{
    AboveGroundCell(Water W);
    void Tick(const TerrainFormation & terrainFormation, unsigned int simulationStep);
    unsigned int ID;
private:
    Water W;
};

#endif //TERRAIN_TERRAINAGENT_HPP
