//
// Created by Vojtěch Pröschl on 05.08.2022.
//

#include <iostream>
#include <stdexcept>
#include "Nutrients.hpp"

std::ostream & operator<<(std::ostream & os,NutrientType N){
    switch(N){
        case NutrientType::N:
            os << "N";
            break;
        case NutrientType::K:
            os << "K";
            break;
        case NutrientType::P:
            os << "P";
            break;
    }
    return os;
}

Nutrient::Nutrient(enum NutrientType nutrientType, float amount) {
    Type = nutrientType;
    Amount = amount;
}

NutrientType Nutrient::NutrientType() const {
    return Type;
}

NutrientPack::NutrientPack(std::vector<Nutrient> nutrients) {
    Nutrients = nutrients;
}

std::vector<NutrientType> NutrientPack::NutrientPackType() const{
    std::vector<NutrientType> temp;
    for(auto && N : Nutrients){
        temp.push_back(N.NutrientType());
    }
    return temp;
}

bool operator==(const Nutrient & N1,const Nutrient & N2){
    return N1.NutrientType() == N2.NutrientType();
}

bool operator==(const NutrientPack & NP1, const NutrientPack & NP2){
    return NP1.NutrientPackType() == NP2.NutrientPackType();
}

Nutrient operator+(const Nutrient & N1, const Nutrient & N2){
    if(!(N1==N2)) throw std::invalid_argument("Nutrients must have same type for addition");
    auto temp = N1;
    temp.Amount = N1.Amount + N2.Amount;
    return temp;
}

Nutrient operator-(const Nutrient & N1, const Nutrient & N2){
    if(!(N1==N2)) throw std::invalid_argument("Nutrients must have same type for subtraction");
    auto temp = N1;
    temp.Amount = N1.Amount - N2.Amount;
    return temp;
}

Nutrient operator*(float scalar, const Nutrient & N){
    auto temp = N;
    temp.Amount = scalar * temp.Amount;
    return temp;
}

std::ostream & operator<<(std::ostream & os,const Nutrient & N){
    os << "(" << N.Type << "," << N.Amount << ")";
    return os;
}

NutrientPack operator+(const NutrientPack & NP1, const NutrientPack & NP2){
    if(!(NP1==NP2)) throw std::invalid_argument("NutrientPacks must have same type for addition");
    auto temp = NP1;
    for(int i = 0; i < temp.Nutrients.size(); i++){
        temp.Nutrients[i] = NP1.Nutrients[i] + NP2.Nutrients[i];
    }
    return temp;
}

NutrientPack operator-(const NutrientPack & NP1, const NutrientPack & NP2){
    if(!(NP1==NP2)) throw std::invalid_argument("NutrientPacks must have same type for subtraction");
    auto temp = NP1;
    for(int i = 0; i < temp.Nutrients.size(); i++){
        temp.Nutrients[i] = NP1.Nutrients[i] - NP2.Nutrients[i];
    }
    return temp;
}

NutrientPack operator*(float scalar, const NutrientPack & NP){
    auto temp = NP;
    for(int i = 0; i < temp.Nutrients.size(); i++){
        temp.Nutrients[i] = scalar * NP.Nutrients[i];
    }
    return temp;
}

std::ostream & operator<<(std::ostream & os, const NutrientPack & NP){
    os << "( ";
    for(int i = 0; i < NP.Nutrients.size(); i++){
        os << NP.Nutrients[i];
        os << " ";
    }
    os << ")";
    return os;
}



