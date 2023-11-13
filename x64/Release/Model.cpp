#include "Mesh.cpp"

using namespace std;

class Light : public Mesh
{
public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	VertexArray vertexMeshArray;
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	mat4 modelMatrix = mat4(1.0f);

	Light(const char* filename, vector<Texture> newtextures) {
		this->vertexMeshArray.Bind();
		this->textures = newtextures;
		this->vertices = loadOBJ(filename);
		VertexBuffer vertexMeshBuffer(this->vertices);

		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		this->vertexMeshArray.Unbind();
		vertexMeshBuffer.Unbind();
	}

	Light(vector <Vertex>& vertices, vector <Texture>& textures) {

		this->vertices = vertices;
		this->textures = textures;

		this->vertexMeshArray.Bind();

		VertexBuffer vertexMeshBuffer(vertices);

		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		this->vertexMeshArray.LinkAttribute(vertexMeshBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		this->vertexMeshArray.Unbind();
		vertexMeshBuffer.Unbind();
	}

	vector<Vertex> loadOBJ(const char* file_name)
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

		//File open error check
		if (!in_file.is_open())
		{
			throw "ERROR::OBJLOADER::Could not open file.";
		}

		//Read one line at a time
		while (std::getline(in_file, line))
		{
			//Get the prefix of the line
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
			else if (prefix == "v") //Vertex position
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
					//Pushing indices into correct arrays
					if (counter == 0)
						vertex_position_indicies.push_back(temp_glint);
					else if (counter == 1)
						vertex_texcoord_indicies.push_back(temp_glint);
					else if (counter == 2)
						vertex_normal_indicies.push_back(temp_glint);

					//Handling characters
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

					//Reset the counter
					if (counter > 2)
						counter = 0;
				}
			}
			else
			{

			}
		}

		//Build final vertex array (mesh)
		vertices.resize(vertex_position_indicies.size(), Vertex());

		//Load in all indices
		for (size_t i = 0; i < vertices.size(); ++i)
		{
			vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
			vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
			vertices[i].textureUv = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		}

		//DEBUG
		std::cout << "Nr of vertices: " << vertices.size() << "\n";

		//Loaded success
		std::cout << "OBJ file loaded!" << "\n";
		return vertices;
	}

	void DrawMesh(ShaderUseClass& shader, Camera& camera) {
		shader.UseShader();
		this->vertexMeshArray.Bind();
		if (!this->textures.empty()) {
			GLuint textureDiffuseNumber = 0;
			GLuint textureSpecularNumber = 0;

			for (int i = 0; i < textures.size(); i++) {
				string textureName;
				string textureType = textures[i].type;
				if (textureType == "Diffuse") {
					textureName = to_string(textureDiffuseNumber++);
				}
				else if (textureType == "Specular") {
					textureName = to_string(textureSpecularNumber++);
				}
				textures[i].textureUnit(shader, ("fragTexture" + textureType + textureName).c_str(), i);
				textures[i].Bind();
			}
		}
		glUniform3f(glGetUniformLocation(shader.shaderID, "fragCameraPosition"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "vertCamMatrix");
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}

	void SetUniform(ShaderUseClass& shader, vec4 lightColor, vec3 lightPos) {
		this->modelMatrix = translate(modelMatrix, position);
		shader.UseShader();
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderID, "vertModel"), 1, GL_FALSE, value_ptr(this->modelMatrix));
		glUniform4f(glGetUniformLocation(shader.shaderID, "fragLightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shader.shaderID, "fragLightPos"), lightPos.x, lightPos.y, lightPos.z);

	}
};