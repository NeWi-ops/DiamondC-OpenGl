#include "MapGenerator.hpp"
#include "Joueur.hpp"
#include "Enemis.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
//#include <img/img.h>


// Fonction pour lire un caractère sans attendre Entrée / CA NE MARCHE QUE POUR MAC/LINUX
//Pour Windows, il faudrait utiliser _getch() de <conio.h>.
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    // Créer une carte de taille 50x50
    MapGenerator map(50, 50);

    // Générer la carte
    map.genererCarte();

    // Afficher la carte
    map.afficherCarte();

    // Créer un joueur
    Joueur J;

    std::cout << "Entrez une direction (z/s/q/d) ou 'a' pour quitter: ";

    
    while (true) {
        //std::cout << "Entrez une direction (z/s/q/d) ou 'a' pour quitter: ";
        //std::cin >> direction;
        map.deplacerEnnemis(map.generer_le_flow_field());
        
        char direction{getch()};
        if (direction == 'a' || J.finduJeu()==1 || J.finduJeu()==2) {break;}
        
        J.deplacer(direction,map);
        
        map.afficherCarte();
        // J.destruction(map);
        // map.afficherCarte();
    }

    return 0;
}


