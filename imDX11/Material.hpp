#pragma once

#include <Windows.h>
#include <memory>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "d3dutil.h"
#include "Texture.hpp"

class Material {
public:
	Material(aiMaterial * mat) {
		// load the diffuse texture
		if (mat->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path("Models/");
			aiString file;

			mat->GetTexture(aiTextureType_DIFFUSE, 0, &file);

			path.Append(file.C_Str());
			tex = std::make_shared<Texture>(path.C_Str());
		}

		// load the normal map texture
		if (mat->GetTextureCount(aiTextureType_NORMALS)) {
			aiString path("Models/");
			aiString file;

			mat->GetTexture(aiTextureType_NORMALS, 0, &file);
			path.Append(file.C_Str());

			normals = std::make_shared<Texture>(path.C_Str());
		}
	}

	void Release() {
		if (tex) { tex->Release(); }
		if (normals) { normals->Release(); }
	}

	void SetActive() {
		if (tex) { tex->SetActive(0); }
		if (normals) { normals->SetActive(1); }
	}

private:
	std::shared_ptr<Texture> tex;
	std::shared_ptr<Texture> normals;
};