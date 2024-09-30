#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../ew/external/glad.h"
#include "../ew/external/stb_image.h"
#include "../ew/ewMath/ewMath.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture2D {
public:
    unsigned int ID; 
    int width, height, nrChannels;

    // loading texture
    Texture2D(const std::string& path);

    // binding texture
    void bind(int textureNum) const;
};

#endif