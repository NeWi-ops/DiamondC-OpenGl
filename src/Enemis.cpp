#include Enemis.hpp
#include <iostream>

Enemis::Enemis(int x,int y) {}

void Enemis::attaque(MapGenerator& map, Joueur& J) {
    auto& pos = map.getPositionJoueur();
    int joueurX = pos.first;
    int joueurY = pos.second;

    // Logique d'attaque simple : si l'ennemi est adjacent au joueur, il attaque
    if ((joueurX == x && (joueurY == y - 1 || joueurY == y + 1)) || 
        (joueurY == y && (joueurX == x - 1 || joueurX == x + 1))) {
        std::cout << "L'ennemi attaque le joueur !" << std::endl;
        J.vie--;
        if (J.vie <= 0) {
            std::cout << "Le joueur a été vaincu par l'ennemi !" << std::endl;
            J.finduJeu(); // Mettre à jour l'état du jeu
        }
    }
}
