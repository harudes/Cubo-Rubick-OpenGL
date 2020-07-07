#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "Cube.h"
#include <iostream>
#include <queue>

#define CUBE_UP {11, 14,17, 16, 15, 12, 9, 10}
#define CUBE_DOWN {18, 21, 24, 25, 26, 23, 20, 19}
#define CUBE_RIGHT {15, 16, 17, 8, 26, 25, 24, 6}
#define CUBE_LEFT {11, 10, 9, 3, 18, 19, 20, 5}
#define CUBE_FRONT {9, 12, 15, 6, 24, 21, 18, 3}
#define CUBE_BACK {17, 14, 11, 5, 20, 23, 26, 8}


class RubickCube{
private:
	bool animating;
	int animationCounter;
	int animationTime;
	std::string actualAnimation;
	std::queue<std::string> solutionQueue;

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
	void addCenters(std::vector<int> &indices);
	std::vector<int> getSideIndices();
	GLfloat getSideAngle();
	void move();
	void updateIndex();
public:
	RubickCube();
    RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram);
	void restartCube();
	void generateCube();
	void setColors(std::string colors);
	void setOffset(GLfloat offset);
	void Draw();
	void movement();
	void Solve(std::vector<std::string> solution);
	void expand(float distance);
	bool setAnimation(std::string move);
    ~RubickCube();
};