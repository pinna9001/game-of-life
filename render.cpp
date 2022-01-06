#include "./render.h"


void Renderer::createShaders() 
{
	vertexID = createShader(&vertexShader, GL_VERTEX_SHADER);
	fragmentID = createShader(&fragmentShader, GL_FRAGMENT_SHADER);
}

GLuint Renderer::createShader(const char** shader, GLenum type) 
{
	GLuint shaderID = glCreateShader(type);

	glShaderSource(shaderID, 1, shader, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}

void Renderer::createProgram()
{
	programID = glCreateProgram();

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	glUseProgram(programID);
}

void Renderer::createVertexArray() 
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::Renderer() 
{
	createShaders();
	createProgram();
	createVertexArray();
}

Renderer::~Renderer() 
{
	glUseProgram(0);

	glBindVertexArray(0);

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	glDeleteProgram(programID);

	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &buffer);
}

void Renderer::render(int* array)
{

	glUniform1iv(glGetUniformLocation(programID, "array"), 96, array);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glBindVertexArray(vertexArray);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
}
