#pragma once

#include <glad/gl.h>
#include <iostream>

class Renderer {

private:
	void createShaders();
	GLuint createShader(const char** shader, GLenum type);
	void createProgram();
	void createVertexArray();

	GLuint programID;
	GLuint fragmentID;
	GLuint vertexID;

	GLuint vertexArray;
	GLuint buffer;

	int success;
	char infoLog[512];

	const char* vertexShader =
		"#version 400 core\n"
		"layout (location = 0) in vec2 vertexPos;"
		"void main(){"
		"gl_Position = vec4(vertexPos, 0.0, 1.0);"
		"}";

	const char* fragmentShader =
		"#version 400 core\n"
		"uniform int[96] array;"
		"out vec4 fragment;"

		"void main()"
		"{"
		"int x = int(gl_FragCoord.x) / 10;"
		"int y = int(gl_FragCoord.y) / 10;"

		"uint colorFromArray = array[y*2+x/32];"
		"uint mask = 1;"
		"mask <<= x%32;"
		"vec3 color = vec3(colorFromArray & mask);"
		"fragment = vec4(color, 1.0);"
		"}";

	float data[12] = { 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f };

public: 
	Renderer();
	void render(int* array=nullptr);
	~Renderer();
};


