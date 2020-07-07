#include "RubickCube.h"

RubickCube::RubickCube() {}

/*
Parametros de entrada:
	GLfloat centerX
	GLfloat centerY
	GLfloat centerZ
	GLfloat arista  //tamaño de la arista de los cubitos
	GLfloat offset //tamaño de la distancia entre cubos
	GLuint shaderProgram //provisional hasta que empleemos shader dinamicos

Genera un array de cubitos
*/
RubickCube::RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram) :cubitos(27, nullptr), animating(false), animationCounter(0), animationTime(30){
	this->centerX = center.x;
	this->centerY = center.y;
	this->centerZ = center.z;
	this->arista = arista;
	this->offset = offset;
	this->shaderProgram = shaderProgram;

	restartCube();
}

void RubickCube::restartCube() {
	this->colors = "UUUUUUUUULLLLLLLLLFFFFFFFFFRRRRRRRRRBBBBBBBBBDDDDDDDDD";
}


glm::vec3 RubickCube::getCharColor(char c) {
	glm::vec3 color;
	switch (c) {
	case 'F':
		color = YELLOW;
		break;
	case 'D':
		color = GREEN;
		break;
	case 'U':
		color = BLUE;
		break;
	case 'B':
		color = WHITE;
		break;
	case 'R':
		color = ORANGE;
		break;
	case 'L':
		color = RED;
		break;
	}
	return color;
}

unsigned int RubickCube::getDuplePosition(std::string duple) {
	int side, number;
	switch (duple[0]) {
	case 'F':
		side = 2;
		break;
	case 'D':
		side = 3;
		break;
	case 'U':
		side = 0;
		break;
	case 'B':
		side = 5;
		break;
	case 'R':
		side = 1;
		break;
	case 'L':
		side = 4;
		break;
	}
	number = duple[1] - '0';
	return side * 9 + number - 1;
}

