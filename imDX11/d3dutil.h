// d3dutil.h
// Ian Malerich

#pragma once
#pragma comment(lib, "d3d11.lib")

#include <Windows.h>
#include <d3d11.h>

#define SCREEN_W 800
#define SCREEN_H 600

extern HWND hwnd;

extern ID3D11Device * device;
extern IDXGISwapChain * SwapChain;
extern ID3D11DeviceContext * context;
extern ID3D11RenderTargetView * view;

bool InitD3D11(HINSTANCE hInstance);
void ReleaseObjects();

bool InitScene();
void UpdateScene();
void DrawScene();