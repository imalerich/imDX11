#include "Model.h"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

Model::Model() : vertexCount(0), indexCount(0) { }

Model::Model(size_t VertexCount, size_t IndexCount)
		: vertexCount(VertexCount), indexCount(IndexCount) {
}

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
	aiMesh * mesh = scene->mMeshes[0];
	vertexCount = mesh->mNumVertices;
	indexCount = mesh->mNumFaces * 3;

	VertexData * vert = new VertexData[vertexCount];
	DWORD * idx = new DWORD[indexCount];

	for (int i = 0; i < vertexCount; i++) {
		auto pos = mesh->mVertices[i];
		vert[i] = VertexData(VECTOR3(pos.x, pos.y, pos.z), WHITE);
	}

	for (int i = 0; i < indexCount; i++) {
		auto face = mesh->mFaces[i / 3];
		idx[i] = (DWORD)face.mIndices[i % 3];
	}

	GenVertexBuffer(vert);
	GenIndexBuffer(idx);
	delete[] vert;
	delete[] idx;
}

void Model::Release() {
	indexBuffer->Release();
	vertexBuffer->Release();
}

void Model::SetActiveBuffers() {
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	UINT stride = sizeof(VertexData), offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

void Model::Draw() {
	SetActiveBuffers();
	context->DrawIndexed(indexCount, 0, 0);
}

Model Model::MakeSquare(float Width, float Height) {
	VertexData v[] = {
		VertexData(VECTOR3(-Width/2.0f, -Height/2.0f, 0.5f), RED),
		VertexData(VECTOR3(-Width/2.0f,  Height/2.0f, 0.5f), GREEN),
		VertexData(VECTOR3( Width/2.0f,  Height/2.0f, 0.5f), BLUE),
		VertexData(VECTOR3( Width/2.0f, -Height/2.0f, 0.5f), WHITE),
	};

	DWORD i[] = {
		0, 1, 2, 0, 2, 3
	};

	Model model(4, 6);
	model.GenVertexBuffer(v);
	model.GenIndexBuffer(i);
	return model;
}

void Model::GenVertexBuffer(const void * data) {
	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.ByteWidth = sizeof(VertexData) * vertexCount;
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));
	vBufferData.pSysMem = data;
	hr = device->CreateBuffer(&vBufferDesc, &vBufferData, &vertexBuffer);
}

void Model::GenIndexBuffer(const void * data) {
	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.ByteWidth = sizeof(DWORD) * indexCount;
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iInitData;
	iInitData.pSysMem = data;
	device->CreateBuffer(&iBufferDesc, &iInitData, &indexBuffer);
}