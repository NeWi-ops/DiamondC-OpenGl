#pragma once
#include "MapGenerator.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include "Joueur.hpp"



void gererDeplacementJoueur(MapGenerator& map, GLFWwindow* window, float& joueur_x_case, float& joueur_y_case, float vitesse, float delta);
void gererCollisionEtLogique(float& joueur_x_case, float& joueur_y_case, int& joueur_case_x, int& joueur_case_y, Joueur& J, MapGenerator& map);