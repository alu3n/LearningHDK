cmake_minimum_required(VERSION 3.23)
project(TerrainModel)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        TerrainModel main.cpp
        Nutrients.cpp
        TerrainAgent.cpp
        TerrainFormation.cpp
        TerrainSimulation.cpp
        Water.cpp
        TerrainMessage.cpp main.cpp Utility/Vector.hpp Utility/Vector.cpp Settings.hpp Lookup.hpp TerrainFormationProcess.cpp TerrainFormationConstructors.cpp Utility/Math.hpp DiffusionFunctions.hpp SurfaceComposition.hpp)
