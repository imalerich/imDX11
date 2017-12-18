#include "Model.h"

Model::Model() : vertexCount(0), indexCount(0) { }

Model::Model(size_t VertexCount, size_t IndexCount)
		: vertexCount(VertexCount), indexCount(IndexCount) {
}

Model::Model(const char * Filename) {
	// TODO
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
	Model model(4, 6);

	//
	// create the vertex buffer
	//

	VertexData v[] = {
		VertexData(VECTOR3(-Width/2.0f, -Height/2.0f, 0.5f), RED),
		VertexData(VECTOR3(-Width/2.0f,  Height/2.0f, 0.5f), GREEN),
		VertexData(VECTOR3( Width/2.0f,  Height/2.0f, 0.5f), BLUE),
		VertexData(VECTOR3( Width/2.0f, -Height/2.0f, 0.5f), WHITE),
	};

	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.ByteWidth = sizeof(VertexData) * model.vertexCount;
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));
	vBufferData.pSysMem = v;
	hr = device->CreateBuffer(&vBufferDesc, &vBufferData, &model.vertexBuffer);

	//
	// create the index buffer
	//

	DWORD i[] = {
		0, 1, 2, 0, 2, 3
	};

	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.ByteWidth = sizeof(DWORD) * model.indexCount;
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iInitData;
	iInitData.pSysMem = i;
	device->CreateBuffer(&iBufferDesc, &iInitData, &model.indexBuffer);

	return model;
}