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

void RubickCube::generateSolvedCube() {
	cubitos[0] = new Cube(glm::vec3((centerX + arista + offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);
	cubitos[1] = new Cube(glm::vec3(centerX, centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//centro
	cubitos[2] = new Cube(glm::vec3((centerX - arista - offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,WHITE,BLACK }, shaderProgram);


	cubitos[3] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,BLACK,YELLOW }, shaderProgram);
	cubitos[4] = new Cube(glm::vec3(centerX, (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,BLACK,BLACK }, shaderProgram);//L5
	cubitos[5] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,WHITE,BLACK }, shaderProgram);

	cubitos[6] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);
	cubitos[7] = new Cube(glm::vec3(centerX, (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);
	cubitos[8] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);

																																										 //---

	cubitos[9] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,BLACK,YELLOW }, shaderProgram);
	cubitos[10] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,BLACK,BLACK }, shaderProgram);
	cubitos[11] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,WHITE,BLACK }, shaderProgram);

	cubitos[12] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);
	cubitos[13] = new Cube(glm::vec3(centerX, centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,BLACK,BLACK }, shaderProgram);
	cubitos[14] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,WHITE,BLACK }, shaderProgram);

	cubitos[15] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);
	cubitos[16] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);
	cubitos[17] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);

																																															 //---

	cubitos[18] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,BLACK,YELLOW }, shaderProgram);
	cubitos[19] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,BLACK,BLACK }, shaderProgram);//D4, L8
	cubitos[20] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,WHITE,BLACK }, shaderProgram);//D7, L7, B9,

	cubitos[21] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);//D2, F8
	cubitos[22] = new Cube(glm::vec3(centerX, centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//D5
	cubitos[23] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,WHITE,BLACK }, shaderProgram);//D8, B8

	cubitos[24] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);//D3, R7, F9
	cubitos[25] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);//D6, R8
	cubitos[26] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);//D9,R9, B7
}

void RubickCube::generateCube() {
	std::vector<glm::vec3> coloresPos = generarColoresSegunPos();

	cubitos[0] = new Cube(glm::vec3((centerX + arista + offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK, coloresPos[22] }, shaderProgram);//F5
	cubitos[1] = new Cube(glm::vec3(centerX, centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//centro
	cubitos[2] = new Cube(glm::vec3((centerX - arista - offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,coloresPos[40],BLACK }, shaderProgram);//B5


	cubitos[3] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,coloresPos[14],BLACK,BLACK,coloresPos[21] }, shaderProgram);//L6, F4
	cubitos[4] = new Cube(glm::vec3(centerX, (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,coloresPos[13],BLACK,BLACK,BLACK }, shaderProgram);//L5
	cubitos[5] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,coloresPos[12],BLACK,coloresPos[41],BLACK }, shaderProgram);//L4, B6

	cubitos[6] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,coloresPos[30],BLACK,coloresPos[23] }, shaderProgram);//R4, F6
	cubitos[7] = new Cube(glm::vec3(centerX, (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,coloresPos[31],BLACK,BLACK }, shaderProgram);//R5
	cubitos[8] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,coloresPos[32],coloresPos[39],BLACK }, shaderProgram);//R6, B4

																								
																																														  
																																														  //---

	cubitos[9] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[6],coloresPos[11],BLACK,BLACK,coloresPos[18] }, shaderProgram);//U7, L3, F1, 
	cubitos[10] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[3],coloresPos[10],BLACK,BLACK,BLACK }, shaderProgram);// U4,L2
	cubitos[11] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[0],coloresPos[9],BLACK,coloresPos[38],BLACK }, shaderProgram);//U1, L1, B3

	cubitos[12] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ + arista + offset)), arista, { BLACK,coloresPos[7],BLACK,BLACK,BLACK,coloresPos[19] }, shaderProgram);//U8, F2
	cubitos[13] = new Cube(glm::vec3(centerX, centerY, (centerZ + arista + offset)), arista, { BLACK,coloresPos[4],BLACK,BLACK,BLACK,BLACK }, shaderProgram);//U5
	cubitos[14] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ + arista + offset)), arista, { BLACK,coloresPos[1],BLACK,BLACK,coloresPos[37],BLACK }, shaderProgram);//U2, B2

	cubitos[15] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[8],BLACK,coloresPos[27],BLACK,coloresPos[20] }, shaderProgram);//U9,R1,F3
	cubitos[16] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[5],BLACK,coloresPos[28],BLACK,BLACK }, shaderProgram);//U6,R2
	cubitos[17] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,coloresPos[2],BLACK,coloresPos[29],coloresPos[36],BLACK }, shaderProgram);//U3, R3, B1

																									
																																															 
																																															 //---

	cubitos[18] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { coloresPos[45],BLACK,coloresPos[17],BLACK,BLACK,coloresPos[24] }, shaderProgram);//D1, L9, F7
	cubitos[19] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ - arista - offset)), arista, { coloresPos[48],BLACK,coloresPos[16],BLACK,BLACK,BLACK }, shaderProgram);//D4, L8
	cubitos[20] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { coloresPos[51],BLACK,coloresPos[15],BLACK,coloresPos[44],BLACK }, shaderProgram);//D7, L7, B9,

	cubitos[21] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ - arista - offset)), arista, { coloresPos[46],BLACK,BLACK,BLACK,BLACK,coloresPos[25] }, shaderProgram);//D2,F8
	cubitos[22] = new Cube(glm::vec3(centerX, centerY, (centerZ - arista - offset)), arista, { coloresPos[49],BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//D5
	cubitos[23] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ - arista - offset)), arista, { coloresPos[52],BLACK,BLACK,BLACK,coloresPos[43],BLACK }, shaderProgram);//D8,B8

	cubitos[24] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { coloresPos[47],BLACK,BLACK,coloresPos[33],BLACK,coloresPos[26] }, shaderProgram);//D3, R7, F9
	cubitos[25] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ - arista - offset)), arista, { coloresPos[50],BLACK,BLACK,coloresPos[34],BLACK,BLACK }, shaderProgram);//D6, R8
	cubitos[26] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { coloresPos[53],BLACK,BLACK,coloresPos[35],coloresPos[42],BLACK }, shaderProgram);//D9,R9, B7

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