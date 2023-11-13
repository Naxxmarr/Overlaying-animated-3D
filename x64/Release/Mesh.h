
#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	int current_frame;
	int direction;
	float czas;

	VAO VAO;
	Mesh(std::vector<Texture> textures);
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
	void DrawAnimation(Shader& shader, Camera& camera,float DT);

	std::vector<Vertex> loadOBJ(const char* file_name);


};

#endif
