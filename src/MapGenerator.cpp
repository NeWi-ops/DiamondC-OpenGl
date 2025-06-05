#include "MapGenerator.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Joueur.hpp"




MapGenerator::MapGenerator(int largeur, int hauteur)
    : m_largeur(largeur), m_hauteur(hauteur) {
    m_carte.resize(m_hauteur, std::vector<int>(m_largeur, 0));
}

std::pair<int, int>& MapGenerator::getPositionJoueur() { return m_positionJoueur; }
const std::vector<std::vector<int>>& MapGenerator::getCarte() const { return m_carte; }
std::vector<std::vector<int>>& MapGenerator::getCarte() {return m_carte;}
int MapGenerator::getLargeur() const { return m_largeur; }
int MapGenerator::getHauteur() const { return m_hauteur; }
std::vector<std::pair<int, int>>& MapGenerator::getPositionEnnemis() {return m_positionEnnemis;}

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
        if(valeur == 4) { // Si c'est un ennemi, on stocke sa position
            m_positionEnnemis.push_back({x, y});
            m_casesSousEnnemis.push_back(0); 
            m_positionEnnemisFloat.push_back({float(x), float(y)});
        }
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

// void MapGenerator::deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur) { //version premeire avec beug sur fils d ennemis
//     std::vector<std::vector<bool>> reservee(m_hauteur, std::vector<bool>(m_largeur, false));
//     for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
//         auto& pos = m_positionEnnemis[i];
//         int x = pos.first;
//         int y = pos.second;
//         int minDist = flow_field[y][x];
//         int bestX = x, bestY = y;
//         //int type_case = m_carte[y][x]; // sauvegarde le type de la case actuelle
//         for (int dx : {-1, 0, 1}) {
//             for (int dy : {-1, 0, 1}) {
//                 if (abs(dx) + abs(dy) != 1) continue;
            
//                 int nx = x + dx, ny = y + dy;
//                 if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
//                     if (flow_field[ny][nx] != -1 && flow_field[ny][nx] < minDist && m_carte[ny][nx] != 1) {
//                         minDist = flow_field[ny][nx];
//                         bestX = nx;
//                         bestY = ny;
//                         //type_case = m_carte[y][x];
//                     }
//                 }
//             }
//         }
//         reservee[bestY][bestX] = true; //pour eviter que 2 ennemis soit sur la même case
//         if (bestX == m_positionJoueur.first && bestY == m_positionJoueur.second) {
//             joueur.vie--;
//             std::cout << "Le joueur est attaqué par un ennemi !" << std::endl;
//             }
    
//         // Met à jour la carte et la position
//         m_carte[y][x] = m_casesSousEnnemis[i];
//         m_casesSousEnnemis[i] = m_carte[bestY][bestX];
//         //type_case = m_carte[bestY][bestX]; // remet l'ancienne case
//         m_carte[bestY][bestX] = 4;
        
//         pos = {bestX, bestY};
//     }
// }

void MapGenerator::deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur ) {
    // Phase 1 : Calcul des déplacements
std::vector<std::pair<int, int>> nouvellesPositions = m_positionEnnemis;
std::vector<int> nouvellesCasesSousEnnemis = m_casesSousEnnemis;
std::vector<std::vector<bool>> reservee(m_hauteur, std::vector<bool>(m_largeur, false));

// Marquer les positions actuelles comme réservées (pour éviter qu'un ennemi "saute" sur un autre)
for (const auto& pos : m_positionEnnemis) {
    reservee[pos.second][pos.first] = true;
}

for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
    auto& pos = m_positionEnnemis[i];
    int x = pos.first;
    int y = pos.second;
    int minDist = flow_field[y][x];
    int bestX = x, bestY = y;
    for (int dx : {-1, 0, 1}) {
        for (int dy : {-1, 0, 1}) {
            if (abs(dx) + abs(dy) != 1) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
                // On ne va pas sur une case déjà réservée
                if (!reservee[ny][nx] && flow_field[ny][nx] != -1 && flow_field[ny][nx] < minDist && m_carte[ny][nx] != 1) {
                    minDist = flow_field[ny][nx];
                    bestX = nx;
                    bestY = ny;
                }
            }
        }
    }
    
    // Réserve la nouvelle case d'arrivée pour cet ennemi
    reservee[bestY][bestX] = true;
    nouvellesPositions[i] = {bestX, bestY};
    nouvellesCasesSousEnnemis[i] = m_carte[bestY][bestX];
    if (bestX == m_positionJoueur.first && bestY == m_positionJoueur.second) {
            joueur.vie--;
            std::cout << "Le joueur est attaqué par un ennemi !" << std::endl;
            }
}

