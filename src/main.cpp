#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
#include "Joueur.hpp"
// #include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "tools/texture.hpp"
#include "draw.hpp"
#include "Deplacement.hpp"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;




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

    auto& pos = map.getPositionJoueur();
    int joueur_case_x = pos.first;
    int joueur_case_y = pos.second; 
    float joueur_x_case = static_cast<float> (joueur_case_x); // position en cases (float)
    float joueur_y_case = static_cast<float> (joueur_case_y);
    float vitesse = 3.0f; // cases par seconde
    float ennemi_timer = 0.0f;
    float ennemi_interval = 0.5f; // les ennemis bougent toutes les 0.5 secondes (ajuste à ta convenance)

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCarte(map, tex_mur, tex_vide, tex_gemme, tex_ennemi, tex_piege);
        // Déplacement des ennemis (comme en console)
        // map.deplacerEnnemis(map.generer_le_flow_field(), J);

        
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float delta = float(currentTime - lastTime);
        lastTime = currentTime;

        ennemi_timer += delta;
        if (ennemi_timer >= ennemi_interval) {
            map.deplacerEnnemis(map.generer_le_flow_field(), J);
            ennemi_timer = 0.0f;
        }


        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || J.finduJeu() == 2) break; 
        
        gererDeplacementJoueur(map , window, joueur_x_case, joueur_y_case, vitesse, delta);

        gererCollisionEtLogique(joueur_x_case,joueur_y_case,joueur_case_x, joueur_case_y, J, map);

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

        drawJoueur(joueur_x, joueur_y, joueur_width, joueur_height, tex_joueur);


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