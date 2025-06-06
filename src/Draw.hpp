#pragma once
#include "MapGenerator.hpp"
#include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "glbasimac/tools/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Joueur.hpp"


GLuint chargerTexture(const char* filename);
void drawFullScreenTexture(GLuint texture);
void drawCaseTexture(float xpos, float ypos, float cellWidth, float cellHeight, GLuint texture);
extern bool clicValide;
void afficherAccueil(GLFWwindow* window, GLuint tex_accueil);
int afficherEcranFin(GLFWwindow* window, GLuint texture_fin);
void drawCarte(const MapGenerator& map, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege);
void drawJoueur(float joueur_x, float joueur_y, float joueur_width, float joueur_height, GLuint tex_joueur);


