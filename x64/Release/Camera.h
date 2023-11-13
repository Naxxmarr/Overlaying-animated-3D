#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>
#include"shaderClass.h"

class Camera
{
public:
	// wektory do kamery
	glm::vec3 Pozycja;
	glm::vec3 Orientacja = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// do zapobiegania przeskakiwania kamery przy pierwszym kliku
	bool pierwszyKlik = true;

	int width;
	int height;

	float speed = 0.1f;
	float czulosc = 100.0f;

	// konstruktor kamery
	Camera(int width, int height, glm::vec3 pozycja);

	void updateMatrix(float FOVdeg, float blisPlan, float dalPlan);

	// Eksportuje macierz kamery
	void Matrix(Shader& shader, const char* uniform);

	//camera inputs
	void Keyboard(GLFWwindow* window);
};
#endif