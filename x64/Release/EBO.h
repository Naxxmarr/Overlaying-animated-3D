#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<glad/glad.h>
#include<vector>

class EBO
{
public:
	//Odwo³anie do identyfikatora obiektu bufora elementów
	GLuint ID;
	// Konstruktor generuj¹cy obiekt Elements Buffer Object i ³¹cz¹cy go z indeksami
	EBO(std::vector<GLuint>& indices);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif
