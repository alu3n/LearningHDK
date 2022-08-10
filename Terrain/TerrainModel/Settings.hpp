//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#ifndef TERRAINMODEL_SETTINGS_HPP
#define TERRAINMODEL_SETTINGS_HPP

#include <vector>

struct TerrainSettings{
    static constexpr size_t RX = 20;
    static constexpr size_t RY = 20;
    static constexpr size_t RZ = 20;

    static constexpr float VoxelSize = 0.25;
    static constexpr float VoxelVolume = VoxelSize*VoxelSize*VoxelSize;
};

struct SimulationSettings{
    static constexpr float TimeStepDuration = 1;

    static constexpr float DiffusionThreshold = 0.05; //of its capacity
    static constexpr float DiffusionLimitPerHour = 0.6; //of its water above capacity

    static constexpr float LateralDiffusionPerHour = 0.05; //m^3 per m^2 * h^-1
    static constexpr float UpDiffusionPerHour = 0.001;
    static constexpr float DownDiffusionPerHour = 0.3;
    static constexpr float SurfaceDiffusionPerHour = 0.1;

//    static constexpr float DiffusionPerTickLimit = SurfaceDiffusionPerHour * TerrainSettings::VoxelSize * TerrainSettings::VoxelSize * TimeStepDuration;


    static constexpr float RainAmount = 0.01; //m^3 per m^2 of surface per hour
};



#endif //TERRAINMODEL_SETTINGS_HPP
