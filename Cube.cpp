#include "Cube.h"

Cube::Cube(GLfloat *vertex, GLfloat *colors, int *index, GLuint program) :vertexNum(48), indexNum(72), shaderProgram(program), vertices(vertex), vertexColors(colors), indices(index) {
	init();
}

//El primer parametro es un vec3, el centro del cubo
//El segundo parametro es un GLfloat, la longitud de las aristas
//El tercer parametro es un vector de 6 vec3, que representan los colores de cada cara, tengo algunos defines con los colores del cubo
//El cuarto parametro es el programa, por si en algun momento usamos diferentes shaders
Cube::Cube(glm::vec3 center, glm::vec3 sideLength, std::vector<glm::vec3> colors, std::vector<glm::vec2> textCoords, GLuint program, unsigned int textureNum) :vertexNum(48),indexNum(72),shaderProgram(program),cubeCenter(center), texture(textureNum) {

	model = glm::mat4(1.0);

	modelPos = glGetUniformLocation(shaderProgram, "model");
	glm::vec3 side = sideLength;
	side.x /= 2;
	side.y /= 2;
	side.z /= 2;

	std::vector<glm::vec3> newColors(6,BLACK);

	newColors.insert(newColors.end(), colors.begin(), colors.end());

	std::vector<glm::vec2> newTextCoords;

	newTextCoords.reserve(48);

	for (int i = 0; i < 6; ++i) {
		newTextCoords.push_back(glm::vec2(0.0, 0.0));
		newTextCoords.push_back(glm::vec2(0.0, 0.01));
		newTextCoords.push_back(glm::vec2(0.01, 0.01));
		newTextCoords.push_back(glm::vec2(0.01, 0.0));
	}

	newTextCoords.insert(newTextCoords.end(),textCoords.begin(),textCoords.end());

	vertices = new GLfloat[144];

	vertexColors = new GLfloat[144];

	normal = new GLfloat[144];

	textureCoords = new GLfloat[96];

	indices = new int[72];

	GLfloat newVertices[144] = {
		center.x - side.x, center.y - side.y, center.z - side.z,
		center.x + side.x, center.y - side.y, center.z - side.z,
		center.x + side.x, center.y + side.y, center.z - side.z,
		center.x - side.x, center.y + side.y, center.z - side.z,

		center.x + side.x, center.y - side.y, center.z + side.z,
		center.x - side.x, center.y - side.y, center.z + side.z,
		center.x - side.x, center.y + side.y, center.z + side.z,
		center.x + side.x, center.y + side.y, center.z + side.z,

		center.x - side.x, center.y - side.y, center.z - side.z,
		center.x - side.x, center.y - side.y, center.z + side.z,
		center.x + side.x, center.y - side.y, center.z + side.z,
		center.x + side.x, center.y - side.y, center.z - side.z,

		center.x + side.x, center.y + side.y, center.z - side.z,
		center.x + side.x, center.y + side.y, center.z + side.z,
		center.x - side.x, center.y + side.y, center.z + side.z,
		center.x - side.x, center.y + side.y, center.z - side.z,

		center.x - side.x, center.y + side.y, center.z - side.z,
		center.x - side.x, center.y + side.y, center.z + side.z,
		center.x - side.x, center.y - side.y, center.z + side.z,
		center.x - side.x, center.y - side.y, center.z - side.z,

		center.x + side.x, center.y - side.y, center.z - side.z,
		center.x + side.x, center.y - side.y, center.z + side.z,
		center.x + side.x, center.y + side.y, center.z + side.z,
		center.x + side.x, center.y + side.y, center.z - side.z,



		center.x - (side.x - 0.05), center.y - (side.y - 0.05), center.z - side.z - 0.001,
		center.x + (side.x - 0.05), center.y - (side.y - 0.05), center.z - side.z - 0.001,
		center.x + (side.x - 0.05), center.y + (side.y - 0.05), center.z - side.z - 0.001,
		center.x - (side.x - 0.05), center.y + (side.y - 0.05), center.z - side.z - 0.001,

		center.x + (side.x - 0.05), center.y - (side.y - 0.05), center.z + side.z + 0.001,
		center.x - (side.x - 0.05), center.y - (side.y - 0.05), center.z + side.z + 0.001,
		center.x - (side.x - 0.05), center.y + (side.y - 0.05), center.z + side.z + 0.001,
		center.x + (side.x - 0.05), center.y + (side.y - 0.05), center.z + side.z + 0.001,

		center.x - (side.x - 0.05), center.y - side.y - 0.001, center.z - (side.z - 0.05),
		center.x - (side.x - 0.05), center.y - side.y - 0.001, center.z + (side.z - 0.05),
		center.x + (side.x - 0.05), center.y - side.y - 0.001, center.z + (side.z - 0.05),
		center.x + (side.x - 0.05), center.y - side.y - 0.001, center.z - (side.z - 0.05),

		center.x + (side.x - 0.05), center.y + side.y + 0.001, center.z - (side.z - 0.05),
		center.x + (side.x - 0.05), center.y + side.y + 0.001, center.z + (side.z - 0.05),
		center.x - (side.x - 0.05), center.y + side.y + 0.001, center.z + (side.z - 0.05),
		center.x - (side.x - 0.05), center.y + side.y + 0.001, center.z - (side.z - 0.05),

		center.x - side.x - 0.001, center.y + (side.y - 0.05), center.z - (side.z - 0.05),
		center.x - side.x - 0.001, center.y + (side.y - 0.05), center.z + (side.z - 0.05),
		center.x - side.x - 0.001, center.y - (side.y - 0.05), center.z + (side.z - 0.05),
		center.x - side.x - 0.001, center.y - (side.y - 0.05), center.z - (side.z - 0.05),

		center.x + side.x + 0.001, center.y - (side.y - 0.05), center.z - (side.z - 0.05),
		center.x + side.x + 0.001, center.y - (side.y - 0.05), center.z + (side.z - 0.05),
		center.x + side.x + 0.001, center.y + (side.y - 0.05), center.z + (side.z - 0.05),
		center.x + side.x + 0.001, center.y + (side.y - 0.05), center.z - (side.z - 0.05)
	};

	GLfloat newNormal[144] = {
		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,

		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,

		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,

		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,

		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,

		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f,



		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,
		0.0f, 0.0f , -1.0f,

		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,
		0.0f, 0.0f , 1.0f,

		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,
		0.0f, -1.0f , 0.0f,

		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,
		0.0f, 1.0f , 0.0f,

		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,
		-1.0f, 0.0f , 0.0f,

		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f,
		1.0f, 0.0f , 0.0f
	};



	GLubyte newIndices[72] = {
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
		20 ,22 ,23,



		24, 25, 26,
		24 ,26 ,27,

		28 ,29 ,30,
		28 ,30 ,31,

		32 ,33,34,
		32 ,34 ,35,

		36 ,37 ,38,
		36 ,38 ,39,

		40 ,41 ,42,
		40 ,42 ,43,

		44 ,45 ,46,
		44 ,46 ,47
	};

	for (int i = 0; i < 72; ++i) {
		indices[i] = newIndices[i];
		vertices[i * 2] = newVertices[i * 2];
		vertices[i * 2 + 1] = newVertices[i * 2 + 1];
		normal[i * 2] = newNormal[i * 2];
		normal[i * 2 + 1] = newNormal[i * 2 + 1];
	}

	for (int i = 0; i < 144; i += 3) {
		vertexColors[i] = newColors[i / 12].x;
		vertexColors[i + 1] = newColors[i / 12].y;
		vertexColors[i + 2] = newColors[i / 12].z;
	}

	for (int i = 0; i < 48; ++i) {
		textureCoords[i * 2] = newTextCoords[i].x;
		textureCoords[i * 2 + 1] = newTextCoords[i].y;
	}

	init();

	delete[] vertices;
	delete[] vertexColors;
	delete[] indices;
	delete[] normal;
	delete[] textureCoords;
}

