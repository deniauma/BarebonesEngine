#pragma once
#include <string>


class Shader
{
private:
	unsigned int id;

public:
	std::string _vertexShader;
	std::string _fragmentShader;

	Shader(std::string vertex, std::string fragment);
	~Shader();

	void use();
};

