//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_TERRAINSIMULATION_HPP
#define TERRAIN_TERRAINSIMULATION_HPP

#include "TerrainFormation.hpp"
#include "Settings.hpp"


class TerrainSimulation{
private:
    using S = TerrainSettings;
public:
    TerrainFormation T;
    void Tick(size_t);
    void Reset();
    TerrainSimulation();
};


#endif //TERRAIN_TERRAINSIMULATION_HPP
