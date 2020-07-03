#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
//#include "AKube.h"
#include "Cube.h"
#include <iostream>

class RubickCube{
private:
	std::vector<Cube*> cubitos;

public:
	RubickCube();
    RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram, std::string colors="UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB");
	void Draw();
	void generateRandomCube();
	void Solve();
    ~RubickCube();
};