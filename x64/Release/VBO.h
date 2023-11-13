#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm.hpp>
#include<glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;

};

class VBO
{
public:
	//Identyfikator referencyjny obiektu bufora wierzcho³ków
	GLuint ID;
	// Konstruktor generuj¹cy Vertex Buffer Object i ³¹cz¹cy go z wierzcho³kami
	VBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif