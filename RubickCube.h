#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "Cube.h"
#include <iostream>

class RubickCube{
private:
	std::vector<Cube*> cubitos;
	GLfloat centerX;
	GLfloat centerY;
	GLfloat centerZ;
	GLfloat arista;
	GLfloat offset;
	GLuint shaderProgram;

	std::string colors;
	glm::vec3 getCharColor(char c);
	unsigned int getDuplePosition(std::string duple);
public:
	RubickCube();
    RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram);
	void restartCube();
	void generateCube();
	void setColors(std::string colors);
	void setOffset(GLfloat offset);
	void Draw();
	void Solve();
    ~RubickCube();
};