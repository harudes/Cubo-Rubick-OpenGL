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
	GLfloat centerX = center.x;
	GLfloat centerY = center.y;
	GLfloat centerZ = center.z;	

	cubitos[0] = new Cube(glm::vec3((centerX + arista + offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);//F5
	cubitos[1] = new Cube(glm::vec3(centerX, centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//centro
	cubitos[2] = new Cube(glm::vec3((centerX - arista - offset), centerY, centerZ), arista, { BLACK,BLACK,BLACK,BLACK,WHITE,BLACK }, shaderProgram);//B5


	cubitos[3] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,BLACK,YELLOW }, shaderProgram);//F4, L6
	cubitos[4] = new Cube(glm::vec3(centerX, (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,BLACK,BLACK }, shaderProgram);//L5
	cubitos[5] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), centerZ), arista, { BLACK,BLACK,RED,BLACK,WHITE,BLACK }, shaderProgram);//B6, L4

	cubitos[6] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);//F6, R4
	cubitos[7] = new Cube(glm::vec3(centerX, (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);//R5
	cubitos[8] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), centerZ), arista, { BLACK,BLACK,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);//R6, B4

	//---

	cubitos[9] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,BLACK,YELLOW }, shaderProgram);//F1, L3, U7
	cubitos[10] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,BLACK,BLACK }, shaderProgram);//L2, U4
	cubitos[11] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,RED,BLACK,WHITE,BLACK }, shaderProgram);//B3, L1, U7

	cubitos[12] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);//F2, U8
	cubitos[13] = new Cube(glm::vec3(centerX, centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//U5
	cubitos[14] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,BLACK,WHITE,BLACK }, shaderProgram);//U2, B8

	cubitos[15] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);//F3,U9,R1
	cubitos[16] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);//R2, U8
	cubitos[17] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ + arista + offset)), arista, { BLACK,BLUE,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);//R3, B1, U7

	//---

	cubitos[18] = new Cube(glm::vec3((centerX + arista + offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,BLACK,YELLOW }, shaderProgram);//F7, L9, D1
	cubitos[19] = new Cube(glm::vec3(centerX, (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,BLACK,BLACK }, shaderProgram);//L8, D2
	cubitos[20] = new Cube(glm::vec3((centerX - arista - offset), (centerY - arista - offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,RED,BLACK,WHITE,BLACK }, shaderProgram);//L7, B9, D3

	cubitos[21] = new Cube(glm::vec3((centerX + arista + offset), centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,BLACK,YELLOW }, shaderProgram);//F8, D2
	cubitos[22] = new Cube(glm::vec3(centerX, centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,BLACK,BLACK }, shaderProgram);//D5
	cubitos[23] = new Cube(glm::vec3((centerX - arista - offset), centerY, (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,BLACK,WHITE,BLACK }, shaderProgram);//B8, D2

	cubitos[24] = new Cube(glm::vec3((centerX + arista + offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,BLACK,YELLOW }, shaderProgram);//F9, R7, D3
	cubitos[25] = new Cube(glm::vec3(centerX, (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,BLACK,BLACK }, shaderProgram);//D6, R8
	cubitos[26] = new Cube(glm::vec3((centerX - arista - offset), (centerY + arista + offset), (centerZ - arista - offset)), arista, { GREEN,BLACK,BLACK,ORANGE,WHITE,BLACK }, shaderProgram);//R9, B7, D1

}

void RubickCube::Draw() {
	for (Cube* cubito : cubitos) {
		cubito->draw();
	}
}

void RubickCube::generateRandomCube() {
	/*std::string data = GetData();
	std::string cubo = get_cubo(data);
	std::vector<std::string> solution = get_solution(data);
	std::cout << cubo << std::endl;

	for (string paso : solution)
		std::cout << paso << std::endl;*/
}

void RubickCube::Solve() {

}

RubickCube::~RubickCube(){
	for (Cube* cubito : cubitos) {
		delete cubito;
	}
}