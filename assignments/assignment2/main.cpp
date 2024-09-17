#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../core/bsilva/shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

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

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// linking vertex attributes
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO; // VBO stands for Vertex Buffer Object
	glGenBuffers(1, &VBO); // generic buffer

	// glNamedBufferData(VBO, sizeof(vertices, vertices, GL_STATIC_DRAW)   ---   equivalency to lines 39 and 40

	Shader ourShader("assets/shader.vert", "assets/shader.frag"); // creating shader object, with the type of vertex shader

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		GLfloat updateTime = glfwGetTime();

		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.5f * sin(updateTime) + 0.5f, 0.5f * sin(updateTime) + 0.5f, 0.5f * sin(updateTime) + 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clearing color buffer

		//Drawing happens here!
		// activate program
		ourShader.use();

		//update colors based on uniform time
		int timeLocation = glGetUniformLocation(ourShader.ID, "uniTime");
		glUniform1f(timeLocation, updateTime);

		//render the triangle
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // presenting to window
		glfwPollEvents();
	}
	printf("Shutting down...");
}
