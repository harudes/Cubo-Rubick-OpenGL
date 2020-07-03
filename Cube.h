#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#define RED glm::vec3(1.0,0.0,0.0)
#define GREEN glm::vec3(0.0,1.0,0.0)
#define BLUE glm::vec3(0.0,0.0,1.0)
#define WHITE glm::vec3(1.0,1.0,1.0)
#define YELLOW glm::vec3(1.0,1.0,0.0)
#define ORANGE glm::vec3(1.0,0.5,0.0)
#define BLACK glm::vec3(0.0,0.0,0.3)

class Cube{
	GLfloat *vertices, *vertexColors;
	unsigned int shaderProgram, VAO, VBOs[2], EBO, vertexNum, indexNum;
	int *indices;
	void init();
	glm::mat4 model;
	GLuint modelPos;
public:
	Cube(GLfloat *vertex, GLfloat *colors, int *index, GLuint program);
	Cube(glm::vec3 center, GLfloat sideLength, std::vector<glm::vec3> colors, GLuint program);
	void draw();
	void rotate(GLfloat angle, int axis);
    ~Cube();
};