void Cube::draw() {

	

	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);

	glBindTexture(GL_TEXTURE_2D, texture);

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
	model = glm::rotate(glm::mat4(1.0f), angle, direction) * model;
	cubeCenter = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, direction)) * cubeCenter;
}

void Cube::traslate(glm::vec3 traslation) {
	model = glm::translate(glm::mat4(1.0f), traslation) * model;
	cubeCenter = glm::mat3(glm::translate(glm::mat4(1.0f), traslation)) * cubeCenter;
}

void Cube::init() {


	glGenVertexArrays(1, &VAO);
	glGenBuffers(4, VBOs);
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

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords[0]) * vertexNum * 2, textureCoords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normal[0]) * vertexNum * 3, normal, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexNum, indices, GL_STATIC_DRAW);

	//glBindVertexArray(0);
}

void Cube::moveAway(glm::vec3 center, float distance) {
	glm::vec3 direction = cubeCenter - center;
	if (direction.x > 0) direction.x = 1;
	if (direction.y > 0) direction.y= 1;
	if (direction.z > 0) direction.z= 1;
	model = glm::translate(glm::mat4(1.0), direction * distance) * model;

	cubeCenter = glm::mat3(glm::translate(glm::mat4(1.0), direction * distance)) * cubeCenter;
}

Cube::~Cube(){
	delete vertices;
	delete vertexColors;
	delete indices;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBOs);
	glDeleteBuffers(1, &EBO);
}