#pragma once 
#include"MapGenerator.hpp"
#include"Joueur.hpp"


class Enemis {
public:
    Enemis(int x, int y);
    void attaque(MapGenerator& map, Joueur& J);

}