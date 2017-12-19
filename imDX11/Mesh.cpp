#include "Mesh.h"

Mesh::Mesh(size_t VertexCount, size_t IndexCount)
		: vertexCount(VertexCount), indexCount(IndexCount) { }

void Mesh::Release() {
	indexBuffer->Release();
	vertexBuffer->Release();
}

void Mesh::SetActiveBuffers() {
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	UINT stride = sizeof(VertexData), offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

void Mesh::Draw() {
	SetActiveBuffers();
	context->DrawIndexed(indexCount, 0, 0);
}

void Mesh::GenVertexBuffer(const void * data) {
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

void Mesh::GenIndexBuffer(const void * data) {
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