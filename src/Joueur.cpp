#include "Joueur.hpp"
#include "MapGenerator.hpp"
#include <iostream>

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
        else if (carte[nouvelleY][nouvelleX] == 1) {
            carte[nouvelleY][nouvelleX] = 0; //on détruit la case
            return true; 
        }
        else if (carte[nouvelleY][nouvelleX] == 2 || carte[nouvelleY][nouvelleX] == 4) {//on peut modifier pour que le score baisse + avec un piège ou l'inverse
            std::cout << "Vous avez trouvé un ennemi/... !" << std::endl;
            carte[nouvelleY][nouvelleX] = 0;
            pos.first = nouvelleX;
            pos.second = nouvelleY;
            Joueur::vie--;
            finduJeu();
            return false; 
        }
        else if (carte[nouvelleY][nouvelleX] == 3) {
            std::cout << "Vous avez trouvé une gemme !" << std::endl;
            gemmeTrouvee();
            carte[nouvelleY][nouvelleX] = 0;
            pos.first = nouvelleX;
            pos.second = nouvelleY;
            return true; 
        }
    
    }
    return false; 
}

// void Joueur::destruction(MapGenerator& map) {
//     auto& pos = map.getPositionJoueur();
//     if(pos.first == 1 && pos.second == 1) {
//         map.getCarte()[pos.second][pos.first] = 0; // On détruit la case
//     }
// }

int Joueur::finduJeu(){ //si le retour est true, on affiche une image de victoire, si false, une image de défaite
    if (Joueur::gemme==10 && Joueur::vie > 0) {
        std::cout << "Vous avez gagné ! Votre score est de " << Joueur::score << "." << std::endl;
        return 1; //page de victoire
    }
    else if (Joueur::vie <= 0) {
        std::cout << "Vous avez perdu ! Votre score est de " << Joueur::score << "." << std::endl;
        return 2; //page de défaite
    }
    
}

void Joueur::gemmeTrouvee(){
    Joueur::gemme++;
    Joueur::score += 10;

}
