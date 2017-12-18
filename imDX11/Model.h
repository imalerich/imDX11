#pragma once

#include <stdlib.h>
#include "d3dutil.h"

class Model {
public:
	Model();
	Model(size_t VertexCount, size_t IndexCount);
	Model(const char * Filename);

	inline const size_t GetVertexCount() { return vertexCount;  }
	inline const size_t GetIndexCount() { return indexCount;  }
	inline const size_t GetFaceCount() { return indexCount / 3;  }

	/**
	 * Release all buffers stored by this model.
	 */
	void Release();

	/**
	 * Set this models vertex and index buffers as 
	 * active in the current context.
	 */
	void SetActiveBuffers();

	/**
	 * Draw's this model to the current context.
	 * This method will call SetActiveBuffers() on this
	 * model, therefore that function does NOT need to be 
	 * called before a call to Draw().
	 */
	void Draw();

	/**
	 * Creates a square mesh centered around the origin
	 * with the given width and height.
	 */
	static Model MakeSquare(float W, float H);

private:
	size_t vertexCount;
	size_t indexCount;

	ID3D11Buffer * indexBuffer;
	ID3D11Buffer * vertexBuffer;

	void GenVertexBuffer(const void * data);
	void GenIndexBuffer(const void * data);
};