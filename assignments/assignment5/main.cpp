#include <stdio.h>
#include <math.h>

#include <ew/external/stb_image.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/bsilva/shader.h"
#include "../core/bsilva/texture2D.h"
#include "../core/bsilva/camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

// lighting cube pos
glm::vec3 lightPos(0.0f, 0.0f, -10.0f);

float vertices[] = {
	// x      y      z     nx     ny     nz     u      v
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};
glm::vec3 cubePositions[] = {
	glm::vec3(4.0f,  -4.0f, -18.0f),
	glm::vec3(-4.0f, -4.0f, -16.0f),
	glm::vec3(-4.0f,  4.0f, -10.0f),
	glm::vec3(4.0f, 4.0f, -8.0f),
	glm::vec3(4.0f,  -4.0f, -6.0f),
	glm::vec3(-4.0f,  -4.0f, -4.0f),
	glm::vec3(8.0f,  -8.0f, -18.0f),
	glm::vec3(-8.0f, -8.0f, -16.0f),
	glm::vec3(-8.0f,  8.0f, -10.0f),
	glm::vec3(8.0f, 8.0f, -8.0f),
	glm::vec3(8.0f,  -8.0f, -6.0f),
	glm::vec3(-8.0f,  -8.0f, -4.0f),
	glm::vec3(12.0f,  -12.0f, -18.0f),
	glm::vec3(-12.0f, -12.0f, -16.0f),
	glm::vec3(-12.0f,  12.0f, -10.0f),
	glm::vec3(12.0f, 12.0f, -8.0f),
	glm::vec3(12.0f,  -12.0f, -6.0f),
	glm::vec3(-12.0f,  -12.0f, -4.0f),
	glm::vec3(0.0f, 0.0f, -2.0f),
	glm::vec3(0.0f, 0.0f, -20.0f)
};

float cubeScales[] = {(rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f,
					  (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f,
					  (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f,
					  (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f, (rand() % 10 + 3) / 10.0f,
};

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
bool perspective = true;

double deltaTime = 0.0f;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Field of Cubes", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// enabling alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// enabling depth testing
	glEnable(GL_DEPTH_TEST);

	// for non light cube cubes -------------------------------------
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// for light cube -------------------------------------------------
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader cubeShader("assets/shader.vert", "assets/shader.frag");
	Shader lightShader("assets/lighting.vert", "assets/lighting.frag");

	Texture2D diamBlock("assets/diamond_block.png");

	cubeShader.use();
	cubeShader.setInt("texture1", 0);
	cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	cubeShader.setVec3("lightPos", lightPos);

	double timeSinceStart = glfwGetTime();
	double lastFrame = 0.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

	//Render loop
	while (!glfwWindowShouldClose(window)) 
	{
		GLfloat updateTime = glfwGetTime();
		
		double currentTime = glfwGetTime();
		double deltaTimeTotal = currentTime - timeSinceStart;
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		processInput(window);
	
		//Clear framebuffer
		glClearColor(0.375f, 0.45f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clearing color buffer

		// activate shader
		cubeShader.use();
		diamBlock.bind(0);

		// picking projection matrix to send to shader
		if (perspective)
		{
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		}
		else if (!perspective)
		{
			projection = glm::ortho(-SCREEN_WIDTH / 300.0f, SCREEN_WIDTH / 300.0f, -SCREEN_HEIGHT / 300.0f, SCREEN_HEIGHT / 300.0f, 0.1f, 1000.0f);
		}
		cubeShader.setMat4("projection", projection);

		// camera
		glm::mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("view", view);

		//render container
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z));
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::scale(model, glm::vec3(cubeScales[i], cubeScales[i], cubeScales[i]));
			cubeShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// light cube drawing
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);

		//glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window); // presenting to window
		glfwPollEvents();
	}

	printf("Shutting down...");
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = static_cast<float>(2.5f * deltaTime);
	// sprint
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(SPRINT, deltaTime);
	// normal movements
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	// up and down
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	// perspective change // O for orthographic, P for perspective
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		perspective = false;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		perspective = true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
