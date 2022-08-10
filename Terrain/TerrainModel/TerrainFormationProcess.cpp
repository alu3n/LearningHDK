//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#include <algorithm>
#include "TerrainFormation.hpp"
#include "Utility/Math.hpp"



void TerrainFormation::ProcessVoxel(Vector3i coords) {
    if(Storage.AgentType(coords) == CellType::UG){
        ProcessUG(coords);
    }
    else{
        ProcessAG(coords);
    }
}

void TerrainFormation::ProcessAG(Vector3i coords) {
    //Only diffuse to neighbors that are soil/air
}

void TerrainFormation::ProcessUG(Vector3i coords) {
    //Only diffuse to neighbors that are soil

    std::vector<std::tuple<Vector3i,Direction>> neighbors;
    for(auto && direction : Storage.NeighborDirections){
        if(Storage.HasNeighbor(coords,direction)){
            if(direction.Y == -1){
                neighbors.emplace_back(coords+direction,Direction::Downward);
            }
            else if(direction.Y == 1){
                neighbors.emplace_back(coords+direction,Direction::Upward);
            }
            else{
                neighbors.emplace_back(coords+direction,Direction::Lateral);
            }
        }
    }

    auto myWater = Storage.CellUG(coords).W;
    auto totalTickDiffusionLimit = SS::DiffusionLimitPerHour * TS::VoxelVolume;
    auto availableVolume = min<float>(myWater.Volume,totalTickDiffusionLimit);

    if(availableVolume <= 0) return;

    std::vector<float> intakeLimits{};

    float totalIntakeLimit = 0;

    for(auto && neighbor : neighbors){
        float volumeDifference = myWater.Volume - Storage.CellUG(std::get<0>(neighbor)).W.Volume;
        float possibleIntake;
        if(std::get<1>(neighbor) == Direction::Downward){
            possibleIntake = min<float>(volumeDifference,TS::VoxelVolume*SS::DownDiffusionPerHour);
        }
        else if(std::get<1>(neighbor) == Direction::Upward){
            possibleIntake = min<float>(volumeDifference,TS::VoxelVolume*SS::UpDiffusionPerHour);
        }
        else{
            possibleIntake = min<float>(volumeDifference,TS::VoxelVolume*SS::LateralDiffusionPerHour);
        }
        if(volumeDifference <= 0){
            possibleIntake = 0;
        }
        intakeLimits.push_back(possibleIntake);
        totalIntakeLimit += possibleIntake;
    }

    if(totalIntakeLimit <= 0) return;

    auto multiplier = min<float>(1,availableVolume/totalIntakeLimit);

    for(int i = 0; i < neighbors.size(); ++i){
        if(intakeLimits[i] > 0){
            auto water = myWater;
            water.Volume = multiplier*intakeLimits[i];
            auto increaseMessage = std::make_unique<UnderGroundMessage>(MessageTypes::Increase,Storage.Id(get<0>(neighbors[i])),water);
            SendMessage(std::move(increaseMessage));
        }
    }

    myWater.Volume = totalIntakeLimit*multiplier;
    auto decreaseMessage = std::make_unique<UnderGroundMessage>(MessageTypes::Decrease,Storage.Id(coords),myWater);
    SendMessage(std::move(decreaseMessage));
}

