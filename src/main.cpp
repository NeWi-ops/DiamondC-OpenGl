#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
#include "Joueur.hpp"
// #include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "tools/texture.hpp"
#include "draw.hpp"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

float joueur_x_case = 1.0f; // position en cases (float)
float joueur_y_case = 1.0f;
int joueur_case_x = 1; // position logique (int)
int joueur_case_y = 1;         
float vitesse = 3.0f; // cases par seconde


int main() {
    if (!glfwInit()) return -1;

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // #ifdef __APPLE__
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // #endif

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Carte OpenGL", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    stbi_set_flip_vertically_on_load(1); // pour que les images soient orientées correctement

    GLuint tex_mur = chargerTexture("../images/mur/mur.png");
    GLuint tex_vide = chargerTexture("../images/vide/vide.png");
    GLuint tex_gemme = chargerTexture("../images/gemme/gemme.png");
    GLuint tex_ennemi = chargerTexture("../images/ennemi/ennemi.png");
    GLuint tex_piege = chargerTexture("../images/piege/piege.png");
    GLuint tex_joueur = chargerTexture("../images/joueur/joueur.png");

    Joueur J;

    // float joueur_x = 0.0f; // centre horizontal (de -1 à 1)
    // float joueur_y = 0.0f; // centre vertical (de -1 à 1)

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // fond blanc
    MapGenerator map(30, 30); // plus petit pour la démo graphique
    map.genererCarte();
    

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCarte(map, tex_mur, tex_vide, tex_gemme, tex_ennemi, tex_piege);
        // Déplacement des ennemis (comme en console)
        //map.deplacerEnnemis(map.generer_le_flow_field(), J);

        // Gestion clavier (exemple simple, à adapter selon GLFW)
        //char direction = ; // À récupérer avec GLFW (voir plus bas)
        //if (direction == 'a' || J.finduJeu() == 1 || J.finduJeu() == 2) break;
        //J.deplacer(direction, map);


        
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float delta = float(currentTime - lastTime);
        lastTime = currentTime;

        // Gestion clavier fluide
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)    joueur_y_case -= vitesse * delta;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)  joueur_y_case += vitesse * delta;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)  joueur_x_case -= vitesse * delta;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) joueur_x_case += vitesse * delta;

        // Empêche de sortir de la carte
        if (joueur_x_case < 0) joueur_x_case = 0;
        if (joueur_y_case < 0) joueur_y_case = 0;
        if (joueur_x_case > map.getLargeur()-1) joueur_x_case = map.getLargeur()-1;
        if (joueur_y_case > map.getHauteur()-1) joueur_y_case = map.getHauteur()-1;
        

        auto& pos = map.getPositionJoueur();
        joueur_case_x = pos.first;
        joueur_case_y = pos.second;

        int new_case_x = int(joueur_x_case + 0.5f);
        int new_case_y = int(joueur_y_case + 0.5f);
         // Conversion en coordonnées OpenGL
        // float cellWidth = 2.0f / map.getLargeur();
        // float cellHeight = 2.0f / map.getHauteur();
        // float joueur_x = -1.0f + (joueur_case_x + 0.5f) * cellWidth;
        // float joueur_y = -1.0f + (joueur_case_y + 0.5f) * cellHeight;
        // float joueur_width = cellWidth * 0.6f;
        // float joueur_height = cellHeight * 0.6f;



        // Conversion en coordonnées OpenGL
        float cellWidth = 2.0f / map.getLargeur();
        float cellHeight = 2.0f / map.getHauteur();
        float joueur_x = -1.0f + (joueur_x_case + 0.5f) * cellWidth;
        float joueur_y = -1.0f + (joueur_y_case + 0.5f) * cellHeight;
        float joueur_width = cellWidth * 0.6f;
        float joueur_height = cellHeight * 0.6f;

        drawCaseTexture(
            joueur_x - joueur_width / 2,
            joueur_y - joueur_height / 2,
            joueur_width,
            joueur_height,
            tex_joueur
        );
        // // float joueur_width = 2.0f / map.getLargeur() * 0.6f;
        // // float joueur_height = 2.0f / map.getHauteur() * 0.6f;
        // drawCaseTexture(
        //     joueur_x - joueur_width / 2,
        //     joueur_y - joueur_height / 2,
        //     joueur_width,
        //     joueur_height,
        //     tex_joueur
        // );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfwDestroyWindow(window);
    // glfwTerminate();
    return 0;
}