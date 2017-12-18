// d3dutil.h
// Ian Malerich

#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include <Windows.h>

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX11async.h>

#define SCREEN_W 800
#define SCREEN_H 600

extern HWND hwnd;
extern HRESULT hr;

//
// Device & Context
//

extern ID3D11Device * device;
extern IDXGISwapChain * SwapChain;
extern ID3D11DeviceContext * context;
extern ID3D11RenderTargetView * view;

//
// Buffers
//

extern ID3D11Buffer * indexBuffer;
extern ID3D11Buffer * vertexBuffer;
extern ID3D11VertexShader * vShader;
extern ID3D11PixelShader * pShader;
extern ID3D11InputLayout * vLayout;
extern ID3D10Blob * VS_Buffer;
extern ID3D10Blob * PS_Buffer;

//
// Utility Functions
//

bool InitD3D11(HINSTANCE hInstance);
void ReleaseObjects();

bool InitScene();
void UpdateScene();
void DrawScene();