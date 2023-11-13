#include "Mesh.h"


Mesh::Mesh(std::vector<Texture> textures) {
	this->textures = textures;

}
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();

	//Generuje Vertex Buffer Object i ³¹czy go z wierzcho³kami
	VBO VBO(vertices);
	//Generuje obiekt bufora elementu(element buffer object) i ³¹czy go z indeksami
	EBO EBO(indices);
	current_frame = 0;
	direction = 1;

	// £¹czy VBO z VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));


	//Od³¹czenie wszystkich, aby zapobiec ich przypadkowej modyfikacji
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{ 
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "pozycjaKamery"), camera.Pozycja.x, camera.Pozycja.y, camera.Pozycja.z);
	camera.Matrix(shader, "camMatrix");

	// Narysuj aktual mesha
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}
void Mesh::DrawAnimation(Shader& shader, Camera& camera, float DT)
{
	
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	//std::cout << current_frame << std::endl;


	if (czas > 0.1)
	{
		czas = 0;


		if (current_frame == 0)
		{
			direction = 1;
			current_frame += direction;
		}
		else if (current_frame < textures.size() - 1)
		{
			current_frame += direction;
		}
		else
		{
			direction = -1;
			current_frame += direction;
		}

	}
	else {
		czas+= DT;
	}
	textures[current_frame].texUnit(shader, "diffuse 0", 0);
	textures[current_frame].Bind();

	

	glUniform3f(glGetUniformLocation(shader.ID, "pozycjaKamery"), camera.Pozycja.x, camera.Pozycja.y, camera.Pozycja.z);
	camera.Matrix(shader, "camMatrix");

	// Narysuj aktual mesha
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	
}

//loader do modeli .obj
std::vector<Vertex>Mesh::loadOBJ(const char* file_name)
{
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face vectors
	std::vector<GLint> vertex_position_indicies;
	std::vector<GLint> vertex_texcoord_indicies;
	std::vector<GLint> vertex_normal_indicies;

	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Nie moze otworzyc pliku.";
	}

	while (std::getline(in_file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") 
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
					counter = 0;
			}
		}

	}

	vertices.resize(vertex_position_indicies.size(), Vertex());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
		vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
		vertices[i].texUV = vertex_texcoords[vertex_texcoord_indicies[i] - 1];

	}

	//DEBUG
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";

	Mesh::vertices = vertices;
	Mesh::indices = std::vector<GLuint>();

	VAO.Bind();

	//Generuje Vertex Buffer Object i ³¹czy go z wierzcho³kami
	VBO VBO(vertices);

	// £¹czy VBO z VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));


	//Od³¹czenie wszystkich, aby zapobiec ich przypadkowej modyfikacji
	VAO.Unbind();
	VBO.Unbind();

	return vertices;
}