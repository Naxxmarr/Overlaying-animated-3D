#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>

#include"VBO.h"

class VAO
{
public:
	//Odniesienie do identyfikatora obiektu Vertex Array Object
	GLuint ID;
	//Konstruktor generuj¹cy identyfikator VAO
	VAO();

	//£¹czy VBO z VAO za pomoc¹ okreœlonego uk³adu
	void LinkAttrib(VBO& VBO, GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void*offset);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
