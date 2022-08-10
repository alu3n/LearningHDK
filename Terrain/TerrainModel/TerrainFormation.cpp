//
// Created by Vojtěch Pröschl on 06.08.2022.
//

#include <memory>
#include "TerrainFormation.hpp"

void TerrainFormation::Dispatch(size_t timeStep) {
//    RainSource(0.01);
//    CornerSource(0.2);
    RandomRainSource(0.026,10);
    for (int x = 0; x < TS::RX; ++x) {
        for (int y = 0; y < TS::RY; ++y) {
            for (int z = 0; z < TS::RZ; ++z) {
                ProcessVoxel({x,y,z});
            }
        }
    }
}

void TerrainFormation::Clearance(size_t timeStep) {
    for(auto && messageUG : PostBoxUG){
        messageUG->Receive(Storage.CellUG(messageUG->TargetID),timeStep);
    }

    for(auto && messageAG : PostBoxAG){
        messageAG->Receive(Storage.CellAG(messageAG->TargetID),timeStep);
    }

    PostBoxAG.clear();
    PostBoxUG.clear();
}

void TerrainFormation::RainSource(float AmountPerHour){
    auto water = Storage.CellUG(0).W;
    water.Volume = AmountPerHour*(TS::VoxelSize*TS::VoxelSize);
    for(int x = 0; x < TS::RX; ++x){
        for(int z = 0; z < TS::RZ; ++z){
            auto msg = std::make_unique<UnderGroundMessage>(MessageTypes::Increase,Storage.Id({x,TS::RY-1,z}),water);
            SendMessage(std::move(msg));
        }
    }
}

void TerrainFormation::CornerSource(float AmountPerHour) {
    auto coords = Vector3i(TS::RX-1,TS::RY-1,TS::RZ-1);
    auto water = Storage.CellUG(0).W;

    std::unique_ptr<UnderGroundMessage> msgUG;
    std::unique_ptr<AboveGroundMessage> msgAG;

    water.Volume = AmountPerHour;

    switch(Storage.AgentType(coords)){
        case CellType::UG:
            msgUG = std::make_unique<UnderGroundMessage>(MessageTypes::Increase,Storage.Id(coords),water);
            SendMessage(std::move(msgUG));
            break;
        case CellType::AG:
            msgAG = std::make_unique<AboveGroundMessage>(MessageTypes::Increase,Storage.Id(coords),water);
            SendMessage(std::move(msgAG));
            break;
    }
}




void TerrainFormation::SendMessage(std::unique_ptr<AboveGroundMessage> message) {
    PostBoxAG.push_back(std::move(message));
}

void TerrainFormation::SendMessage(std::unique_ptr<UnderGroundMessage> message) {
    PostBoxUG.push_back(std::move(message));
}

void TerrainFormation::RandomRainSource(float AmountPerHour, size_t hotSpots) {
//    auto water = (Storage.AgentType(0) == CellType::UG) ? Storage.CellUG(0).W : Storage.CellAG(0).W;//Storage.CellUG(0).W;
    auto water = Storage.GetWater();
    water.Volume = AmountPerHour;

    std::unique_ptr<UnderGroundMessage> msgUG;
    std::unique_ptr<AboveGroundMessage> msgAG;

    for(int i = 0; i < hotSpots; ++i){
        int x = rand() % TS::RX;
        int z = rand() % TS::RZ;
        Vector3i coords{x,TS::RY-1,z};
        switch(Storage.AgentType(coords)){
            case CellType::UG:
                msgUG = std::make_unique<UnderGroundMessage>(MessageTypes::Increase,Storage.Id(coords),water);
                SendMessage(std::move(msgUG));
            case CellType::AG:
                msgAG = std::make_unique<AboveGroundMessage>(MessageTypes::Increase,Storage.Id(coords),water);
                SendMessage(std::move(msgAG));
        }
    }
}