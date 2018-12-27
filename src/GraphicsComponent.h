#pragma once
#include "BBwindow.h"
#include "Mesh.h"
#include "Shader.h"

class GraphicsComponent
{
public:
	Mesh* mesh;
	Shader* shader;

	GraphicsComponent();
	~GraphicsComponent();

	void setMesh(Mesh m);
	void setShader(Shader s);
	void update();
};

