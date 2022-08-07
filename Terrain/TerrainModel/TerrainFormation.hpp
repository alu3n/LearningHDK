//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#ifndef TERRAIN_TERRAINFORMATION_HPP
#define TERRAIN_TERRAINFORMATION_HPP

#include <vector>
#include <memory>
#include <array>
#include "TerrainAgent.hpp"
#include "TerrainMessage.hpp"

//region PROPERTIES
constexpr size_t ResolutionX = 10;
constexpr size_t ResolutionY = 5;
constexpr size_t ResolutionZ = 20;

constexpr float TimeStepDuration = 1; //In hours
//endregion

class TerrainFormation{
public:
    void Tick(unsigned int simulationStep);
    void Clearance(unsigned int simulationStep);
    void SendMessage(const UnderGroundMessage & message);
    void SendMessage(const AboveGroundMessage & message);


    TerrainFormation();
    //template<typename HeightField>
    //explicit TerrainFormation(const HeightField & heightField);

private:
    std::vector<std::unique_ptr<UnderGroundMessage>> UnderGroundPostBox;
    std::vector<std::unique_ptr<AboveGroundMessage>> AboveGroundPostBox;

    std::vector<UnderGroundCell> UnderGroundCells;
    std::vector<AboveGroundCell> AboveGroundCells;

    std::array<std::array<std::array<std::tuple<CellType,unsigned int>,ResolutionZ>,ResolutionY>,ResolutionX> LookUpArray;
};

#endif //TERRAIN_TERRAINFORMATION_HPP
