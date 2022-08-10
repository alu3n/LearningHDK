//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_TERRAINFORMATION_HPP
#define TERRAIN_TERRAINFORMATION_HPP

#include <vector>
#include <memory>
#include <array>
#include <map>
#include "TerrainAgent.hpp"
#include "Lookup.hpp"
#include "TerrainMessage.hpp"

//auto t1 = std::vector<std::tuple<AboveGroundCell,Vector3i>>();
//auto t2 = std::vector<std::tuple<UnderGroundCell,Vector3i>>();

enum class Direction{
    Lateral,
    Downward,
    Upward
};

//enum class ConstructionType{
//    OnlyUG,
//
//};

class TerrainFormation{
private:
    using TS = TerrainSettings;
    using SS = SimulationSettings;
    void ProcessVoxel(Vector3i coords);
    void ProcessAG(Vector3i coords);
    void ProcessUG(Vector3i coords);

    std::vector<std::unique_ptr<UnderGroundMessage>> PostBoxUG;
    std::vector<std::unique_ptr<AboveGroundMessage>> PostBoxAG;

    void RainSource(float AmountPerHour);
    void CornerSource(float AmountPerHour);
    void RandomRainSource(float AmountPerHour,size_t hotSpots);
public:
    TerrainLookup<TS::RX,TS::RY,TS::RZ> Storage;

    void Dispatch(size_t timeStep);
    void Clearance(size_t timeStep);
    void SendMessage(std::unique_ptr<UnderGroundMessage> message);
    void SendMessage(std::unique_ptr<AboveGroundMessage> message);

    TerrainFormation() = default;
    explicit TerrainFormation(bool);
    explicit TerrainFormation(int);

};

#endif //TERRAIN_TERRAINFORMATION_HPP
