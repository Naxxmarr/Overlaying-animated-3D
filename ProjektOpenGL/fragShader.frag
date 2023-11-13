#version 330 core
out vec4 FragColor;



// Importuje kolor z Vertex Shader
in vec3 color;

// Importuje wsp�rz�dne tekstury z Vertex Shader
in vec2 texCoord;

// Importuje normaln� z Vertex Shader
in vec3 Normal;

// Importuje bie��c� pozycj� z Vertex Shader
in vec3 aktPozycja;

// Pobiera jednostk� tekstury z funkcji g��wnej
uniform sampler2D diffuse0;

// Pobiera kolor �wiat�a z funkcji g��wnej
uniform vec4 kolorSwiatla;

// Pobiera pozycj� �wiat�a z funkcji g��wnej
uniform vec3 pozycjaSwiatla;

// Pobiera pozycj� kamery z funkcji g��wnej
uniform vec3 pozycjaKamery;

vec4 pointlight()
{
	vec3 lightWektor = pozycjaSwiatla - aktPozycja;
	float dist = length(lightWektor);
	float a = 3.0;
	float b = 0.7;
	float intensywnosc = 3.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;


	// diffuse lighting
    vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightWektor);
	float diffuse = max(dot(normal, lightDirection), 0.0f);


	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(pozycjaKamery - aktPozycja);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount + specularLight;

    return texture(diffuse0, texCoord) * kolorSwiatla * intensywnosc * (diffuse + ambient + specular);
}

void main()
{

    FragColor = pointlight();
}