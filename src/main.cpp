#include "MapGenerator.hpp"
#include "Joueur.hpp"
#include <iostream>

int main() {
    // Créer une carte de taille 50x50
    MapGenerator map(50, 50);

    // Générer la carte
    map.genererCarte();

    // Afficher la carte
    map.afficherCarte();

    // Créer un joueur
    Joueur J;

    //Deplacement du joueur
    char direction;
    while (true) {
        std::cout << "Entrez une direction (z/s/q/d) ou 'a' pour quitter: ";
        std::cin >> direction;

        if (direction == 'a') {
            break;
        }
        J.deplacer(direction,map);
        map.afficherCarte();
    }

    return 0;
}