void RubickCube::generateCube(){
	cubitos[0] = new Cube(glm::vec3((centerX + arista + offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("F5")]) }, shaderProgram);//F5
	cubitos[1] = new Cube(glm::vec3(centerX, centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//centro
	cubitos[2] = new Cube(glm::vec3((centerX - arista - offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("B5")]),BLACK }, shaderProgram);//B5


	cubitos[3] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,getCharColor(colors[getDuplePosition("L6")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("F4")]) }, shaderProgram);//F4, L6
	cubitos[4] = new Cube(glm::vec3(centerX, (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,getCharColor(colors[getDuplePosition("L5")]),BLACK,BLACK,BLACK }, shaderProgram);//L5
	cubitos[5] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,getCharColor(colors[getDuplePosition("L4")]),BLACK,getCharColor(colors[getDuplePosition("B6")]),BLACK }, shaderProgram);//B6, L4

	cubitos[6] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("R4")]),BLACK,getCharColor(colors[getDuplePosition("F6")]) }, shaderProgram);//F6, R4
	cubitos[7] = new Cube(glm::vec3(centerX, (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("R5")]),BLACK,BLACK }, shaderProgram);//R5
	cubitos[8] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("R6")]),getCharColor(colors[getDuplePosition("B4")]),BLACK }, shaderProgram);//R6, B4



																																										 //---
	cubitos[9] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U7")]),getCharColor(colors[getDuplePosition("L3")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("F1")]) }, shaderProgram);//F1, L3, U7
	cubitos[10] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U4")]),getCharColor(colors[getDuplePosition("L2")]),BLACK,BLACK,BLACK }, shaderProgram);//L2, U4
	cubitos[11] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U1")]),getCharColor(colors[getDuplePosition("L1")]),BLACK,getCharColor(colors[getDuplePosition("B3")]),BLACK }, shaderProgram);//B3, L1, U1

	cubitos[12] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U8")]),BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("F2")]) }, shaderProgram);//F2, U8
	cubitos[13] = new Cube(glm::vec3(centerX, centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U5")]),BLACK,BLACK,BLACK,BLACK }, shaderProgram);//U5
	cubitos[14] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U2")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("B2")]),BLACK }, shaderProgram);//U2, B8

	cubitos[15] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U9")]),BLACK,getCharColor(colors[getDuplePosition("R1")]),BLACK,getCharColor(colors[getDuplePosition("F3")]) }, shaderProgram);//F3,U9,R1
	cubitos[16] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U6")]),BLACK,getCharColor(colors[getDuplePosition("R2")]),BLACK,BLACK }, shaderProgram);//R2, U8
	cubitos[17] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U3")]),BLACK,getCharColor(colors[getDuplePosition("R3")]),getCharColor(colors[getDuplePosition("B1")]),BLACK }, shaderProgram);//R3, B1, U3
																																															 
					

	cubitos[18] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D1")]),BLACK,getCharColor(colors[getDuplePosition("L9")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("F7")]) }, shaderProgram);//F7, L9, D1
	cubitos[19] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D4")]),BLACK,getCharColor(colors[getDuplePosition("L8")]),BLACK,BLACK,BLACK }, shaderProgram);//L8, D2
	cubitos[20] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D7")]),BLACK,getCharColor(colors[getDuplePosition("L7")]),BLACK,getCharColor(colors[getDuplePosition("B9")]),BLACK }, shaderProgram);//L7, B9, D3

	cubitos[21] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D2")]),BLACK,BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("F8")]) }, shaderProgram);//F8, D2
	cubitos[22] = new Cube(glm::vec3(centerX, centerY, (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D5")]),BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//D5
	cubitos[23] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D8")]),BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("B8")]),BLACK }, shaderProgram);//B8, D2

	cubitos[24] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D3")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("R7")]),BLACK,getCharColor(colors[getDuplePosition("F9")]) }, shaderProgram);//F9, R7, D3
	cubitos[25] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D6")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("R8")]),BLACK,BLACK }, shaderProgram);//D6, R8
	cubitos[26] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { getCharColor(colors[getDuplePosition("D9")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("R9")]),getCharColor(colors[getDuplePosition("B7")]),BLACK }, shaderProgram);//R9, B7, D1

}



void RubickCube::setColors(std::string colors) {
	this->colors = colors;
}

void RubickCube::setOffset(GLfloat offset) {
	this->offset = offset;
}

void RubickCube::Draw() {
	for (Cube* cubito : cubitos) {
		cubito->draw();
	}
}

void RubickCube::addCenters(std::vector<int> &indices) {
	switch (actualAnimation[0]) {
	case 'U':
		indices.push_back(13);
		break;
	case 'D':
		indices.push_back(22);
		break;
	case 'R':
		indices.push_back(7);
		break;
	case 'L':
		indices.push_back(4);
		break;
	case 'F':
		indices.push_back(0);
		break;
	case 'B':
		indices.push_back(2);
		break;
	}
}

std::vector<int> RubickCube::getSideIndices() {
	std::vector<int> sideCubes;
	switch (actualAnimation[0]) {
	case 'U':
		sideCubes = CUBE_UP;
		break;
	case 'D':
		sideCubes = CUBE_DOWN;
		break;
	case 'R':
		sideCubes = CUBE_RIGHT;
		break;
	case 'L':
		sideCubes = CUBE_LEFT;
		break;
	case 'F':
		sideCubes = CUBE_FRONT;
		break;
	case 'B':
		sideCubes = CUBE_BACK;
		break;
	}
	return sideCubes;
}

GLfloat RubickCube::getSideAngle() {
	float angle;
	switch (actualAnimation[0]) {
	case 'U':
		angle = -1.0;
		break;
	case 'D':
		angle = 1.0;
		break;
	case 'R':
		angle = -1.0;
		break;
	case 'L':
		angle = 1.0;
		break;
	case 'F':
		angle = -1.0;
		break;
	case 'B':
		angle = 1.0;
		break;
	}
	return angle;
}

void RubickCube::move() {
	std::vector<int> sideCubes = getSideIndices();
	addCenters(sideCubes);
	int axis;
	GLfloat angle = getSideAngle();
	angle *= glm::pi<float>() / 60;
	switch (actualAnimation[0]) {
	case 'U':
		axis = 2;
		break;
	case 'D':
		axis = 2;
		break;
	case 'R':
		axis = 1;
		break;
	case 'L':
		axis = 1;
		break;
	case 'F':
		axis = 0;
		break;
	case 'B':
		axis = 0;
		break;
	}
	if (actualAnimation.length() == 2 && actualAnimation[1] == '\'')
		angle *= -1;
	for (int i : sideCubes) {
		cubitos[i]->rotate(angle, axis);
	}
}

void RubickCube::updateIndex() {
	int offset = 6;
	if (actualAnimation.length() == 2 && actualAnimation[1] == '\'')
		offset = 2;
	if (actualAnimation.length() == 2 && actualAnimation[1] == '2')
		offset = 4;

	std::vector<int> sideCubes = getSideIndices();
	std::vector<Cube*> originalCubitos = cubitos;
	for (std::size_t i = 0, top= sideCubes.size(); i < top; ++i) {
		cubitos[sideCubes[i]] = originalCubitos[sideCubes[(i+offset)%top]];
	}
}

void RubickCube::movement() {
	if (!solutionQueue.empty()) {
		if (!animating) {
			actualAnimation = solutionQueue.front();
			setAnimation(actualAnimation);
			solutionQueue.pop();
		}
	}
	if (animationCounter == animationTime) {
		animating = false;
		updateIndex();
		animationCounter++;
	}
	if (animating) {
		move();
		animationCounter++;
	}
}

bool RubickCube::setAnimation(std::string move) {
	if (!animating) {
		actualAnimation = move;
		animating = true;
		animationCounter = 0;
		if (actualAnimation.length() == 2 && actualAnimation[1] == '2')
			animationTime = 60;
		else
			animationTime = 30;
		return true;
	}
	return false;
}

void RubickCube::Solve(std::vector<std::string> solution) {
	for (std::string move : solution) {
		solutionQueue.push(move);
	}
}

void RubickCube::expand(float distance) {
	for (Cube* cubito : cubitos) {
		if(cubito != cubitos[1])
		cubito->moveAway(glm::vec3(centerX,centerY,centerZ), distance);
	}
}

RubickCube::~RubickCube(){
	for (Cube* cubito : cubitos) {
		delete cubito;
	}
}