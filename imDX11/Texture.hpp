#pragma once

#include "d3dutil.h"

class Texture {
public:
	Texture(const char * Filename) : texture(NULL) {
		hr = D3DX11CreateShaderResourceViewFromFileA(device, Filename, NULL, NULL, &texture, NULL);
		if (!texture) {
			MessageBox(0, L"Failed to load texture", L"Error", MB_OK);
			exit(-1);
		}

		D3D11_SAMPLER_DESC sDesc;
		ZeroMemory(&sDesc, sizeof(sDesc));
		sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sDesc.MinLOD = 0;
		sDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = device->CreateSamplerState(&sDesc, &state);
	}

	void SetActive(UINT slot) {
		context->PSSetShaderResources(slot, 1, &texture);
		context->PSSetSamplers(slot, 1, &state);
	}

	void Release() {
		texture->Release();
		state->Release();
	}

private:
	ID3D11ShaderResourceView * texture;
	ID3D11SamplerState * state;
};