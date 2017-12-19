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

	// TODO - Load more than one mesh per  model.
	for (int m = 0; m < scene->mNumMeshes; m++) {
		auto mesh = scene->mMeshes[m];
		auto vertexCount = mesh->mNumVertices;
		auto indexCount = mesh->mNumFaces * 3;

		VertexData * vert = new VertexData[vertexCount];
		DWORD * idx = new DWORD[indexCount];

		for (int i = 0; i < vertexCount; i++) {
			auto pos = mesh->mVertices[i];
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

			vert[i] = VertexData(VECTOR3(pos.x, pos.y, pos.z), norm, texcoord);
		}

		for (int i = 0; i < indexCount; i++) {
			auto face = mesh->mFaces[i / 3];
			idx[i] = (DWORD)face.mIndices[i % 3];
		}

		// create the mesh using the vertex & index buffers we just generated
		auto tmp = std::make_shared<Mesh>(vertexCount, indexCount);
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
}

void Model::Draw() {
	for (auto mesh : meshes) {
		mesh->Draw();
	}
}

Model Model::MakeSquare(float Width, float Height) {
	const VECTOR3 norm = VECTOR3(0.0f, 0.0f, -1.0f);
	VertexData v[] = {
		VertexData(VECTOR3(-Width/2.0f, -Height/2.0f, 0.5f), norm),
		VertexData(VECTOR3(-Width/2.0f,  Height/2.0f, 0.5f), norm),
		VertexData(VECTOR3( Width/2.0f,  Height/2.0f, 0.5f), norm),
		VertexData(VECTOR3( Width/2.0f, -Height/2.0f, 0.5f), norm),
	};

	DWORD i[] = {
		0, 1, 2, 0, 2, 3
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(4, 6);
	mesh->GenVertexBuffer(v);
	mesh->GenIndexBuffer(i);

	Model model;
	model.meshes.push_back(mesh);
	return model;
}