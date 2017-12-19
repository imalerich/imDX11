// data.hpp
// Ian Malerich

#pragma once

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

#include <d3d11.h>
#include <glm/glm.hpp>

typedef glm::vec2 VECTOR2;
typedef glm::vec3 VECTOR3;
typedef glm::vec4 VECTOR4;
typedef glm::vec4 COLOR;

#define VECTOR2_ZERO VECTOR2(0.0f, 0.0f)
#define VECTOR2_ONE VECTOR2(1.0f, 1.0f)

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
	glm::mat4 IW;
};

class VertexData {
public:
	VertexData() : pos(VECTOR3_ZERO), norm(VECTOR3_ZERO), texcoord(VECTOR2_ZERO) { }
	VertexData(glm::vec3 Pos, glm::vec3 Norm, glm::vec3 Tan, glm::vec3 Binorm, 
			glm::vec2 Texcoord = VECTOR2_ZERO) 
		: pos(Pos), norm(Norm), tan(Tan), binorm(Binorm), texcoord(Texcoord) { }

	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 tan;
	glm::vec3 binorm;
	glm::vec2 texcoord;
};

const D3D11_INPUT_ELEMENT_DESC layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const UINT numElements = ARRAYSIZE(layout);