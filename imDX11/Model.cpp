#include "Model.h"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

Model::Model() { }

Model::Model(const char * Filename) {
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(Filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (!scene) {
		MessageBox(0, L"Failed to load model", L"Error", MB_OK);
		exit(-1);
	}

	for (int m = 0; m < scene->mNumMaterials; m++) {
		materials.push_back(std::make_shared<Material>(scene->mMaterials[m]));
	}

	for (int m = 0; m < scene->mNumMeshes; m++) {
		auto mesh = scene->mMeshes[m];
		auto vertexCount = mesh->mNumVertices;
		auto indexCount = mesh->mNumFaces * 3;

		VertexData * vert = new VertexData[vertexCount];
		DWORD * idx = new DWORD[indexCount];

		for (int i = 0; i < vertexCount; i++) {
			auto pos = mesh->mVertices[i];
			auto tan = mesh->mTangents[i];
			auto binorm = mesh->mBitangents[i];

			auto norm = VECTOR3_ZERO;
			if (mesh->mNormals) {
				auto tmp = mesh->mNormals[i];
				norm = VECTOR3(tmp.x, tmp.y, tmp.z);
			}

			auto texcoord = VECTOR2_ZERO;
			if (mesh->mTextureCoords[0]) {
				auto tmp = mesh->mTextureCoords[0][i];
				texcoord = VECTOR2(tmp.x, tmp.y);
			}

			vert[i] = VertexData(VECTOR3(pos.x, pos.y, pos.z), norm, 
				VECTOR3(tan.x, tan.y, tan.z), VECTOR3(binorm.x, binorm.y, binorm.z), texcoord);
		}

		for (int i = 0; i < indexCount; i++) {
			auto face = mesh->mFaces[i / 3];
			idx[i] = (DWORD)face.mIndices[i % 3];
		}

		// create the mesh using the vertex & index buffers we just generated
		auto tmp = std::make_shared<Mesh>(vertexCount, indexCount);
		if (materials.size()) { tmp->SetMaterial(materials[mesh->mMaterialIndex]); }
		tmp->GenVertexBuffer(vert);
		tmp->GenIndexBuffer(idx);
		meshes.push_back(tmp);

		delete[] vert;
		delete[] idx;
	}
}

void Model::Release() {
	for (auto mesh : meshes) {
		mesh->Release();
	}

	for (auto mat : materials) {
		mat->Release();
	}
}

void Model::Draw() {
	for (auto mesh : meshes) {
		mesh->Draw();
	}
}