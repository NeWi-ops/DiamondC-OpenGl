// #include "Enemis.hpp"
// #include <iostream>
// #include "MapGenerator.hpp"
// #include "Joueur.hpp"
// #include <vector>


// Enemis::Enemis(int x, int y) {}

// std::vector<std::vector<int>> generer_le_flow_field(MapGenerator& map, Joueur& J) {
//     auto& pos = map.getPositionJoueur();
//     int joueurX = pos.first;
//     int joueurY = pos.second;
//     int largeur = map.getLargeur();
//     int hauteur = map.getHauteur();
//     auto& carte = map.getCarte();

//     std::vector<std::vector<int>> distance(hauteur, std::vector<int>(largeur, -1));
//     std::queue<std::pair<int, int>> q;
//     q.push({joueurX, joueurY});
//     distance[joueurY][joueurX] = 0;

//     while (!q.empty()) {
//         auto [x, y] = q.front(); q.pop();
//         for (int dx : {-1, 0, 1}) {
//             for (int dy : {-1, 0, 1}) {
//                 if (abs(dx) + abs(dy) != 1) continue; // 4 directions
//                 int nx = x + dx, ny = y + dy;
//                 if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
//                     if (carte[ny][nx] != 1 && distance[ny][nx] == -1) { // pas un mur
//                         distance[ny][nx] = distance[y][x] + 1;
//                         q.push({nx, ny});
//                     }
//                 }
//             }
//         }
//     }
//     return distance;
// }

// // void Enemis::attaque(MapGenerator& map, const std::vector<std::vector<int>>& flow_field) {
// //     auto& pos = map.getPositionEnnemis();
// //     int x = pos[0].first; // Position de l'ennemi
// //     int y = pos[0].second; // Position de l'ennemi
// //     int minDist = flow_field[y][x];
// //     int bestX = x, bestY = y;
// //     for (int dx : {-1, 0, 1}) {
// //         for (int dy : {-1, 0, 1}) {
// //             if (abs(dx) + abs(dy) != 1) continue;
// //             int nx = x + dx, ny = y + dy;
// //             if (nx >= 0 && nx < map.getLargeur() && ny >= 0 && ny < map.getHauteur()) {
// //                 if (flow_field[ny][nx] != -1 && flow_field[ny][nx] < minDist) {
// //                     minDist = flow_field[ny][nx];
// //                     bestX = nx;
// //                     bestY = ny;
// //                 }
// //             }
// //         }
// //     }
// //     // Déplace l'ennemi
// //     x = bestX;
// //     y = bestY;
// // }
