#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <d2d1.h>
#include <dwrite.h>

#include <chrono>
#include "ChiliTimer.h"


class Graphics
{
public:
	Graphics(HWND hwnd, int height, int width);
	~Graphics();
	void EndFrame();
	void BeginFrame();
	void Resize(HWND hwnd, int width, int height);
public:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	int                                                 width;
	int                                                 height;

	Microsoft::WRL::ComPtr<ID2D1RenderTarget>          d2RenderTarget;
	Microsoft::WRL::ComPtr< ID2D1SolidColorBrush>      SolidColorBrush;
	Microsoft::WRL::ComPtr< IDWriteTextFormat>         TextFormat;
	
private:
	ChiliTimer  timer;

	
};

