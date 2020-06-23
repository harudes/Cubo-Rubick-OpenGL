#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "Cube.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

glm::mat4 projection;
glm::mat4 modelview;

glm::vec3 cameraCenter(0, 0, 0);
glm::vec3 cameraUp(0, 0, 1);
glm::vec3 cameraEye(0, -2, 0);

GLuint projectionPos;
GLuint modelviewPos;

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;"
"out vec3 Color;"
"uniform mat4 modelview;"
"uniform mat4 projection;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0f);\n"
"	Color = aColor;"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 Color;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(Color, 1.0f);\n"
"}\n\0";

int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Basic OpenGL Program", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);;
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint shaderProgram = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);



	projectionPos = glGetUniformLocation(shaderProgram, "projection");
	modelviewPos = glGetUniformLocation(shaderProgram, "modelview");
	projection = glm::mat4(1.0f);
	modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
	framebuffer_size_callback(window, 500, 500);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

	//El primer parametro es un vec3, el centro del cubo
	//El segundo parametro es un GLfloat, la longitud de las aristas
	//El tercer parametro es un vector de 6 vec3, que representan los colores de cada cara, tengo algunos defines con los colores del cubo
	//El cuarto parametro es el programa, por si en algun momento usamos diferentes shaders
	Cube testCube(glm::vec3(0.55, 0.0, 0.0), 0.5, { ORANGE,WHITE,RED,GREEN,BLUE,YELLOW },shaderProgram);
	Cube testCube2(glm::vec3(0.0, 0.0, 0.0), 0.5, { ORANGE,WHITE,RED,GREEN,BLUE,YELLOW }, shaderProgram);
	Cube testCube3(glm::vec3(-0.55, 0.0, 0.0), 0.5, { ORANGE,WHITE,RED,GREEN,BLUE,YELLOW }, shaderProgram);
	//Cube testCube(vertices, colors, indices, shaderProgram);
	

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		processInput(window);
		testCube.draw();
		testCube2.draw();
		testCube3.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// Think about the rationale for this choice
	// What would happen if you changed near and far planes? 
	// Note that the field of view takes in a radian angle!

	if (h > 0)
	{
		projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
		
		glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}