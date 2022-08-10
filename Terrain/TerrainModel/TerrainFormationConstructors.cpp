//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#include "TerrainFormation.hpp"

using namespace std;



TerrainFormation::TerrainFormation(bool) {
    std::vector<std::tuple<UnderGroundCell,Vector3i>> dataUG;
    std::vector<std::tuple<AboveGroundCell,Vector3i>> dataAG;

    NutrientPack nutrientPack{};
    Water water{};
//    water.Volume = 0.00123;

    size_t id;

    for(int x = 0; x < TS::RX; ++x){
        for(int y = 0; y < TS::RY; ++y){
            for(int z = 0; z < TS::RZ; ++z){
                UnderGroundCell cell{water,nutrientPack,id};
                Vector3i vec{x,y,z};
                dataUG.emplace_back(tuple<UnderGroundCell,Vector3i>(cell,vec));
                id++;
            }
        }
    }

    Storage = TerrainLookup<TS::RX,TS::RY,TS::RZ>(dataAG, dataUG);
}

TerrainFormation::TerrainFormation(int) {
    std::vector<std::tuple<UnderGroundCell,Vector3i>> dataUG;
    std::vector<std::tuple<AboveGroundCell,Vector3i>> dataAG;

    NutrientPack nutrientPack{};
    Water water{};

    size_t id;

    for(int x = 0; x < TS::RX; ++x){
        for(int z = 0; z < TS::RZ; ++z){
            AboveGroundCell cell{water,id};
            Vector3i vec{x,TS::RY-1,z};
            dataAG.emplace_back(tuple<AboveGroundCell,Vector3i>(cell,vec));
            id++;
        }
    }

    for(int x = 0; x < TS::RX; ++x){
        for(int y = 0; y < TS::RY-1; ++y){
            for(int z = 0; z < TS::RZ; ++z){
                UnderGroundCell cell{water,nutrientPack,id};
                Vector3i vec{x,y,z};
                dataUG.emplace_back(tuple<UnderGroundCell,Vector3i>(cell,vec));
                id++;
            }
        }
    }

    Storage = TerrainLookup<TS::RX,TS::RY,TS::RZ>(dataAG, dataUG);
}
