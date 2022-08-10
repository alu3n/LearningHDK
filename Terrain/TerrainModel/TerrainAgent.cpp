//
// Created by Vojtěch Pröschl on 06.08.2022.
//

#include "TerrainAgent.hpp"

UnderGroundCell::UnderGroundCell(Water water, NutrientPack nutrientPack, size_t iD) : NP(nutrientPack), W(water) {
    ID = iD;
}

AboveGroundCell::AboveGroundCell(Water water, size_t iD) : W(water) {
    ID = iD;
}