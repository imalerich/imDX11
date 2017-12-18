// data.hpp
// Ian Malerich

#pragma once

#include <d3d11.h>
#include "glm/glm.hpp"

#define VECTOR3 glm::vec3
#define COLOR glm::vec4

#define WHITE COLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK COLOR(0.0f, 0.0f, 0.0f, 1.0f)

#define DGRAY COLOR(0.2f, 0.2f, 0.2f, 1.0f)
#define NGRAY COLOR(0.5f, 0.5f, 0.5f, 1.0f)
#define LGRAY COLOR(0.8f, 0.8f, 0.8f, 1.0f)

#define RED COLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN COLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE COLOR(0.0f, 0.0f, 1.0f, 1.0f)

#define MAGENTA COLOR(1.0f, 0.0f, 1.0f, 1.0f)
#define YELLOW COLOR(1.0f, 1.0f, 0.0f, 1.0f)
#define CYAN COLOR(0.0f, 1.0f, 1.0f, 1.0f)

class cbPerObject {
public:
	glm::mat4 WVP;
};

class VertexData {
public:
	VertexData() : pos(0.0f, 0.0f, 0.0f) { }
	VertexData(glm::vec3 Pos, glm::vec4 Color) : pos(Pos), color(Color) { }
	VertexData(float x, float y, float z, float r, float g, float b) 
		: pos(x, y, z), color(r, g, b, 1.0) { }

	glm::vec3 pos;
	glm::vec4 color;
};

const D3D11_INPUT_ELEMENT_DESC layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const UINT numElements = ARRAYSIZE(layout);