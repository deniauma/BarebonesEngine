#pragma once
#include <vector>

class Mesh
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	Mesh(float v[]);
	Mesh(std::vector<float>);
	~Mesh();
};

