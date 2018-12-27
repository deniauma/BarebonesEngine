#include "GraphicsComponent.h"



GraphicsComponent::GraphicsComponent()
{
}


GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::setMesh(Mesh m)
{
	mesh = new Mesh(m.vertices);
}

void GraphicsComponent::setShader(Shader s)
{
	shader = new Shader(s._vertexShader, s._fragmentShader);
}

void GraphicsComponent::update()
{
}
