#include "MapGenerator.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>




MapGenerator::MapGenerator(int largeur, int hauteur)
    : m_largeur(largeur), m_hauteur(hauteur) {
    m_carte.resize(m_hauteur, std::vector<int>(m_largeur, 0));
}

std::pair<int, int>& MapGenerator::getPositionJoueur() { return m_positionJoueur; }
std::vector<std::vector<int>>& MapGenerator::getCarte() { return m_carte; }
int MapGenerator::getLargeur() const { return m_largeur; }
int MapGenerator::getHauteur() const { return m_hauteur; }

void MapGenerator::genererCarte() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Initialisation aléatoire
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            m_carte[y][x] = (std::rand() % 100) < 50 ? 1 : 0;
        }
    }

    for (int i = 0; i < 4; ++i) {
        appliquerReglesAutomate();
    }

    // Placement sans chevauchement
    placerElements(20, 2); // pièges
    placerElements(10, 3); // gemmes
    placerElements(5, 4);  // ennemis
    trouverPointDeDepartJoueur();  // Choisir le point de départ du joueur

}

void MapGenerator::appliquerReglesAutomate() {
    std::vector<std::vector<int> > nouvelleCarte = m_carte;

    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            int voisinsPlein = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) { //qd dx et dy = 0, est on compte la case elle même?
                        voisinsPlein += m_carte[ny][nx];
                    }
                }
            }

            if (m_carte[y][x] == 1 && voisinsPlein < 5) {
                nouvelleCarte[y][x] = 0;
            } else if (m_carte[y][x] == 0 && voisinsPlein >= 5) {
                nouvelleCarte[y][x] = 1;
            }
        }
    }

    m_carte = nouvelleCarte;
}

std::vector<std::pair<int, int> > MapGenerator::trouverCasesVides() const {
    std::vector<std::pair<int, int> > vides;
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            if (m_carte[y][x] == 0) {
                vides.emplace_back(x, y);
            }
        }
    }
    return vides;
}

void MapGenerator::placerElements(int nb, int valeur) {
    std::vector<std::pair<int, int> > casesVides = trouverCasesVides();
    std::random_shuffle(casesVides.begin(), casesVides.end());

    int compteur = 0;
    for (auto& pos : casesVides) {
        if (compteur >= nb) break;
        int x = pos.first;
        int y = pos.second;
        m_carte[y][x] = valeur;
        ++compteur;
    }
}

void MapGenerator::afficherCarte() const {
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            if (m_positionJoueur.first == x && m_positionJoueur.second == y) {
                std::cout << "@ ";  // Joueur
            } else {
                switch (m_carte[y][x]) {
                    case 0: std::cout << ". "; break; //case vide
                    case 1: std::cout << "# "; break; //case mur
                    case 2: std::cout << "X "; break; //case piège
                    case 3: std::cout << "* "; break; //case gemme
                    case 4: std::cout << "E "; break; //case ennemi
                    default: std::cout << "? "; break; 
                }
            }
        }
        std::cout << "\n";
    }
    
        std::cout << "\n";
       }

       void MapGenerator::trouverPointDeDepartJoueur() {
        std::vector<std::pair<int, int> > vides = trouverCasesVides();
        std::random_shuffle(vides.begin(), vides.end());
    
        for (const auto& pos : vides) {
            int x = pos.first;
            int y = pos.second;
    
            if (m_carte[y][x] == 0 && estAssezLoinDesEnnemis(x, y, 10)) {
                m_positionJoueur = {x, y};
                return;
            }
        }
    
        // Si aucun point ne respecte la contrainte, on prend le premier vide (fallback)
        if (!vides.empty()) {
            m_positionJoueur = vides[0];
        } else {
            m_positionJoueur = {0, 0};  // Aucun point valide trouvé
        }
    }
    
    bool MapGenerator::estAssezLoinDesEnnemis(int x, int y, int distanceMin) const {
        for (int j = 0; j < m_hauteur; ++j) {
            for (int i = 0; i < m_largeur; ++i) {
                if (m_carte[j][i] == 4) { // Ennemi
                    int distance = abs(x - i) + abs(y - j);
                    if (distance < distanceMin) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    

