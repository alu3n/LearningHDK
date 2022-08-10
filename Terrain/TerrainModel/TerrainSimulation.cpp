//
// Created by Vojtěch Pröschl on 06.08.2022.
//

#include "TerrainSimulation.hpp"

void TerrainSimulation::Tick(size_t timeStep) {
    T.Dispatch(timeStep);
    T.Clearance(timeStep);
}

void TerrainSimulation::Reset() {
    T = TerrainFormation(1);
}

TerrainSimulation::TerrainSimulation() {
    Reset();
}