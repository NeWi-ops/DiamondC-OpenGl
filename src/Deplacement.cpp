#include "Deplacement.hpp"
// #include <GLFW/glfw3.h>

void gererDeplacementJoueur(MapGenerator& map , GLFWwindow* window, float& joueur_x_case, float& joueur_y_case, float vitesse, float delta) {
    float dx = 0.0f, dy = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dy -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dy += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dx -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dx += 1.0f;

    float norme = sqrt(dx*dx + dy*dy);
    if (norme > 0.0f) {
        dx /= norme;
        dy /= norme;
        joueur_x_case += dx * vitesse * delta;
        joueur_y_case += dy * vitesse * delta;
    }

        // Empêche de sortir de la carte
    if (joueur_x_case < 0) joueur_x_case = 0;
    if (joueur_y_case < 0) joueur_y_case = 0;
    if (joueur_x_case > map.getLargeur()-1) joueur_x_case = map.getLargeur()-1;
    if (joueur_y_case > map.getHauteur()-1) joueur_y_case = map.getHauteur()-1;
}

void gererCollisionEtLogique(float& joueur_x_case, float& joueur_y_case, int& joueur_case_x, int& joueur_case_y, Joueur& J, MapGenerator& map) {
    int new_case_x = int(joueur_x_case + 0.5f);
    int new_case_y = int(joueur_y_case + 0.5f);

    // Pour les murs, on bloque strictement à la frontière
    int mur_x = int(joueur_x_case);
    int mur_y = int(joueur_y_case);

    if (new_case_x != joueur_case_x || new_case_y != joueur_case_y) {
        bool deplacement_ok = false;
        if (new_case_x > joueur_case_x) deplacement_ok = J.deplacer('d', map);
        else if (new_case_x < joueur_case_x) deplacement_ok = J.deplacer('q', map);
        else if (new_case_y > joueur_case_y) deplacement_ok = J.deplacer('s', map);
        else if (new_case_y < joueur_case_y) deplacement_ok = J.deplacer('z', map);

        if (deplacement_ok) {
            joueur_case_x = new_case_x;
            joueur_case_y = new_case_y;
        } else {
            // Si mur, bloque à la frontière stricte
            if (new_case_x > joueur_case_x) joueur_x_case = joueur_case_x + 0.99f;
            else if (new_case_x < joueur_case_x) joueur_x_case = joueur_case_x;
            if (new_case_y > joueur_case_y) joueur_y_case = joueur_case_y + 0.99f;
            else if (new_case_y < joueur_case_y) joueur_y_case = joueur_case_y;
        }
    }
}