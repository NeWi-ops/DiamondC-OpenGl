#pragma once
#include <vector>
#include "MapGenerator.hpp"


class Joueur{
public:
    Joueur();
    bool deplacer(char direction, MapGenerator& map);

    
};