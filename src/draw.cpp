#include "draw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "glbasimac/tools/stb_image.h"


// Charge une image et crée une texture OpenGL
GLuint chargerTexture(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data) {
        std::cerr << "Erreur chargement image : " << filename << std::endl;
        return 0;
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    return texture;
}

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

void drawCaseTexture(float xpos, float ypos, float cellWidth, float cellHeight, GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1,1,1); // pour ne pas teinter la texture
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex2f(xpos, ypos);
    glTexCoord2f(1,0); glVertex2f(xpos + cellWidth, ypos);
    glTexCoord2f(1,1); glVertex2f(xpos + cellWidth, ypos + cellHeight);
    glTexCoord2f(0,1); glVertex2f(xpos, ypos + cellHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void afficherAccueil(GLFWwindow* window, GLuint tex_accueil) {
    clicValide = false;
    while (!glfwWindowShouldClose(window) && !clicValide) {
        // glClear(GL_COLOR_BUFFER_BIT);

        // glEnable(GL_TEXTURE_2D);
        // glBindTexture(GL_TEXTURE_2D, tex_accueil);
        // glBegin(GL_QUADS);
        //     glTexCoord2f(0, 1); glVertex2f(-1,  1);
        //     glTexCoord2f(0, 0); glVertex2f(-1, -1);
        //     glTexCoord2f(1, 0); glVertex2f( 1, -1);
        //     glTexCoord2f(1, 1); glVertex2f( 1,  1);
        // glEnd();
        // glDisable(GL_TEXTURE_2D);
        drawFullScreenTexture(tex_accueil);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void afficherEcranFin(GLFWwindow* window, GLuint texture_fin) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawFullScreenTexture(texture_fin);
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Appuyer sur Espace ou Entrée pour relancer ou revenir à l'accueil
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            break;
        }
        // Quitter si clic gauche souris
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            break;
        }
    }
}

void drawCarte(const MapGenerator& map, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege) {
    auto& carte = map.getCarte();
    int largeur = map.getLargeur();
    int hauteur = map.getHauteur();

    

    float cellWidth = 2.0f / largeur;
    float cellHeight = 2.0f / hauteur;

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int val = carte[y][x];

            float xpos = -1.0f + x * cellWidth;
            float ypos = -1.0f + y * cellHeight;

            
            if (val == 1) drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_mur);//mur
            else if (val == 2) { //piege
                float scale = 1.0f;
                float offsetX = (cellWidth * scale - cellWidth) / 2.0f;
                float offsetY = (cellHeight * scale - cellHeight) / 2.0f;
                drawCaseTexture(xpos + cellWidth * scale,
                    ypos + cellHeight * scale,
                    cellWidth * (1 - 2 * scale),
                    cellHeight * (1 - 2 * scale),
                    tex_piege);
            }
            else if (val == 3) { // gemme
                float scale = 1.0f;
                float offsetX = (cellWidth * scale - cellWidth) / 2.0f;
                float offsetY = (cellHeight * scale - cellHeight) / 2.0f;
                drawCaseTexture(xpos - offsetX,
                    ypos - offsetY,
                    cellWidth * scale,
                    cellHeight * scale,
                    tex_gemme);
            }
            else if (val == 4) { // ennemi
                float scale = 1.0f;
                float offsetX = (cellWidth * scale - cellWidth) / 2.0f;
                float offsetY = (cellHeight * scale - cellHeight) / 2.0f;
                drawCaseTexture(xpos - offsetX,
                    ypos - offsetY,
                    cellWidth * scale,
                    cellHeight * scale,
                    tex_ennemi);
            }
            else drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_vide);//vide
        }
    }
}

void drawJoueur(float joueur_x, float joueur_y, float joueur_width, float joueur_height, GLuint tex_joueur) {
    float scale = 1.5f;
    float w = joueur_width * scale;
    float h = joueur_height * scale;
    drawCaseTexture(
        joueur_x - w / 2,
        joueur_y - h / 2,
        w,
        h,
        tex_joueur
);
}

