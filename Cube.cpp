#include "Cube.h"

Cube::Cube(GLfloat *vertex, GLfloat *colors, int *index, GLuint program) :vertexNum(24), indexNum(36), shaderProgram(program), vertices(vertex), vertexColors(colors), indices(index) {
	init();
}

//El primer parametro es un vec3, el centro del cubo
//El segundo parametro es un GLfloat, la longitud de las aristas
//El tercer parametro es un vector de 6 vec3, que representan los colores de cada cara, tengo algunos defines con los colores del cubo
//El cuarto parametro es el programa, por si en algun momento usamos diferentes shaders
Cube::Cube(glm::vec3 center, GLfloat sideLength, std::vector<glm::vec3> colors, GLuint program) :vertexNum(24),indexNum(36),shaderProgram(program) {

	model = glm::mat4(1.0);

	modelPos = glGetUniformLocation(shaderProgram, "model");

	GLfloat side = sideLength / 2.0;

	vertices = new GLfloat[72];

	vertexColors = new GLfloat[72];

	indices = new int[36];

	GLfloat newVertices[72] = {
		center.x - side, center.y - side, center.z - side,
		center.x + side, center.y - side, center.z - side,
		center.x + side, center.y + side, center.z - side,
		center.x - side, center.y + side, center.z - side,

		center.x - side, center.y - side, center.z + side,
		center.x - side, center.y + side, center.z + side,
		center.x + side, center.y + side, center.z + side,
		center.x + side, center.y - side, center.z + side,

		center.x - side, center.y - side, center.z - side,
		center.x + side, center.y - side, center.z - side,
		center.x + side, center.y - side, center.z + side,
		center.x - side, center.y - side, center.z + side,

		center.x - side, center.y + side, center.z - side,
		center.x - side, center.y + side, center.z + side,
		center.x + side, center.y + side, center.z + side,
		center.x + side, center.y + side, center.z - side,

		center.x - side, center.y - side, center.z - side,
		center.x - side, center.y + side, center.z - side,
		center.x - side, center.y + side, center.z + side,
		center.x - side, center.y - side, center.z + side,

		center.x + side, center.y - side, center.z - side,
		center.x + side, center.y - side, center.z + side,
		center.x + side, center.y + side, center.z + side,
		center.x + side, center.y + side, center.z - side
	};

	

	GLubyte newIndices[36] = {
		0, 1, 2,
		0 ,2 ,3,

		4 ,5 ,6,
		4 ,6 ,7,

		8 ,9,10,
		8 ,10 ,11,

		12 ,13 ,14,
		12 ,14 ,15,

		16 ,17 ,18,
		16 ,18 ,19,

		20 ,21 ,22,
		20 ,22 ,23
	};

	for (int i = 0; i < 36; ++i) {
		indices[i] = newIndices[i];
		vertices[i * 2] = newVertices[i * 2];
		vertices[i * 2 + 1] = newVertices[i * 2 + 1];
	}

	for (int i = 0; i < 72; i+=3) {
		vertexColors[i] = colors[i / 12].x;
		vertexColors[i+1] = colors[i / 12].y;
		vertexColors[i+2] = colors[i / 12].z;
	}

	init();
}

void Cube::draw() {

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexNum * 3, vertices, GL_STATIC_DRAW);

	glUseProgram(shaderProgram);

	glUniformMatrix4fv(modelPos, 1, GL_FALSE, &model[0][0]);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void Cube::rotate(GLfloat angle, int axis) {
	glm::vec3 direction;
	switch (axis) {
	case 0:
		direction = glm::vec3(1.0, 0.0, 0.0);
		break;
	case 1:
		direction = glm::vec3(0.0, 1.0, 0.0);
		break;
	case 2:
		direction = glm::vec3(0.0, 0.0, 1.0);
		break;
	}
	model = glm::rotate(glm::mat4(1.0f), angle, direction)* model;
}

void Cube::init() {


	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertexNum * 3, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors[0]) * vertexNum * 3, vertexColors, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexNum, indices, GL_STATIC_DRAW);

	//glBindVertexArray(0);
}

Cube::~Cube(){
	delete vertices;
	delete vertexColors;
	delete indices;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(1, &EBO);
}