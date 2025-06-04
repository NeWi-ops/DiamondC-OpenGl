cmake_minimum_required(VERSION 3.10)

project("Le Jeu")


set(CMAKE_CXX_STANDARD 11)


# Inclut les répertoires de fichiers source
include_directories(src)

# Liste des fichiers sources
set(SOURCES_COMMON
    
    src/MapGenerator.cpp
    src/Joueur.cpp
    src/draw.cpp
    # Ajouter d'autres fichiers source nécessaires
)

# Crée l'exécutable du projet
#add_executable("main.cpp" ${SOURCES})
# Version console
add_executable(jeu_console src/main_console.cpp ${SOURCES_COMMON})

# Version OpenGL
add_executable(jeu_opengl src/main.cpp ${SOURCES_COMMON})


# Set the folder where the executable will be created
set(OUTPUT_BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Librairies

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(third_party)
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad third_party/glad/src/glad.c)
include_directories(third_party/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)

# ---Add glbasimac---
add_subdirectory(third_party/glbasimac)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glbasimac)
include_directories(third_party/glbasimac/)
set(CMAKE_COLOR_MAKEFILE ON)

file(GLOB TD_DIRECTORIES "TD*")

foreach(TD ${TD_DIRECTORIES})
    add_subdirectory(${TD})
	get_filename_component(DIRN ${TD} NAME)
    add_custom_target(${DIRN} COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/${DIRN} COMMAND make
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${DIRN})
endforeach()

target_link_libraries(jeu_opengl ${ALL_LIBRARIES})