#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#pragma once
//#include "AKube.h"
#include "Cube.h"

class RubickCube{
private:
	std::vector<Cube*> cubitos;

public:
	RubickCube();
    RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram);
	void Draw();
	void generateRandomCube();
	void Solve();
    ~RubickCube();
};