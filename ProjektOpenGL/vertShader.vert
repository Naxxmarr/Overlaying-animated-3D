#version 330 core

// Pozycje/Wsp�rz�dne
layout (location = 0) in vec3 aPos;

// Kolory
layout (location = 2) in vec3 aKolor;

// Wsp�rz�dne tekstury
layout (location = 3) in vec2 aTex;

// Normalne (niekoniecznie znormalizowane)
layout (location = 1) in vec3 aNormal;




// Wy�wietla kolor dla Fragment Shader
out vec3 color;

// Wyprowadza wsp�rz�dne tekstury do Fragment Shader
out vec2 texCoord;

// Wypisuje normalne dla Fragment Shader
out vec3 Normal;

// Wy�wietla aktualn� pozycj� dla Fragment Shader
out vec3 aktPozycja;


// Importuje macierz kamery z funkcji g��wnej
uniform mat4 camMatrix;

// Importuje macierz modelu z funkcji g��wnej
uniform mat4 model;



void main()
{

// oblicza aktualn� pozycj�
aktPozycja = vec3(model * vec4(aPos, 1.0f));

// Wy�wietla pozycje/wsp�rz�dne wszystkich wierzcho�k�w
gl_Position = camMatrix * vec4(aPos,1.0);
 
// Przypisuje kolory z danych wierzcho�k�w do �koloru�
color = aKolor;


// Przypisuje wsp�rz�dne tekstury z danych wierzcho�k�w do "texCoord"
texCoord = aTex;

//Przypisuje normal z Vertex Data do Normal
Normal = aNormal;
}