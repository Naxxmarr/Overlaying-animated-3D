#version 330 core

// Pozycje/Wspó³rzêdne
layout (location = 0) in vec3 aPos;

// Kolory
layout (location = 2) in vec3 aKolor;

// Wspó³rzêdne tekstury
layout (location = 3) in vec2 aTex;

// Normalne (niekoniecznie znormalizowane)
layout (location = 1) in vec3 aNormal;




// Wyœwietla kolor dla Fragment Shader
out vec3 color;

// Wyprowadza wspó³rzêdne tekstury do Fragment Shader
out vec2 texCoord;

// Wypisuje normalne dla Fragment Shader
out vec3 Normal;

// Wyœwietla aktualn¹ pozycjê dla Fragment Shader
out vec3 aktPozycja;


// Importuje macierz kamery z funkcji g³ównej
uniform mat4 camMatrix;

// Importuje macierz modelu z funkcji g³ównej
uniform mat4 model;



void main()
{

// oblicza aktualn¹ pozycjê
aktPozycja = vec3(model * vec4(aPos, 1.0f));

// Wyœwietla pozycje/wspó³rzêdne wszystkich wierzcho³ków
gl_Position = camMatrix * vec4(aPos,1.0);
 
// Przypisuje kolory z danych wierzcho³ków do „koloru”
color = aKolor;


// Przypisuje wspó³rzêdne tekstury z danych wierzcho³ków do "texCoord"
texCoord = aTex;

//Przypisuje normal z Vertex Data do Normal
Normal = aNormal;
}