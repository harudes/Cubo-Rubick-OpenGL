#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "Cube.h"

class RubickCube{
private:
	std::vector<Cube*> cubitos;
	GLfloat centerX;
	GLfloat centerY;
	GLfloat centerZ;
	GLfloat arista;
	GLfloat offset;
	GLuint shaderProgram;

	std::string cuboString;

public:
	RubickCube();
    RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram);
	void generateSolvedCube();
	void generateCube();
	std::vector<glm::vec3> generarColoresSegunPos();
	void setCuboString(std::string cuboString);
	void setOffset(GLfloat offset);
	void Draw();
	void Solve();
    ~RubickCube();
};