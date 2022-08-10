//
// Created by Vojtěch Pröschl on 08.08.2022.
//

#include <iostream>
#include <chrono>
#include "TerrainSimulation.hpp"


using namespace std;

constexpr int timeRange = 100;

int main(){
    TerrainSimulation simulation;

    auto start = std::chrono::system_clock::now();

    for(int i = 0; i < timeRange; ++i){
        cout << "Simulating frame: " << i << endl;
        simulation.Tick(i);
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << elapsed.count() << std::endl;
}