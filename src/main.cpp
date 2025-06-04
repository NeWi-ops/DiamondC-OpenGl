#include "MapGenerator.hpp"
#include "Joueur.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "lib/glbasimac/glfw/include/GLFW/glfw3.h"


// Fonction pour lire un caractère sans attendre Entrée / CA NE MARCHE QUE POUR MAC/LINUX
//Pour Windows, il faudrait utiliser _getch() de <conio.h>.
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {

// Set an error callback to display glfw errors
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "Error " << error << ": " << description << std::endl;
    });

    // Initialize glfw
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window { glfwCreateWindow(1280, 720, "Window", nullptr, nullptr) };
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Créer une carte de taille 50x50
    MapGenerator map(50, 50);

    // Générer la carte
    map.genererCarte();

    // Afficher la carte
    map.afficherCarte();

    // Créer un joueur
    Joueur J;

    std::cout << "Entrez une direction (z/s/q/d) ou 'a' pour quitter: ";

    
    while (true) {
        //std::cout << "Entrez une direction (z/s/q/d) ou 'a' pour quitter: ";
        //std::cin >> direction;

        char direction{getch()};
        if (direction == 'a' || J.finduJeu()==1 || J.finduJeu()==2) {break;}
        J.deplacer(direction,map);
        map.afficherCarte();
        // J.destruction(map);
        // map.afficherCarte();
    }

    while (!glfwWindowShouldClose(window)) {

        
    }
    glfwTerminate();
    
    return 0;
}


