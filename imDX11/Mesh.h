#pragma once

#include <stdlib.h>
#include <memory>

#include "Material.hpp"
#include "d3dutil.h"

class Mesh {
public:
	Mesh(size_t VertexCount, size_t IndexCount);

	inline const size_t GetVertexCount() { return vertexCount;  }
	inline const size_t GetIndexCount() { return indexCount;  }
	inline const size_t GetFaceCount() { return indexCount / 3;  }

	inline void SetMaterial(std::shared_ptr<Material> Material) {
		material = Material;
	}

	/**
	 * Release all buffers stored by this mesh.
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
	 * Assumes vertexCount has bene set.
	 * Generates the vertexBuffer for this mesh.
	 */
	void GenVertexBuffer(const void * data);

	/**
	 * Assumes indexCount has bene set.
	 * Generates the indexBuffer for this mesh.
	 */
	void GenIndexBuffer(const void * data);
	
private:
	size_t vertexCount;
	size_t indexCount;

	ID3D11Buffer * indexBuffer;
	ID3D11Buffer * vertexBuffer;

	std::shared_ptr<Material> material;
};