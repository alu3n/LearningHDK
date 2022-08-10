//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#include <iostream>
#include "Water.hpp"

Water::Water(float volume, NutrientPack nutrientPack) : NP(nutrientPack.Nutrients) {
    Volume = volume;
}

std::vector<NutrientType> Water::WaterType(){
    return NP.NutrientPackType();
}

bool operator==(Water W1, Water W2){
    return W1.NP==W2.NP;
}

Water operator+(Water W1, Water W2){
    auto temp = W1;
    temp.NP = W1.NP + W2.NP;
    temp.Volume = W1.Volume + W2.Volume;
    return temp;
}

Water operator-(Water W1, Water W2){
    auto temp = W1;
    temp.NP = W1.NP - W2.NP;
    temp.Volume = W1.Volume - W2.Volume;
    return temp;
}

Water operator*(float scalar, Water W){
    auto temp = W;
    temp.Volume = scalar * temp.Volume;
    temp.NP = scalar * temp.NP;
    return temp;
}

std::ostream & operator<<(std::ostream & os, Water W){
    os << "( " << W.NP << " " << W.Volume << " )";
    return os;
}

Water::Water() {
    Volume = 0;
    NP = NutrientPack();
}