// Phase 2 : Application des déplacements
// 1. Remettre les anciennes cases
for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
    int x = m_positionEnnemis[i].first;
    int y = m_positionEnnemis[i].second;
    m_carte[y][x] = m_casesSousEnnemis[i];
}

// 2. Placer les ennemis sur leurs nouvelles cases
for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
    int bestX = nouvellesPositions[i].first;
    int bestY = nouvellesPositions[i].second;
    m_casesSousEnnemis[i] = nouvellesCasesSousEnnemis[i];
    m_carte[bestY][bestX] = 4;
    m_positionEnnemis[i] = {bestX, bestY};
}

// 3. Nettoyage des "fantômes" d'ennemis
for (int y = 0; y < m_hauteur; ++y) {
    for (int x = 0; x < m_largeur; ++x) {
        bool isEnnemi = false;
        for (const auto& pos : m_positionEnnemis) {
            if (pos.first == x && pos.second == y) {
                isEnnemi = true;
                break;
            }
        }
        if (!isEnnemi && m_carte[y][x] == 4) {
            m_carte[y][x] = 0; // ou m_casesSousEnnemis[...] si tu veux restaurer autre chose
        }
    }
}
}

// void MapGenerator::deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur ,float delta) {
//     // Phase 1 : Calcul des déplacements
// std::vector<std::pair<int, int>> nouvellesPositions = m_positionEnnemis;
// std::vector<int> nouvellesCasesSousEnnemis = m_casesSousEnnemis;
// std::vector<std::vector<bool>> reservee(m_hauteur, std::vector<bool>(m_largeur, false));

// for (const auto& pos : m_positionEnnemis) {
//     reservee[pos.second][pos.first] = true;
// }

// float vitesse = 4.0f; // cases/seconde


// for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
//     auto& pos = m_positionEnnemis[i];
//     int x = pos.first;
//     int y = pos.second;
//     int minDist = flow_field[y][x];
//     int bestX = x, bestY = y;
//     for (int dx : {-1, 0, 1}) {
//         for (int dy : {-1, 0, 1}) {
//             if (abs(dx) + abs(dy) != 1) continue;
//             int nx = x + dx, ny = y + dy;
//             if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
//                 if (flow_field[ny][nx] != -1 && flow_field[ny][nx] < minDist && m_carte[ny][nx] != 1) {
//                     minDist = flow_field[ny][nx];
//                     bestX = nx;
//                     bestY = ny;
//                     m_positionEnnemisFloat[i].first += dx * vitesse * delta;
//                     m_positionEnnemisFloat[i].second += dy * vitesse * delta;

//                     // Si la moitié de la case suivante est franchie, mets à jour la position logique
//                     int oldX = m_positionEnnemis[i].first;
//                     int oldY = m_positionEnnemis[i].second;
//                     int newX = int(m_positionEnnemisFloat[i].first + 0.5f);
//                     int newY = int(m_positionEnnemisFloat[i].second + 0.5f);

//                     if (newX != oldX || newY != oldY) {
//                         // Mets à jour la grille et la position logique
//                         // (utilise la même logique de sauvegarde/restauration de case que tu as déjà)
//                         m_positionEnnemis[i] = {newX, newY};
//                     }
//                 }
//             }
//         }
//     }

//     reservee[bestY][bestX] = true;
//     nouvellesPositions[i] = {bestX, bestY};
//     nouvellesCasesSousEnnemis[i] = m_carte[bestY][bestX];
    
// }

// // Phase 2 : Application des déplacements
// // 1. Remettre les anciennes cases
// for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
//     int x = m_positionEnnemis[i].first;
//     int y = m_positionEnnemis[i].second;
//     m_carte[y][x] = m_casesSousEnnemis[i];
// }

// // 2. Placer les ennemis sur leurs nouvelles cases
// for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
//     int bestX = nouvellesPositions[i].first;
//     int bestY = nouvellesPositions[i].second;
//     m_casesSousEnnemis[i] = nouvellesCasesSousEnnemis[i];
//     m_carte[bestY][bestX] = 4;
//     m_positionEnnemis[i] = {bestX, bestY};
// }

