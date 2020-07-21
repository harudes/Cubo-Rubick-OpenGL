#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "RubickCube.h"
#include "AllCube/random.h"
#include "AllCube/solve.h"
//#include "AKube.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void printComands();

string imgRoute = "";

//~~~~~~~~~~~~~~~~ GLOBAL VARIABLES OF THE RUBICK'S CUBE~~~~~~~~~~~~~~~~~~
GLfloat centerX = 0.0f,
centerY = 0.0f,
centerZ = 0.0f;
GLfloat arista = 0.5; //tamaño de la arista de los cubitos
GLfloat offset = 0.00;//tamaño de la distancia entre cubos
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

glm::vec3 cameraUp(0.0, 0.0, 1.0);
glm::vec3 cameraEye(7.0, 0.0, 0.0);
glm::vec3 lightOrigin(-5.0,5.0,5.0);

GLuint projectionPos;
GLuint modelviewPos;
GLuint lightPosPos;
GLuint viewPosPos;
GLuint lightColorPos;

const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"layout (location = 3) in vec3 aNormal;\n"
"out vec3 Color;\n"
"out vec2 TexCoord;\n"
"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"	FragPos = vec3(model * vec4(aPos,1.0));\n"
"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"	Color = aColor;\n"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 Color;\n"
"in vec2 TexCoord;\n"
"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"out vec4 fragColor;\n"
"uniform sampler2D texture1;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 viewPos;\n"
"uniform vec3 lightColor;\n"
"void main(void)\n"
"{\n"
"	float ambientStrenght = 0.8f;\n"//ambient
"	vec3 ambient = ambientStrenght * lightColor;\n"
""
"	vec3 norm = normalize(Normal);\n"//diffuse
"	vec3 lightDir = normalize(lightPos - FragPos);\n"
"	float diff = max(dot(norm, lightDir),0.0);\n"
"	vec3 diffuse = diff * lightColor;\n"
""
"	float specularStrenght = 0.5f;\n"//specular
"	vec3 viewDir = normalize(viewPos - FragPos);\n"
"	vec3 reflectDir = reflect(-lightDir, norm);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
"	vec3 specular = specularStrenght * spec * lightColor;\n"
""
"	vec3 result = (ambient + diffuse + specular) * Color;\n"
"   fragColor = texture(texture1, TexCoord) * vec4(result, 1.0f);\n"
"}\n\0";

int main(int agrc, char* argv[])
{
	printComands();
	string route = argv[0];
	if (route == "C:\\Users\\luisf\\Desktop\\Grafica\\GLFW_GLAD_GLUT_GLEW_cmake_project\\build\\mak.vc15\\x64\\src\\Final\\Debug\\Final.exe") {//Ruta de ejecutable
		imgRoute = "C://Users//luisf//Desktop//Grafica//Cubo-Rubick-OpenGL//CuboRubik.png";//Ruta de la textura
	}
	else if (route == "") {
		imgRoute = "D:/Documentos/Semestre 2020-1/Computacion_Grafica/Material Entregado/GLFW_GLAD_GLUT_GLEW_cmake_project/src/Cubo11/CuboRubik.png";
	}
	else
		imgRoute = "C://Users//luisf//Desktop//Grafica//Cubo-Rubick-OpenGL//CuboRubik.png";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubick Cube Simulator", NULL, NULL);
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
	lightPosPos = glGetUniformLocation(shaderProgram, "lightPos");
	viewPosPos = glGetUniformLocation(shaderProgram, "viewPos");
	lightColorPos = glGetUniformLocation(shaderProgram, "lightColor");
	modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
	projection = glm::mat4(1.0f);
	framebuffer_size_callback(window, 500, 500);
	glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
	glUniform3f(viewPosPos,cameraEye.x,cameraEye.y,cameraEye.z);
	glUniform3f(lightColorPos, 1.0f, 1.0f, 1.0f);
	//glUniform3f(lightPosPos, lightOrigin.x, lightOrigin.y, lightOrigin.z);
	glUniform3f(lightPosPos, -cameraEye.x*2, -cameraEye.y*2, -5.0f);


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
	//stbi_set_flip_vertically_on_load(true);
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(imgRoute.c_str(), &width, &height, &nrChannels, 0);
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

	cuboRubick = new RubickCube(glm::vec3(centerX, centerY, centerZ), arista, offset, shader, texture);
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
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() / 12, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rotation = glm::rotate(glm::mat4(1.0f), -glm::pi<float>() / 12, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (abs(cameraEye.x) < 0.00001f) {
			rotation = glm::rotate(glm::mat4(1.0f), -glm::pi<float>() / 12, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (abs(cameraEye.y) < 0.00001f) {
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
		cameraEye = glm::vec3(7, 0, 0);
		modelview = glm::lookAt(cameraEye, cameraCenter, cameraUp);
		glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
		glUniform3f(viewPosPos, cameraEye.x, cameraEye.y, cameraEye.z);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		//~~~~~~~~~~~~~~~~ OBTAINING RUBBICKS DISORDERED ~~~~~~~~~~~~~~~~~~	
		//std::string data = GetData();
		//std::string cubo = get_cubo(data);
		//-----------------------------------------------------------------
		std::string cubo = randomize();
		std::vector<std::string> solution = get_solution(cubo);
		cuboRubick->setColors(cubo);
		cuboRubick->generateCube();
		cuboRubick->Solve(solution);
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		std::vector<std::string> movements_to_scramble = scramble(15);
		for (int i = 0; i < (int)movements_to_scramble.size(); ++i)std::cout << movements_to_scramble[i] << 'f'; std::cout << std::endl;
		cuboRubick->Scramble(movements_to_scramble);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		std::vector<std::string> solution = get_solution(to_cube_not(cuboRubick->get_sol()));
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
	glUniform3f(viewPosPos, cameraEye.x, cameraEye.y, cameraEye.z);
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

void printComands() {
	std::cout << std::endl << std::endl;
	std::cout << "|----------------------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|----------------------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|Presione la tecla T para generar un cubo aleatorio y que se resuelva automaticamente                      |" << std::endl;
	std::cout << "|Presione la tecla L para desordenar el cubo por pasos                                                     |" << std::endl;
	std::cout << "|Presione la tecla P para armar el cubo generado por la tecla L                                            |" << std::endl;
	std::cout << "|Presione la tecla W para girar la cara superior en sentido horario                                        |" << std::endl;
	std::cout << "|Presione la tecla S para girar la cara inferior en sentido horario                                        |" << std::endl;
	std::cout << "|Presione la tecla A para girar la cara izquierda en sentido horario                                       |" << std::endl;
	std::cout << "|Presione la tecla D para girar la cara derecha en sentido horario                                         |" << std::endl;
	std::cout << "|Presione la tecla Z para girar la cara posterior en sentido horario                                       |" << std::endl;
	std::cout << "|Presione la tecla X para girar la cara Trasera en sentido horario                                         |" << std::endl;
	std::cout << "|Presione las flechas direccionales para mover la camara                                                   |" << std::endl;
	std::cout << "|Presione las teclas + y - para expandir o contraer los cubitos                                            |" << std::endl;
	std::cout << "|Use la rueda del raton para acercar o alejar la camara                                                    |" << std::endl;
	std::cout << "|Recuerde actualizar la ruta de la textura                                                                 |" << std::endl;
	std::cout << "|----------------------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << "|----------------------------------------------------------------------------------------------------------|" << std::endl;
	std::cout << std::endl << std::endl;
}