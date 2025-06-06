#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
#include "glbasimac/tools/stb_image.h"
#include "draw.hpp"
#include "Run.hpp"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


bool clicValide = false; // passe à true quand clic centre validé



int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Carte OpenGL", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    stbi_set_flip_vertically_on_load(1);// pour que les images soient orientées correctement

    GLuint tex_accueil = chargerTexture("../images/accueil/accueil.png");
    GLuint tex_mur = chargerTexture("../images/mur/Burger1.png");
    GLuint tex_vide = chargerTexture("../images/vide/Sol2.png");
    GLuint tex_gemme = chargerTexture("../images/gemme/Scoobysnacks.png");
    GLuint tex_ennemi = chargerTexture("../images/ennemi/Fantome.png");
    GLuint tex_piege = chargerTexture("../images/piege/Trou.png");
    GLuint tex_joueur = chargerTexture("../images/joueur/ScoobydooDroite.png");
    GLuint tex_victoire = chargerTexture("../images/fin/victoire.png");
    GLuint tex_defaite = chargerTexture("../images/fin/defaite.png");

    Joueur J;


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


    
    // Ici la boucle d'attente clic sur accueil (affiche la texture accueil)
    afficherAccueil(window, tex_accueil);



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // fond blanc
    MapGenerator map(30, 30); // Largeur et hauteur de la carte en cases
    map.genererCarte();

    runGame(window, map, J, tex_mur, tex_vide, tex_gemme, tex_ennemi, tex_piege, tex_joueur, tex_victoire, tex_defaite, tex_accueil);
    
    return 0;
}
    