// // 3. Nettoyage des "fantômes" d'ennemis
// for (int y = 0; y < m_hauteur; ++y) {
//     for (int x = 0; x < m_largeur; ++x) {
//         bool isEnnemi = false;
//         for (const auto& pos : m_positionEnnemis) {
//             if (pos.first == x && pos.second == y) {
//                 isEnnemi = true;
//                 break;
//             }
//         }
//         if (!isEnnemi && m_carte[y][x] == 4) {
//             m_carte[y][x] = 0; // ou m_casesSousEnnemis[...] si tu veux restaurer autre chose
//         }
//     }
// }
// }

// void MapGenerator::deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur, float delta) {
//     std::vector<std::pair<int, int>> nouvellesPositions = m_positionEnnemis;
//     std::vector<int> nouvellesCasesSousEnnemis = m_casesSousEnnemis;
//     std::vector<std::vector<bool>> reservee(m_hauteur, std::vector<bool>(m_largeur, false));

//     for (const auto& pos : m_positionEnnemis) {
//         reservee[pos.second][pos.first] = true;
//     }

//     float vitesse = 25.0f; // cases/seconde

//     for (size_t i = 0; i < m_positionEnnemis.size(); ++i) {
//         auto& pos = m_positionEnnemis[i];
//         int x = pos.first;
//         int y = pos.second;
//         int minDist = flow_field[y][x];
//         int bestX = x, bestY = y;
//         int dx = 0, dy = 0;

//         // Recherche la meilleure direction
//         for (int ddx : {-1, 0, 1}) {
//             for (int ddy : {-1, 0, 1}) {
//                 if (abs(ddx) + abs(ddy) != 1) continue;
//                 int nx = x + ddx, ny = y + ddy;
//                 if (nx >= 0 && nx < m_largeur && ny >= 0 && ny < m_hauteur) {
//                     if (flow_field[ny][nx] != -1 && flow_field[ny][nx] < minDist && m_carte[ny][nx] != 1 && !reservee[ny][nx]) {
//                         minDist = flow_field[ny][nx];
//                         bestX = nx;
//                         bestY = ny;
//                         dx = ddx;
//                         dy = ddy;
//                     }
//                 }
//             }
//         }

//         // Déplacement fluide
//         m_positionEnnemisFloat[i].first += dx * vitesse * delta;
//         m_positionEnnemisFloat[i].second += dy * vitesse * delta;

//         int oldX = m_positionEnnemis[i].first;
//         int oldY = m_positionEnnemis[i].second;
//         int newX = int(m_positionEnnemisFloat[i].first + 0.5f);
//         int newY = int(m_positionEnnemisFloat[i].second + 0.5f);

//         if ((newX != oldX || newY != oldY) && newX >= 0 && newX < m_largeur && newY >= 0 && newY < m_hauteur) {
//             // Phase 1 : sauvegarde la case d'arrivée
//             int caseArrivee = m_carte[newY][newX];

//             // Phase 2 : remet la case quittée à sa valeur d'origine
//             m_carte[oldY][oldX] = m_casesSousEnnemis[i];

//             // Phase 3 : place l'ennemi sur la nouvelle case
//             m_casesSousEnnemis[i] = caseArrivee;
//             m_carte[newY][newX] = 4;
//             m_positionEnnemis[i] = {newX, newY};
//             reservee[newY][newX] = true;

//             // Si le joueur est touché
//             if (newX == m_positionJoueur.first && newY == m_positionJoueur.second) {
//                 joueur.vie--;
//                 std::cout << "Le joueur est attaqué par un ennemi !" << std::endl;
//             }
//         }
//     }
// }


std::vector<std::vector<int>> MapGenerator::generer_le_flow_field() {
    auto& pos = m_positionJoueur;
    int joueurX = pos.first;
    int joueurY = pos.second;
    int largeur = this->getLargeur();
    int hauteur = this->getHauteur();
    auto& carte = this->getCarte();

    std::vector<std::vector<int>> distance(hauteur, std::vector<int>(largeur, -1));
    std::queue<std::pair<int, int>> q;
    q.push({joueurX, joueurY});
    distance[joueurY][joueurX] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int dx : {-1, 0, 1}) {
            for (int dy : {-1, 0, 1}) {
                if (abs(dx) + abs(dy) != 1) continue; // 4 directions
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
                    if (carte[ny][nx] != 1 && distance[ny][nx] == -1) { // pas un mur
                        distance[ny][nx] = distance[y][x] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
    return distance;
}


