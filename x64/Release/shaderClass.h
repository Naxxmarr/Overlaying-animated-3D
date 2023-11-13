#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
std::string get_file_contents(const char* filename);
class Shader {
public:

	//Identyfikator referencyjny Shader Program
	GLuint ID;

	// Konstruktor, kt�ry buduje Shader Program z 2 r�nych shader�w
	Shader(const char* vertexFile, const char* fragmentFile);

	//aktywuj Shader Program
	void Activate();

	//usun Shader Program
	void Delete();


};


#endif