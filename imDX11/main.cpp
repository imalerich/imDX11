// main.cpp
// Ian Malerich

#include <Windows.h>
#include "d3dutil.h"

#define WIN32_LEAN_AND_MEAN

HWND hwnd = NULL;
LPCTSTR WndClassName = "firstwindow";

int MessageLoop();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool InitWindow(HINSTANCE hInstance, int ShowWnd, unsigned width, unsigned height, bool windowed);

int WINAPI WinMain(
		HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nShowCmd) {
	if (!InitWindow(hInstance, nShowCmd, SCREEN_W, SCREEN_H, true)) {
		MessageBox(0, "Window Initialization - Failed", "Error", MB_OK);
		return -1;
	}

	if (!InitD3D11(hInstance)) {
		MessageBox(0, "Direct3D Initialization - Failed", "Error", MB_OK);
		return -2;
	}

	if (!InitScene()) {
		MessageBox(0, "Scene Initialization - Failed", "Error", MB_OK);
		return -3;
	}

	MessageLoop();
	ReleaseObjects();
	return 0;
}

int MessageLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true) {
		// process windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) { break; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		} else { // run game code
			UpdateScene();
			DrawScene();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN: 
		if (wParam == VK_ESCAPE) {
			if (MessageBox(0, "Are you sure you want to exit?", "Exit", 
					MB_YESNO | MB_ICONQUESTION) == IDYES) {
				DestroyWindow(hwnd);
			}

			return 0;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool InitWindow(HINSTANCE hInstance, int ShowWnd, unsigned width, unsigned height, bool windowed) {
	// we need to give windows a bunch of information about the windo we want to create
	WNDCLASSEX wc;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = WndClassName;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(NULL, WndClassName, "imDX11", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_W, SCREEN_H, NULL, NULL, hInstance, NULL);

	if (!hwnd) {
		MessageBox(NULL, "Error - Failed to create window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);
	return true;
}