//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#include <algorithm>
#include "TerrainFormation.hpp"
#include "TerrainMessage.hpp"

UnderGroundMessage::UnderGroundMessage(MessageTypes messageType, unsigned int targetID, Water water) : W(water) {
    Type = messageType;
    TargetID = targetID;
}

AboveGroundMessage::AboveGroundMessage(MessageTypes messageType, unsigned int targetID, Water water) : W(water) {
    Type = messageType;
    TargetID = targetID;
}

void UnderGroundMessage::Receive(UnderGroundCell &agent, unsigned int simulationStep) {
    if(Type == MessageTypes::Increase){
        agent.W = agent.W + W;
    }
    else{
        agent.W = agent.W - W;
    }
}

void AboveGroundMessage::Receive(AboveGroundCell &agent, unsigned int simulationStep) {
    if(Type == MessageTypes::Increase){
        agent.W = agent.W + W;
    }
    else{
        agent.W = agent.W - W;
    }
}

