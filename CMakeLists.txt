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

include(FetchContent)

# ---Add libraries---

# ---GLFW---
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    # Disable some stuff we don't need
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# ---glad---
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    # Set some options for glad
    set(GLAD_PROFILE "compatibility" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glad)

## ---glm---
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
)

FetchContent_MakeAvailable(glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# ---img---
FetchContent_Declare(
    img
    GIT_REPOSITORY https://github.com/CoolLibs/img
    GIT_TAG da961a78b622db4f4b26df690b38ac3054e61806
)

FetchContent_MakeAvailable(img)
target_link_libraries(${PROJECT_NAME} PRIVATE img::img)

# ---simpleText--- (fork from https://github.com/podgorskiy/SimpleText)
# Optional library for rendering text
FetchContent_Declare(
    simpletext
    GIT_REPOSITORY https://github.com/dsmtE/SimpleText/
)

FetchContent_MakeAvailable(simpletext)

# Create an interface library for simpletext
add_library(simpletext INTERFACE)
target_include_directories(simpletext SYSTEM INTERFACE ${simpletext_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE simpletext)