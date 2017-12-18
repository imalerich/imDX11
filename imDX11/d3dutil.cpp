// d3dutil.cpp
// Ian Malerich

#include "d3dutil.h"
#include "data.hpp"

HRESULT hr;
ID3D11Device * device;
IDXGISwapChain * SwapChain;
ID3D11DeviceContext * context;
ID3D11RenderTargetView * view;

ID3D11Buffer * vertexBuffer;
ID3D11VertexShader * vShader;
ID3D11PixelShader * pShader;
ID3D11InputLayout * vLayout;
ID3D10Blob * VS_Buffer;
ID3D10Blob * PS_Buffer;

bool InitD3D11(HINSTANCE hInstance) {
	//
	// Buffer Description
	//

	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.Height = SCREEN_H;
	bufferDesc.Width = SCREEN_W;

	//
	// Swap Chain Description
	//

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.Windowed = TRUE;

	// create the swap chain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, 
		NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, 
		&swapChainDesc, &SwapChain, &device, NULL, &context);

	// create the back buffer
	ID3D11Texture2D * backBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// create & set the render target
	hr = device->CreateRenderTargetView(backBuffer, NULL, &view);
	backBuffer->Release();
	context->OMSetRenderTargets(1, &view, NULL);

	return true;
}

void ReleaseObjects() {
	SwapChain->Release();
	context->Release();
	device->Release();
	view->Release();

	vertexBuffer->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	vShader->Release();
	pShader->Release();
	vLayout->Release();
}

bool InitScene() {
	//
	// create & activate the vertex & pixel shaders
	//

	hr = D3DX11CompileFromFile("shaders.hlsl", 0, 0, "vMain", "vs_5_0", 0, 0, 0, &VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile("shaders.hlsl", 0, 0, "pMain", "ps_5_0", 0, 0, 0, &PS_Buffer, 0, 0);

	hr = device->CreateVertexShader(VS_Buffer->GetBufferPointer(), 
		VS_Buffer->GetBufferSize(), NULL, &vShader);
	hr = device->CreatePixelShader(PS_Buffer->GetBufferPointer(), 
		PS_Buffer->GetBufferSize(), NULL, &pShader);

	context->VSSetShader(vShader, 0, 0);
	context->PSSetShader(pShader, 0, 0);

	//
	// create the vertex buffer
	//

	VertexData v[] = {
		VertexData(VECTOR3(0.0f, 0.5f, 0.5f), RED),
		VertexData(VECTOR3(0.0f, -0.5f, 0.5f), GREEN),
		VertexData(VECTOR3(-0.5f, -0.5f, 0.5f), BLUE)
	};

	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.ByteWidth = sizeof(VertexData) * 3;
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));
	vBufferData.pSysMem = v;
	hr = device->CreateBuffer(&vBufferDesc, &vBufferData, &vertexBuffer);

	//
	// set the active vertex buffer
	//

	UINT stride = sizeof(VertexData), offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	hr = device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vLayout);
	context->IASetInputLayout(vLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//
	// create the viewport
	//

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_W;
	viewport.Height = SCREEN_H;

	context->RSSetViewports(1, &viewport);

	return true;
}

void UpdateScene() {
	// TODO
}

void DrawScene() {
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	context->ClearRenderTargetView(view, bgColor);

	// draw the current active vertex buffer
	// using the currently active pixel & vertex shaders
	context->Draw(3, 0);

	SwapChain->Present(0, 0);
}