#include "lib/glbasimac/glad/include/glad/glad.h"
#include "lib/img-main/include/img/img.hpp"


GLuint loadTexture(uint8_t const* data, int width, int height);


void draw_quad_with_texture(GLuint textureId);