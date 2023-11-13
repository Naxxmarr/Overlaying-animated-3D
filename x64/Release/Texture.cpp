#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
	// Przypisuje typ tekstury do obiektu tekstury
	type = texType;

	// Przechowuje szerokoœæ, wysokoœæ i liczbê kana³ów kolorów obrazu
	int widthImg, heightImg, numColCh;
	// Odwraca obraz tak, aby wygl¹da³ praw¹ stron¹ do góry
	stbi_set_flip_vertically_on_load(true);
	// Czyta obraz z pliku i przechowuje go w bajtach
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 4);

	// Generuje obiekt tekstury OpenGL
	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// Konfiguruje typ algorytmu, który jest u¿ywany do zmniejszania lub powiêkszania obrazu
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Konfiguruje sposób powtarzania(repeat) tekstury (jeœli w ogóle siê powtarza)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Przypisuje obraz do obiektu tekstury OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Pobiera lokalizacjê uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader musi byæ aktywowany przed zmian¹ wartoœci uniformu
	shader.Activate();
	// Ustawia wartoœæ uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}