#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>

#include"VBO.h"

class VAO
{
public:
	//Odniesienie do identyfikatora obiektu Vertex Array Object
	GLuint ID;
	//Konstruktor generuj�cy identyfikator VAO
	VAO();

	//��czy VBO z VAO za pomoc� okre�lonego uk�adu
	void LinkAttrib(VBO& VBO, GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void*offset);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
