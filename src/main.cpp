#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MapGenerator.hpp"
// #include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "tools/texture.hpp"
#include "draw.hpp"


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

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // fond blanc
    MapGenerator map(30, 30); // plus petit pour la démo graphique
    map.genererCarte();
    

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCarte(map, tex_mur, tex_vide, tex_gemme, tex_ennemi, tex_piege);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}