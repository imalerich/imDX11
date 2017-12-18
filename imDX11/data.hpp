// data.hpp
// Ian Malerich

#pragma once

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

#include <d3d11.h>
#include "glm/glm.hpp"

typedef glm::vec3 VECTOR3;
typedef glm::vec4 VECTOR4;
typedef glm::vec4 COLOR;

#define VECTOR3_ZERO VECTOR3(0.0f, 0.0f, 0.0f)
#define VECTOR3_ONE VECTOR3(1.0f, 1.0f, 1.0f)

#define VECTOR4_ZERO VECTOR3(0.0f, 0.0f, 0.0f, 0.0f)
#define VECTOR4_ONE VECTOR3(1.0f, 1.0f, 1.0f, 1.0f)

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
	VertexData(glm::vec3 Pos, glm::vec3 Norm, glm::vec4 Color) 
		: pos(Pos), norm(Norm), color(Color) { }

	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec4 color;
};

const D3D11_INPUT_ELEMENT_DESC layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const UINT numElements = ARRAYSIZE(layout);