//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#ifndef TERRAINMODEL_LOOKUP_HPP
#define TERRAINMODEL_LOOKUP_HPP

#include <vector>
#include <array>
#include "Utility/Vector.hpp"
#include "TerrainAgent.hpp"
#include "Settings.hpp"


/* Cells should have the following ID scheme
 * AGCells 0...size(ag)-1
 * UGCells size(ag)...size(ag)+size(ug)-1
 */

template<size_t RX, size_t RY, size_t RZ>
class TerrainLookup{
private:
    std::vector<AboveGroundCell> CellsAG{};
    std::vector<UnderGroundCell> CellsUG{};
    std::vector<Vector3i> CordLookup{};
    std::array<std::array<std::array<size_t,RZ>,RY>,RX> IDLookup{};

    //Helper stuff to avoid repeated calculations etc.
    using TS = TerrainSettings;
    using SS = SimulationSettings;
    Vector3f positionOffset{TS::VoxelSize * RX * 0.5, TS::VoxelSize * RY * 0.5, TS::VoxelSize * RZ * 0.5};
public:
    Water GetWater(){
        Water water;
        if(CellsAG.size() != 0){
            water = CellsAG[0].W;
        }
        else{
            water = CellsUG[0].W;
        }
        water = 0*water;
        return water;
    }

    std::array<Vector3i,6> NeighborDirections{
            Vector3i(1,0,0),
            Vector3i(0,1,0),
            Vector3i(0,0,1),
            Vector3i(-1,0,0),
            Vector3i(0,-1,0),
            Vector3i(0,0,-1)
    };

    AboveGroundCell & CellAG(size_t id){
        return CellsAG[id];
    }

    UnderGroundCell & CellUG(size_t id){
        return CellsUG[id];
    }

    AboveGroundCell & CellAG(Vector3i coords){
        return CellAG(Id(coords));
    }

    UnderGroundCell & CellUG(Vector3i coords){
        return CellUG(Id(coords));
    }

    size_t Count(CellType type){
        return type == CellType::UG ? CellsUG.size() : CellsAG.size();
    }

    Vector3i Cords(size_t id){
        return CordLookup[id];
    }
    size_t Id(Vector3i cords){
        return IDLookup[cords.X][cords.Y][cords.Z];
    }

    CellType AgentType(size_t id){
        if(id < CellsAG.size()){
            return CellType::AG;
        }
        else{
            return CellType::UG;
        }
    }
    CellType AgentType(Vector3i cords){
        return AgentType(Id(cords));
    }

    Vector3f WorldCords(size_t id){
        return WorldCords(Cords(id));
    }
    Vector3f WorldCords(Vector3i cords){
        return Vector3f(TS::VoxelSize * cords.X, TS::VoxelSize * cords.Y, TS::VoxelSize * cords.Z) - positionOffset;
    }

    TerrainLookup() = default;
    TerrainLookup(std::vector<std::tuple<AboveGroundCell,Vector3i>> cellsAG,std::vector<std::tuple<UnderGroundCell,Vector3i>> cellsUG){
        size_t index = 0;

        for(auto && var : cellsAG){
            auto cord = get<1>(var);
            CellsAG.push_back(get<0>(var));
            CordLookup.push_back(cord);
            IDLookup[cord.X][cord.Y][cord.Z] = index;
            index++;
        }

        for(auto && var : cellsUG){
            auto cord = get<1>(var);
            CellsUG.push_back(get<0>(var));
            CordLookup.push_back(cord);
            IDLookup[cord.X][cord.Y][cord.Z] = index;
            index++;
        }
    }

    bool HasNeighbor(Vector3i coords, Vector3i direction){
        auto position = coords + direction;

        if(position.X < 0 || position.X >= RX) return false;
        if(position.Y < 0 || position.Y >= RY) return false;
        if(position.Z < 0 || position.Z >= RZ) return false;

        return true;
    }
};


#endif //TERRAINMODEL_LOOKUP_HPP
