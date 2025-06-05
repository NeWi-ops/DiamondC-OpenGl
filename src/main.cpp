#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
#include "Joueur.hpp"
// #include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "tools/texture.hpp"
#include "Draw.hpp"
#include "Deplacement.hpp"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
GLuint tex_accueil;
float joueur_x_case = 1.0f; // position en cases (float)
float joueur_y_case = 1.0f;
int joueur_case_x = 1; // position logique (int)
int joueur_case_y = 1;         
float vitesse = 3.0f; // cases par seconde

void drawFullScreenTexture(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1.0f,  1.0f);
        glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1, 0); glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(1, 1); glVertex2f( 1.0f,  1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

bool clicValide = false; // passe à true quand clic centre validé

// Callback souris
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Récupérer la position du clic en pixels (origine coin en haut à gauche)
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Définir zone centrale du clic (par ex 200x200 pixels centrés)
        double zoneXMin = WINDOW_WIDTH/2 - 100;
        double zoneXMax = WINDOW_WIDTH/2 + 100;
        double zoneYMin = WINDOW_HEIGHT/2 - 100;
        double zoneYMax = WINDOW_HEIGHT/2 + 100;

        // Inversion Y car GLFW donne Y depuis le haut
        // Mais on veut vérifier dans la fenêtre, donc c’est ok

        if (xpos >= zoneXMin && xpos <= zoneXMax && ypos >= zoneYMin && ypos <= zoneYMax)
        {
            clicValide = true;
            // Optionnel : désactiver ce callback ou fermer la fenêtre splash
        }
    }
}



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

    stbi_set_flip_vertically_on_load(1);// pour que les images soient orientées correctement


    //TEST ACCUEIL 

    GLuint tex_accueil = chargerTexture("../images/accueil/accueil.png");



    // Callback souris pour détecter clic central
glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(w, &xpos, &ypos);

        // Match exact avec la zone rouge OpenGL
        float offsetx = 0.31f;
        float offsety = 0.064f;

        double centerX = (offsetx + 1.0f) * (WINDOW_WIDTH / 2.0);
        double centerY = (offsety + 1.0f) * (WINDOW_HEIGHT / 2.0); 

        double zoneXMin = centerX - 150;
        double zoneXMax = centerX + 150;
        double zoneYMin = centerY - 140;
        double zoneYMax = centerY + 140;

        if (xpos >= zoneXMin && xpos <= zoneXMax && ypos >= zoneYMin && ypos <= zoneYMax) {
            clicValide = true;
        }
    }
});


    // Comme on ne peut pas modifier clicValide depuis le lambda simple ci-dessus (car variable locale),
    // je te propose une variable globale ou une autre approche (plus bas je te donne la version globale).

    // Ici la boucle d'attente clic sur accueil (affiche la texture accueil)
    while (!glfwWindowShouldClose(window) && !clicValide) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_accueil);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(-1,  1);
            glTexCoord2f(0, 0); glVertex2f(-1, -1);
            glTexCoord2f(1, 0); glVertex2f( 1, -1);
            glTexCoord2f(1, 1); glVertex2f( 1,  1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    GLuint tex_mur = chargerTexture("../images/mur/Burger1.png");
    GLuint tex_vide = chargerTexture("../images/vide/Sol2.png");
    GLuint tex_gemme = chargerTexture("../images/gemme/Scoobysnacks.png");
    GLuint tex_ennemi = chargerTexture("../images/ennemi/Fantome.png");
    GLuint tex_piege = chargerTexture("../images/piege/Trou.png");
    GLuint tex_joueur = chargerTexture("../images/joueur/ScoobydooDroite.png");

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
        //map.deplacerEnnemis(map.generer_le_flow_field(), J);

        // Gestion clavier (exemple simple, à adapter selon GLFW)
        //char direction = ; // À récupérer avec GLFW (voir plus bas)
        //if (direction == 'a' || J.finduJeu() == 1 || J.finduJeu() == 2) break;
        //J.deplacer(direction, map);


        
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float delta = float(currentTime - lastTime);
        lastTime = currentTime;

        ennemi_timer += delta;
        if (ennemi_timer >= ennemi_interval) {
            //map.deplacerEnnemis(map.generer_le_flow_field(), J, delta);
            map.deplacerEnnemis(map.generer_le_flow_field(), J);
            ennemi_timer = 0.0f;
        }


        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || J.finduJeu() == 2) break; 
        
        gererDeplacementJoueur(map , window, joueur_x_case, joueur_y_case, vitesse, delta);

        gererCollisionEtLogique(joueur_x_case,joueur_y_case,joueur_case_x, joueur_case_y, J, map, window);

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