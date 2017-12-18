#pragma once

class Vector4 {
public:
	Vector4(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f) {
		x = X; y = Y; z = Z; w = W;
	}

	float x;
	float y;
	float z;
	float w;
};

typedef class VertexData {
public:
	VertexData(Vector4 Pos = Vector4(), Vector4 Color = Vector4()) {
		pos = Pos;
		color = Color;
	}

	Vector4 pos;
	Vector4 color;
} vertexData;