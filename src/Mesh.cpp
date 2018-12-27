#include "Mesh.h"
#include <iterator>


Mesh::Mesh(float v[])
{
	vertices = std::vector<float>(v, v + sizeof(v) / sizeof(v[0]));
}

Mesh::Mesh(std::vector<float> v): vertices(v)
{
}


Mesh::~Mesh()
{
}
