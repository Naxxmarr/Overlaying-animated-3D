#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<glad/glad.h>
#include<vector>

class EBO
{
public:
	//Odwo�anie do identyfikatora obiektu bufora element�w
	GLuint ID;
	// Konstruktor generuj�cy obiekt Elements Buffer Object i ��cz�cy go z indeksami
	EBO(std::vector<GLuint>& indices);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif
