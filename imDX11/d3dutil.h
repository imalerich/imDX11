// d3dutil.h
// Ian Malerich

#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

#include <Windows.h>

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX11async.h>

#include "data.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef M_PI
#define M_PI 3.14159265f
#endif

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

extern ID3D11VertexShader * vShader;
extern ID3D11PixelShader * pShader;
extern ID3D11InputLayout * vLayout;
extern ID3D10Blob * VS_Buffer;
extern ID3D10Blob * PS_Buffer;

extern ID3D11DepthStencilView * depthView;
extern ID3D11Texture2D * depthBuffer;

extern ID3D11Buffer * cbPerObjectBuffer;
extern cbPerObject cbPerObj;

extern ID3D11Buffer * indexBuffer;
extern ID3D11Buffer * vertexBuffer;

//
// Utility Functions
//

bool InitD3D11(HINSTANCE hInstance);
void ReleaseObjects();

bool InitScene();
void UpdateScene();
void DrawScene();
void buildWVP();