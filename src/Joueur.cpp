#include "Joueur.hpp"
#include "MapGenerator.hpp"

Joueur::Joueur() {};

bool Joueur::deplacer(char direction, MapGenerator& map) {
    int dx = 0, dy = 0;

    switch (direction) {
        case 'z': dy = -1; break; // Haut
        case 's': dy = 1; break;  // Bas
        case 'q': dx = -1; break; // Gauche
        case 'd': dx = 1; break;  // Droite
        default: return false;    
    }

    auto& pos = map.getPositionJoueur();
    int nouvelleX = pos.first + dx;
    int nouvelleY = pos.second + dy;

    if (nouvelleX >= 0 && nouvelleX < map.getLargeur() &&
        nouvelleY >= 0 && nouvelleY < map.getHauteur()) {
        auto& carte = map.getCarte();
        if (carte[nouvelleY][nouvelleX] == 0) {
            pos.first = nouvelleX;
            pos.second = nouvelleY;
            return true; 
        }
    }
    return false; 
}

