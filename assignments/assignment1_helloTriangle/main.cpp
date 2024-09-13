#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "assets/shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

float vertices[] =
{
   -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
	0.0f,  0.3661f, 0.0f,  0.0f, 0.0f, 1.0f // bottom right
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

	Shader ourShader("assets/shader.vs", "assets/shader.fs"); // creating shader object, with the type of vertex shader

	// shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// linking vertex attributes

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// copy over from vertices array into a buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set the vertex attributes pointers

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window); // presenting to window
		glfwPollEvents();
	}
	printf("Shutting down...");
}
