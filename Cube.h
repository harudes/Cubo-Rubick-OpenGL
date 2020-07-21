#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

/*#define RED glm::vec3(1.0,0.0,0.0)
#define GREEN glm::vec3(0.0,1.0,0.0)
#define BLUE glm::vec3(0.0,0.0,1.0)
#define WHITE glm::vec3(1.0,1.0,1.0)
#define YELLOW glm::vec3(1.0,1.0,0.0)
#define ORANGE glm::vec3(1.0,0.5,0.0)*/

#define RED glm::vec3(0.81,0.8,0.8)
#define GREEN glm::vec3(0.79,0.8,0.8)
#define BLUE glm::vec3(0.8,0.81,0.8)
#define WHITE glm::vec3(0.8,0.79,0.8)
#define YELLOW glm::vec3(0.8,0.8,0.81)
#define ORANGE glm::vec3(0.8,0.8,0.79)

#define BLACK glm::vec3(0.0,0.0,0.0)

class Cube{
	GLfloat *vertices, *vertexColors, *textureCoords, *normal;
	unsigned int shaderProgram, texture, VAO, VBOs[3], EBO, vertexNum, indexNum;
	int *indices;
	void init();
	glm::mat4 model;
	GLuint modelPos;
	glm::vec3 cubeCenter;
public:
	Cube(GLfloat *vertex, GLfloat *colors, int *index, GLuint program);
	Cube(glm::vec3 center, glm::vec3 sideLength, std::vector<glm::vec3> colors, std::vector<glm::vec2> textCoords, GLuint program, unsigned int textureNum);
	void draw();
	void rotate(GLfloat angle, int axis);
	void traslate(glm::vec3 traslation);
	void moveAway(glm::vec3 center, float distance);
    ~Cube();
};