cmake_minimum_required(VERSION 3.10)

project("Le Jeu")


set(CMAKE_CXX_STANDARD 11)


# Inclut les répertoires de fichiers source
include_directories(src)

# Liste des fichiers sources
set(SOURCES
    src/main.cpp
    src/MapGenerator.cpp
    src/Joueur.cpp
    # Ajouter d'autres fichiers source nécessaires
)

# Crée l'exécutable du projet
add_executable("main.cpp" ${SOURCES})