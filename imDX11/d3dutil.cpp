// d3dutil.cpp
// Ian Malerich

#include "d3dutil.h"

ID3D11Device * device;
IDXGISwapChain * SwapChain;
ID3D11DeviceContext * context;
ID3D11RenderTargetView * view;

bool InitD3D11(HINSTANCE hInstance) {
	HRESULT hr;

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
	device->Release();
	context->Release();
}

bool InitScene() {
	return true;
}

void UpdateScene() {
	// TODO
}

void DrawScene() {
	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;

	r += 0.00003f;
	g += 0.00004f;
	b += 0.00005f;

	if (r > 1.0f) {
		r = g = b = 0.0f;
	}

	const float bgColor[] = { r, g, b, 1.0f };
	context->ClearRenderTargetView(view, bgColor);
	SwapChain->Present(0, 0);
}