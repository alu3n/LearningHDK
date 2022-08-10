//
// Created by Vojtěch Pröschl on 06.08.2022.
//

#ifndef TERRAIN_TERRAINMESSAGE_HPP
#define TERRAIN_TERRAINMESSAGE_HPP

#include "TerrainAgent.hpp"

enum class MessageTypes{
    Increase,
    Decrease
};


//struct TerrainMessage{
//    virtual CellType TargetType() = 0;
//};

struct UnderGroundMessage{
    MessageTypes Type;
    unsigned int TargetID;
    Water W;
    UnderGroundMessage(MessageTypes,unsigned int,Water);
    void Receive(UnderGroundCell & agent, unsigned int simulationStep);
};

struct AboveGroundMessage{
    MessageTypes Type;
    unsigned int TargetID;
    Water W;
    AboveGroundMessage(MessageTypes,unsigned int,Water);
    void Receive(AboveGroundCell & agent, unsigned int simulationStep);
};

#endif //TERRAIN_TERRAINMESSAGE_HPP
