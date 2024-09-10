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
   -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f // bottom right
}; // gpu will read this as 9 floats

const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"uniform float time;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0"; 
// holding source code for vertex shader and storing it in a const char

const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		in vec3 ourColor;

		void main()
		{
			FragColor = vec4(ourColor, 1.0);;
		}
		)";

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
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
	}
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
	}

	// shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); 
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); // after youve created and assigned the shaders to the program, you can delete the shaders

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


	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.75f, 0.5f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clearing color buffer

		//Drawing happens here!
		// activate program
		glUseProgram(shaderProgram);

		//update colors based on uniform time
		int vertexTimeLocation = glGetUniformLocation(shaderProgram, "time");

		//render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window); // presenting to window
		glfwPollEvents();
	}
	printf("Shutting down...");
}
