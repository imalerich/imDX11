#pragma once

#include <stdlib.h>
#include <memory>
#include <vector>

#include "Material.hpp"
#include "d3dutil.h"
#include "Mesh.h"

class Model {
public:
	Model();
	Model(const char * Filename);

	/**
	 * Release all buffers stored by this model.
	 */
	void Release();

	/**
	 * Loops through each mesh in the model, 
	 * and Draw's them to the current DX11 
	 * graphics context.
	 */
	void Draw();

private:
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<std::shared_ptr<Material>> materials;
};