#include "RubickCube.h"

RubickCube::RubickCube() {}

/*
Parametros de entrada:
	GLfloat centerX
	GLfloatcenterY
	GLfloat centerZ
	GLfloat arista  //tamaño de la arista de los cubitos
	GLfloat offset //tamaño de la distancia entre cubos
	GLuint shaderProgram //provisional hasta que empleemos shader dinamicos

Genera un array de cubitos
*/
RubickCube::RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram):cubitos(27,nullptr){
	this->centerX = center.x;
	this->centerY = center.y;
	this->centerZ = center.z;
	this->arista = arista;
	this->offset = offset;
	this->shaderProgram = shaderProgram;
}


glm::vec3 getCharColor(char c) {
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

unsigned int getDuplePosition(std::string duple) {
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

RubickCube::RubickCube(glm::vec3 center, GLfloat arista, GLfloat offset, GLuint shaderProgram, std::string colors):cubitos(27,nullptr){
	GLfloat centerX = center.x;
	GLfloat centerY = center.y;
	GLfloat centerZ = center.z;	

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
	cubitos[11] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U1")]),getCharColor(colors[getDuplePosition("L1")]),BLACK,getCharColor(colors[getDuplePosition("B3")]),BLACK }, shaderProgram);//B3, L1, U7

	cubitos[12] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U8")]),BLACK,BLACK,BLACK,getCharColor(colors[getDuplePosition("F2")]) }, shaderProgram);//F2, U8
	cubitos[13] = new Cube(glm::vec3(centerX, centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U5")]),BLACK,BLACK,BLACK,BLACK }, shaderProgram);//U5
	cubitos[14] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U2")]),BLACK,BLACK,getCharColor(colors[getDuplePosition("B2")]),BLACK }, shaderProgram);//U2, B8

	cubitos[15] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U9")]),BLACK,getCharColor(colors[getDuplePosition("R1")]),BLACK,getCharColor(colors[getDuplePosition("F3")]) }, shaderProgram);//F3,U9,R1
	cubitos[16] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U6")]),BLACK,getCharColor(colors[getDuplePosition("R2")]),BLACK,BLACK }, shaderProgram);//R2, U8
	cubitos[17] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,getCharColor(colors[getDuplePosition("U3")]),BLACK,getCharColor(colors[getDuplePosition("R3")]),getCharColor(colors[getDuplePosition("B1")]),BLACK }, shaderProgram);//R3, B1, U7																																								 																						
																																															 
					

																																															 /
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



std::vector<glm::vec3> RubickCube::generarColoresSegunPos() {
	std::vector<glm::vec3> coloresPos(54);
	char cara;
	for (int i = 0; i < 54; ++i) {
		cara = cuboString[i];
		if (cara == 'U') {
			std::cout << i << ": color azul" << std::endl;
			coloresPos[i] = BLUE;
		}
		else if (cara == 'L') {
			std::cout << i << ": color rojo" << std::endl;
			coloresPos[i] = RED;
		}
		else if (cara == 'F') {
			std::cout << i << ": color amarillo" << std::endl;
			coloresPos[i] = YELLOW;
		}
		else if (cara == 'R') {
			std::cout << i << ": color anaranjado" << std::endl;
			coloresPos[i] = ORANGE;
		}
		else if (cara == 'B') {
			std::cout << i << ": color white" << std::endl;
			coloresPos[i] = WHITE;
		}
		else if (cara == 'D') {
			std::cout << i << ": color verde" << std::endl;
			coloresPos[i] = GREEN;
		}
	}
	return coloresPos;
}

void RubickCube::setCuboString(std::string cuboString) {
	this->cuboString = cuboString;
}

void RubickCube::setOffset(GLfloat offset) {
	this->offset = offset;
}

void RubickCube::Draw() {
	for (Cube* cubito : cubitos) {
		cubito->draw();
	}
}



void RubickCube::Solve() {

}

RubickCube::~RubickCube(){
	for (Cube* cubito : cubitos) {
		delete cubito;
	}
}