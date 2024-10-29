#ifndef SHADER_H
#define SHADER_H

#include "../ew/external/glad.h"
#include "../ew/ewMath/ewMath.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const;
    void Shader::setVec3(const std::string& name, const glm::vec3& value) const;
    void Shader::setVec3(const std::string& name, float x, float y, float z) const;
};

#endif