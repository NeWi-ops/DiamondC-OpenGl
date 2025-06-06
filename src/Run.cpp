#include "Run.hpp"
#include "glbasimac/tools/stb_image.h"



void runGame(GLFWwindow* window, MapGenerator& map, Joueur& J, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege, GLuint tex_joueur, GLuint tex_victoire, GLuint tex_defaite, GLuint tex_accueil) {
 
    auto& pos = map.getPositionJoueur();
    int joueur_case_x = pos.first;
    int joueur_case_y = pos.second; 
    float joueur_x_case_f = static_cast<float> (joueur_case_x); // position en cases (float)
    float joueur_y_case_f = static_cast<float> (joueur_case_y);
    float vitesse = 2.5f; // cases par seconde
    float ennemi_timer = 0.0f;
    float ennemi_interval = 0.5f; // les ennemis bougent toutes les 0.5 secondes (ajuste à ta convenance)

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCarte(map, tex_mur, tex_vide, tex_gemme, tex_ennemi, tex_piege);
        // Déplacement des ennemis (comme en console)
        //map.deplacerEnnemis(map.generer_le_flow_field(), J);


        
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

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) break;
        if (J.finduJeu() == 2) {
            if (afficherEcranFin(window, tex_victoire) == 1) {afficherAccueil(window, tex_accueil);}
                
            else break;
        }
        if (J.finduJeu() == 1) {
            if (afficherEcranFin(window, tex_victoire) == 1) {afficherAccueil(window, tex_accueil);}
                
            else break;
        }
        
        gererDeplacementJoueur(map , window, joueur_x_case_f, joueur_y_case_f, vitesse, delta);

        gererCollisionEtLogique(joueur_x_case_f,joueur_y_case_f,joueur_case_x, joueur_case_y, J, map, window);


        // Conversion en coordonnées OpenGL
        float cellWidth = 2.0f / map.getLargeur();
        float cellHeight = 2.0f / map.getHauteur();
        float joueur_x = -1.0f + (joueur_x_case_f + 0.5f) * cellWidth;
        float joueur_y = -1.0f + (joueur_y_case_f + 0.5f) * cellHeight;
        float joueur_width = cellWidth * 0.6f;
        float joueur_height = cellHeight * 0.6f;

        drawJoueur(joueur_x, joueur_y, joueur_width, joueur_height, tex_joueur);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}