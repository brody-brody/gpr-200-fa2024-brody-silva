#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] =
{
   -0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
}; // gpu will read this as 9 floats

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!
	unsigned int VBO; // VBO stands for Vertex Buffer Object
	glGenBuffers(1, &VBO); // generic buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // define what type of buffer by whatever is bound to gl array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// glNamedBufferData(VBO, sizeof(vertices, vertices, GL_STATIC_DRAW)   ---   equivalency to lines 39 and 40

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0"; // holding source code for vertex shader and storing it in a const char

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // creating shader object, with the type of vertex shader

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // supplying the source code to the newly created shader object
	glCompileShader(vertexShader); // compiling shader code

	// compile shader will not let you know if it has worked or not, so it is good to implement a check function
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // grabbing compilation status of most recently compiled shader, with a reference to a variable

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}



	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.75f, 0.5f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clearing color buffer
		//Drawing happens here!
		glfwSwapBuffers(window); // presenting to window
	}
	printf("Shutting down...");
}
