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

struct UnderGroundMessage{
    MessageTypes Type;
    unsigned int TargetID;
    void Receive(const UnderGroundCell & agent, unsigned int simulationStep);
};

struct AboveGroundMessage{
    MessageTypes Type;
    unsigned int TargetID;
    void Receive(const AboveGroundCell & agent, unsigned int simulationStep);
};

#endif //TERRAIN_TERRAINMESSAGE_HPP
