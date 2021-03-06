// d3dutil.cpp
// Ian Malerich

#include "d3dutil.h"
#include "data.hpp"

HRESULT hr;
ID3D11Device * device;
IDXGISwapChain * SwapChain;
ID3D11DeviceContext * context;
ID3D11RenderTargetView * view;

ID3D11VertexShader * vShader;
ID3D11PixelShader * pShader;
ID3D11InputLayout * vLayout;
ID3D10Blob * VS_Buffer;
ID3D10Blob * PS_Buffer;

ID3D11DepthStencilView * depthView;
ID3D11Texture2D * depthBuffer;

ID3D11Buffer * cbPerObjectBuffer;
cbPerObject cbPerObj;

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

	// create the depth/stencil buffer
	D3D11_TEXTURE2D_DESC depthDesc;

	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.Height = SCREEN_H;
	depthDesc.Width = SCREEN_W;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.MiscFlags = 0;

	device->CreateTexture2D(&depthDesc, NULL, &depthBuffer);
	device->CreateDepthStencilView(depthBuffer, NULL, &depthView);
	context->OMSetRenderTargets(1, &view, depthView);

	return true;
}

void ReleaseObjects() {
	SwapChain->Release();
	context->Release();
	device->Release();
	view->Release();

	depthView->Release();
	depthBuffer->Release();

	VS_Buffer->Release();
	PS_Buffer->Release();

	vShader->Release();
	pShader->Release();
	vLayout->Release();

	cbPerObjectBuffer->Release();
}

bool InitScene() {
	//
	// create & activate the vertex & pixel shaders
	//

	ID3DBlob * error;
	hr = D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "vMain", "vs_5_0", 
		0, 0, 0, &VS_Buffer, &error, 0);
	if (error) { OutputDebugStringA((char*)error->GetBufferPointer()); exit(-1); }
	hr = D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "pMain", "ps_5_0", 
		0, 0, 0, &PS_Buffer, &error, 0);
	if (error) { OutputDebugStringA((char*)error->GetBufferPointer()); exit(-1); }

	hr = device->CreateVertexShader(VS_Buffer->GetBufferPointer(), 
		VS_Buffer->GetBufferSize(), NULL, &vShader);
	hr = device->CreatePixelShader(PS_Buffer->GetBufferPointer(), 
		PS_Buffer->GetBufferSize(), NULL, &pShader);

	context->VSSetShader(vShader, 0, 0);
	context->PSSetShader(pShader, 0, 0);

	// set the shader layout to render indexed triangles
	hr = device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vLayout);
	context->IASetInputLayout(vLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//
	// create the viewport
	//

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.Height = SCREEN_H;
	viewport.Width = SCREEN_W;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	context->RSSetViewports(1, &viewport);

	// create the matrix buffer to include with vertices
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObj);
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

	return true;
}

void ClearContext() {
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	context->ClearRenderTargetView(view, bgColor);
	context->ClearDepthStencilView(depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}