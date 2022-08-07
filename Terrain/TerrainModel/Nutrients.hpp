//
// Created by Vojtěch Pröschl on
// 05.08.2022.
//

#ifndef TERRAIN_NUTRIENTS_HPP
#define TERRAIN_NUTRIENTS_HPP

#include <vector>

enum class NutrientType{
    K,
    N,
    P
};

std::ostream & operator<<(std::ostream &,NutrientType);

struct Nutrient{
    float Amount;
    NutrientType Type;
    Nutrient(NutrientType,float);
    NutrientType NutrientType() const;
};

struct NutrientPack{
    std::vector<Nutrient> Nutrients;
    explicit NutrientPack(std::vector<Nutrient> nutrients);
    std::vector<NutrientType> NutrientPackType() const;
};

//Note: Those two aren't comparing values but types!
bool operator==(const Nutrient &,const Nutrient &);
bool operator==(const NutrientPack &,const NutrientPack &);

Nutrient operator+(const Nutrient &, const Nutrient &);
Nutrient operator-(const Nutrient &, const Nutrient &);
Nutrient operator*(float,const Nutrient &);
std::ostream & operator<<(std::ostream &,const Nutrient &);

NutrientPack operator+(const NutrientPack &, const NutrientPack &);
NutrientPack operator-(const NutrientPack &, const NutrientPack &);
NutrientPack operator*(float, const NutrientPack &);
std::ostream & operator<<(std::ostream &, const NutrientPack &);

#endif //TERRAIN_NUTRIENTS_HPP
