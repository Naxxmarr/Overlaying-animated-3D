#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 pozycja)
{
	Camera::width = width;
	Camera::height = height;
	Pozycja = pozycja;
}

void Camera::updateMatrix(float FOVdeg, float blisPlan, float dalPlan)
{
	// Inicjuje macierze
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// kamera patrzy we w³aœciwym kierunku z w³aœciwej pozycji
	view = glm::lookAt(Pozycja, Pozycja + Orientacja, Up);

	// perspektywa
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, blisPlan, dalPlan);

	cameraMatrix = projection * view;

}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Keyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Pozycja += speed * Orientacja;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Pozycja += speed * -glm::normalize(glm::cross(Orientacja, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Pozycja += speed * -Orientacja;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Pozycja += speed * glm::normalize(glm::cross(Orientacja, Up));
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//schowanie kursora myszki
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		// zeby przy pierwszym kliku nie przeskakiwala kamera
		if (pierwszyKlik)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			pierwszyKlik = false;
		}
		
		// do przechowywania wsporzednych
		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = czulosc * (float)(mouseY - (height / 2)) / height;
		float rotY = czulosc * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientacja = glm::rotate(Orientacja, glm::radians(-rotX), glm::normalize(glm::cross(Orientacja, Up)));

		
		if (abs(glm::angle(newOrientacja, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientacja = newOrientacja;
		}

		// obracanie lewo prawo orientacja
		Orientacja = glm::rotate(Orientacja, glm::radians(-rotY), Up);

		//kursor na srodku ekranu
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		pierwszyKlik = true;
	}
}
