#include"Mesh.h"

const unsigned int width = 800;
const unsigned int height = 800;

Vertex vertices[] =

{ //         Koordynaty                 /       NORMAL                  /    Kolor                   /    TexCordy       //
	Vertex{glm::vec3(-12.0f, 0.0f,  12.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-12.0f, 0.0f, -12.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 10.0f)},
	Vertex{glm::vec3(12.0f, 0.0f, -12.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, 10.0f)},
	Vertex{glm::vec3(12.0f, 0.0f,  12.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, 0.0f)}
};

// Indeksy kolejności wierzchołków
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

//źródlo światla
Vertex lightVertices[] =
{
	Vertex{glm::vec3(-0.01f, -0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f, -0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f, -0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f, -0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f,  0.01f,  0.01f)},
	Vertex{glm::vec3(-0.01f,  0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f,  0.01f, -0.01f)},
	Vertex{glm::vec3(0.01f,  0.01f,  0.01f)}
};
GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Rafal_Kolda_Projekt", NULL, NULL);

	//sprawdzenie  bledu okna
	if (window == NULL)
	{
		std::cout << "Blad tworzenia okna" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	//do tekstur
	Texture textures[]
	{
		Texture("Trawa.jpg", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)

	};
	Texture textures2[]
	{
		Texture("tekstury/ognisko.jpg", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	Texture textures3[]
	{
		Texture("tekstury/fabric.jpg", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	Texture textures4[]
	{
		Texture("tekstury/rock.jpg", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	Texture textures5[]
	{
		Texture("tekstury/drzewo.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	Texture textures6[]
	{
		Texture("tekstury/lampa.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	Texture textures7[]
	{
		Texture("tekstury/trawaAnimacje/trawa1.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("tekstury/trawaAnimacje/trawa2.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("tekstury/trawaAnimacje/trawa3.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("tekstury/trawaAnimacje/trawa4.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("tekstury/trawaAnimacje/trawa5.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("tekstury/trawaAnimacje/trawa6.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	

	//Shadery
	Shader shaderProgram("vertShader.vert","fragShader.frag");
	Shader trawaProgram("vertShader.vert", "trawa.frag");


	// vektory dla mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector <Texture> tex2(textures2, textures2 + sizeof(textures2) / sizeof(Texture));
	std::vector <Texture> tex3(textures3, textures3 + sizeof(textures3) / sizeof(Texture));
	std::vector <Texture> tex4(textures4, textures4 + sizeof(textures4) / sizeof(Texture));
	std::vector <Texture> tex5(textures5, textures5 + sizeof(textures5) / sizeof(Texture));
	std::vector <Texture> tex6(textures6, textures6 + sizeof(textures6) / sizeof(Texture));
	std::vector <Texture> tex7(textures7, textures7 + sizeof(textures7) / sizeof(Texture));


	// floor mesh
	Mesh floor(verts, ind, tex);

	//obiekty
	Mesh ognisko = Mesh(tex2);
	ognisko.loadOBJ("Modele/ognisko.obj");

	Mesh tent = Mesh(tex3);
	tent.loadOBJ("Modele/tent.obj");
	
	Mesh garnek = Mesh(tex4);
	garnek.loadOBJ("Modele/garnek.obj");

	Mesh kamienie = Mesh(tex4);
	kamienie.loadOBJ("Modele/kamienie.obj");

	Mesh drzewo = Mesh(tex5);
	drzewo.loadOBJ("Modele/drzewa2.obj");

	Mesh lampa = Mesh(tex6);
	lampa.loadOBJ("Modele/lampa.obj");

	Mesh trawa = Mesh(tex7);
	trawa.loadOBJ("Modele/tr.obj");


	//shader dla swiatla
	Shader lightShader("swiatlo.vert", "swiatlo.frag");

	// Przechowuj dane w wektorach 
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	// stworz light mesh
	Mesh light(lightVerts, lightInd, tex);

	// do operowania swiatlem
	glm::vec4 kolorSwiatla = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 pozycjaSwiatla = glm::vec3(-0.61f, 0.1f, -0.51f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, pozycjaSwiatla);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "kolorSwiatla"), kolorSwiatla.x, kolorSwiatla.y, kolorSwiatla.z, kolorSwiatla.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "kolorSwiatla"), kolorSwiatla.x, kolorSwiatla.y, kolorSwiatla.z, kolorSwiatla.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "pozycjaSwiatla"), pozycjaSwiatla.x, pozycjaSwiatla.y, pozycjaSwiatla.z);

	trawaProgram.Activate();
	glUniform4f(glGetUniformLocation(trawaProgram.ID, "kolorSwiatla"), kolorSwiatla.x, kolorSwiatla.y, kolorSwiatla.z, kolorSwiatla.w);
	glUniform3f(glGetUniformLocation(trawaProgram.ID, "pozycjaSwiatla"), pozycjaSwiatla.x, pozycjaSwiatla.y, pozycjaSwiatla.z);



	//Włącza bufor głębokości
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 5.0f));


	float currTime = 0,dt = 0,lastTime = 0;


	while (!glfwWindowShouldClose(window)) {

		// kolor tła
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currTime = static_cast<float>(glfwGetTime());
		dt = currTime - lastTime;
		lastTime = currTime;


		// Obsługuje wejścia kamery
		camera.Keyboard(window);

		// Aktualizuje i eksportuje macierz kamery do Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
	
		trawa.DrawAnimation(trawaProgram, camera,dt);
		lampa.Draw(shaderProgram, camera);
		ognisko.Draw(shaderProgram, camera);
		floor.Draw(shaderProgram, camera);
		tent.Draw(shaderProgram, camera);
		garnek.Draw(shaderProgram, camera);
		kamienie.Draw(shaderProgram, camera);
		drzewo.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);



		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	shaderProgram.Delete();
	lightShader.Delete();
	trawaProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}