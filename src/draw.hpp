#pragma once
#include "MapGenerator.hpp"
#include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Joueur.hpp"


GLuint chargerTexture(const char* filename);
void drawCaseTexture(float xpos, float ypos, float cellWidth, float cellHeight, GLuint texture);
void drawCarte(const MapGenerator& map, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege);
void drawJoueur(float joueur_x, float joueur_y, float joueur_width, float joueur_height, GLuint tex_joueur);

bool verifierChangementCase(float joueur_x_case, float joueur_y_case, int& case_x, int& case_y, const MapGenerator& map);

