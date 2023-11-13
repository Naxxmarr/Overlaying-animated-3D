#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Konstruktor, który buduje program Shader z 2 ró¿nych shaderów
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{

	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Utwórz Vertex Shader Object i uzyskaj jego referencjê
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Do³¹cz Ÿród³o Vertex Shader do obiektu Vertex Shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Utwórz obiekt Fragment Shader i uzyskaj jego odniesienie
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Do³¹cz Ÿród³o Fragment Shader do obiektu Fragment Shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);



	// Utwórz obiekt programu Shader i uzyskaj jego odniesienie(referencje)
	ID = glCreateProgram();
	// Do³¹cz Vertex i Fragment Shader do Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Po³¹cz wszystkie shadery razem w Shader Program
	glLinkProgram(ID);


	// Usuñ teraz bezu¿yteczne obiekty Vertex i Fragment Shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//aktywuj Shader Program
void Shader::Activate()
{
	glUseProgram(ID);

}

// usun Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);

}


