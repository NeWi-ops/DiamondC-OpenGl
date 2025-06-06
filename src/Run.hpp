#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
#include "Joueur.hpp"
#include "draw.hpp"
#include "Deplacement.hpp"

void runGame(GLFWwindow* window, MapGenerator& map, Joueur& J, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege, GLuint tex_joueur, GLuint tex_victoire, GLuint tex_defaite, GLuint tex_accueil);