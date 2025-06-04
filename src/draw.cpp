#include "draw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

            // Cases vides (blanc) ou murs (noir)
            // if (val == 1) glColor3f(0.0f, 0.0f, 0.0f); // mur noir
            // else glColor3f(1.0f, 1.0f, 1.0f); // vide blanc

            // glBegin(GL_QUADS);
            // glVertex2f(xpos, ypos);
            // glVertex2f(xpos + cellWidth, ypos);
            // glVertex2f(xpos + cellWidth, ypos + cellHeight);
            // glVertex2f(xpos, ypos + cellHeight);
            // glEnd();

            // // piège (petit carré bleu)
            // if (val == 2) {
            //     glColor3f(0.0f, 0.0f, 1.0f);
            //     float margin = 0.2f;
            //     glBegin(GL_QUADS);
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
            //     glEnd();
            // }

            // // Ennemi (petit carré rouge)
            // if (val == 4) {
            //     glColor3f(1.0f, 0.0f, 0.0f);
            //     float margin = 0.2f;
            //     glBegin(GL_QUADS);
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
            //     glEnd();
            // }
            // if (val == 3) { // Gemme (petit carré jaune)
            //     glColor3f(1.0f, 1.0f, 0.0f);
            //     float margin = 0.2f;
            //     glBegin(GL_QUADS);
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
            //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
            //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
            //     glEnd();
            // }
            if (val == 1) drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_mur);//mur
            else if (val == 2) { //piege
                float margin = 0.2;
                drawCaseTexture(xpos + cellWidth * margin,
                    ypos + cellHeight * margin,
                    cellWidth * (1 - 2 * margin),
                    cellHeight * (1 - 2 * margin),
                    tex_piege);
            }
            else if (val == 3) { //gemme
                float margin = 0.2;
                drawCaseTexture(xpos + cellWidth * margin,
                    ypos + cellHeight * margin,
                    cellWidth * (1 - 2 * margin),
                    cellHeight * (1 - 2 * margin),
                    tex_gemme);
            }
            else if (val == 4) { //ennemi
                float margin = 0.2;
                drawCaseTexture(xpos + cellWidth * margin,
                    ypos + cellHeight * margin,
                    cellWidth * (1 - 2 * margin),
                    cellHeight * (1 - 2 * margin),
                    tex_ennemi);
            }
            else drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_vide);//vide
        }
    }
}

void drawJoueur(float joueur_x, float joueur_y, float joueur_width, float joueur_height, GLuint tex_joueur) {
        drawCaseTexture(
            joueur_x - joueur_width / 2,
            joueur_y - joueur_height / 2,
            joueur_width,
            joueur_height,
            tex_joueur
        );
}