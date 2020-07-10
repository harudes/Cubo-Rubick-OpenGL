#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "RubickCube.h"
#include "AKube.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//~~~~~~~~~~~~~~~~ GLOBAL VARIABLES OF THE RUBICK'S CUBE~~~~~~~~~~~~~~~~~~
GLfloat centerX = 0.0f,
centerY = 0.0f,
centerZ = 0.0f;
GLfloat arista = 0.5; //tamaño de la arista de los cubitos
GLfloat offset = 0.05;//tamaño de la distancia entre cubos
GLuint shader;
RubickCube* cuboRubick;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



glm::mat4 projection;
glm::mat4 modelview;

glm::vec3 cameraCenter(0, 0, 0);
/*
glm::vec3 cameraUp(0, 1, -1);
glm::vec3 cameraEye(0, 2, 2);
*/

glm::vec3 cameraUp(0, 0, 1);
glm::vec3 cameraEye(5, 0, 0);

GLuint projectionPos;
GLuint modelviewPos;

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 Color;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(position, 1.0f);\n"
"	Color = color;\n"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 Color;\n"
"in vec2 TexCoord;\n"
"out vec4 fragColor;\n"
"uniform sampler2D texture1;\n"
"void main(void)\n"
"{\n"
"   fragColor = texture(texture1, TexCoord) * vec4(Color, 1.0f);\n"
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
	glfwSetScrollCallback(window, scroll_callback);

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
	GLint linked;
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked) {
		glUseProgram(shaderProgram);
		std::cout << "Success\n";
	}
	else {
		std::cout << "Error\n";
	}

	glUseProgram(shaderProgram);

	projectionPos = glGetUniformLocation(shaderProgram, "projection");
	modelviewPos = glGetUniformLocation(shaderProgram, "view");
	modelview = glm::lookAt(cameraEye,cameraCenter,cameraUp);
	projection = glm::mat4(1.0f);
	framebuffer_size_callback(window, 500, 500);
	glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);


	//~~~~~~~~~~~~~~~~ CREATE THE TEXTURE ~~~~~~~~~~~~~~~~~~~~~~~

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("C://Users//luisf//Pictures//CuboRubik.png", &width, &height, &nrChannels, 0);
	//unsigned char *data = stbi_load("C://Users//luisf//Pictures//base UCSP.png", &width, &height, &nrChannels, 0);
	//unsigned char *data = stbi_load("C://Users//luisf//Pictures//ov6ds6za7s951.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	

	//~~~~~~~~~~~~~~~~ CREATE THE RUBICK'S CUBE~~~~~~~~~~~~~~~~~~	
	shader = shaderProgram;
	
	cuboRubick = new RubickCube(glm::vec3(centerX,centerY,centerZ), arista, offset, shader, texture);
	cuboRubick->generateCube();
	
	/*string randomCube = randomize();

	cout << randomCube << endl;*/

	glEnable(GL_DEPTH_TEST);

	float time;
	glfwSetTime(0);
	float frameRate = 1.0f / 60.0f;

	while (!glfwWindowShouldClose(window))
	{	
		time = glfwGetTime();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (time > frameRate) {
			cuboRubick->movement();
			glfwSetTime(0);
		}
		
		cuboRubick->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
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
		//projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
		projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);

		glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glm::mat4 rotation = glm::mat4(1.0f);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>()/12, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rotation = glm::rotate(glm::mat4(1.0f), -glm::pi<float>() / 12, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (abs(cameraEye.x) < 0.00001f) {
			rotation = glm::rotate(glm::mat4(1.0f), -glm::pi<float>() / 12, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (abs(cameraEye.y) < 0.00001f){
			rotation = glm::rotate(glm::mat4(1.0f), -glm::pi<float>() / 12, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (abs(cameraEye.x) < 0.0001f) {
			rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() / 12, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (abs(cameraEye.y) < 0.0001f) {
			rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() / 12, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (offset < 0.1) offset = 0.2;
		else offset = 0.05;
		cuboRubick->setOffset(offset);
		cuboRubick->generateCube();
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		cuboRubick->restartCube();
		cuboRubick->generateCube();
		cameraUp = glm::vec3(0, 0, 1);
		cameraEye = glm::vec3(5, 0, 0);
		modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
		glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		//~~~~~~~~~~~~~~~~ OBTAINING RUBBICKS DISORDERED ~~~~~~~~~~~~~~~~~~	
		std::string data = GetData();
		std::string cubo = get_cubo(data);
		std::vector<std::string> solution = get_solution(data);
		cuboRubick->setColors(cubo);
		cuboRubick->generateCube();
		cuboRubick->Solve(solution);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cuboRubick->setAnimation("R");
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cuboRubick->setAnimation("L");
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cuboRubick->setAnimation("U");
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cuboRubick->setAnimation("D");
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		cuboRubick->setAnimation("F");
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		cuboRubick->setAnimation("B");
	}

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		cuboRubick->expand(0.1f);
	}

	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		cuboRubick->expand(-0.1f);
	}

	cameraEye = glm::mat3(rotation) * cameraEye;
	cameraUp = glm::mat3(rotation) * cameraUp;

	modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	glm::vec3 direction = cameraCenter - cameraEye;
	GLfloat normal = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	direction.x /= normal * 3;
	direction.y /= normal * 3;
	direction.z /= normal * 3;
	if (yoffset > 0) {
		if (abs(cameraEye.x) > 0.5 || abs(cameraEye.y) > 0.5 || abs(cameraEye.z) > 0.5)
		cameraEye += direction;
	}
	else {
		if (abs(cameraEye.x) < 30.0 || abs(cameraEye.y) < 30.0 || abs(cameraEye.z) < 30.0)
		cameraEye -= direction;
	}
	modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}