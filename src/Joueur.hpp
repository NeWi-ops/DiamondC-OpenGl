#pragma once
#include <vector>
#include "MapGenerator.hpp"


class Joueur{
public:
    Joueur();
    int gemme{0};
    int vie{3};
    int score{0};
    bool deplacer(char direction, MapGenerator& map);
    //void destruction(MapGenerator& map);
    int finduJeu();
    void gemmeTrouvee();
    
};