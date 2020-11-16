#include "TriangleFractal.h"
#include <math.h>
using namespace std;
using namespace Microsoft::WRL;

int TriangleFractal::iteration = 0;

TriangleFractal::TriangleFractal(Vertex T, Vertex BL, Vertex BR, Graphics* gfx)
	:
	gfx(gfx)
{
	HasChildren = false;
	iteration++;


	std::vector<Point> Points;
	
	Points.push_back(TriangleFractal::Point{ (float)T.X, (float)T.Y, 1.0f, 1.0f, 1.0f });
	Points.push_back(TriangleFractal::Point{ (float)BR.X, (float)BR.Y, 1.0f, 1.0f, 1.0f });
	Points.push_back(TriangleFractal::Point{ (float)BL.X, (float)BL.Y, 1.0f, 1.0f, 1.0f });
	Points.push_back(TriangleFractal::Point{ (float)T.X, (float)T.Y, 1.0f, 1.0f, 1.0f });

	HRESULT hr;

	unsigned int lol = Points.size() * sizeof(TriangleFractal::Point);
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = Points.size() * sizeof(TriangleFractal::Point);
	bd.StructureByteStride = sizeof(TriangleFractal::Point);
	D3D11_SUBRESOURCE_DATA sbd = {};
	sbd.pSysMem = Points.data();
	gfx->pDevice->CreateBuffer(&bd, &sbd, &pVertexBuffer);

	ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"TriangleVS.cso", &pBlob);
	hr = gfx->pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	const D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	gfx->pDevice->CreateInputLayout(ied, std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	D3DReadFileToBlob(L"TrianglePS.cso", &pBlob);
	hr = gfx->pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);


	vp.Width = gfx->width;
	vp.Height = gfx->height;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}

void TriangleFractal::Draw() const
{

	const UINT stride = sizeof(TriangleFractal::Point);
	const UINT offset = 0u;


	gfx->pImmediateContext->IASetInputLayout(pInputLayout.Get());
	gfx->pImmediateContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	gfx->pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	gfx->pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	gfx->pImmediateContext->OMSetRenderTargets(1, gfx->pRenderTargetView.GetAddressOf(), nullptr);
	gfx->pImmediateContext->RSSetViewports(1, &vp);
	gfx->pImmediateContext->Draw(4, 0u);
}

void TriangleFractal::CreateChildren()
{
	/*if(!HasChildren)
		{
		Vertex MidLT = (BotomLeft + Top) / 2;
		Vertex MidLR = (BotomLeft + BottomRight) / 2;
		Vertex MidTR = (Top + BottomRight) / 2;
		Children.push_back(TriangleFractal(MidLT ,BotomLeft, MidLR));
		Children.push_back(TriangleFractal(MidTR, MidLR, BottomRight));
		Children.push_back(TriangleFractal(Top, MidLT, MidTR));
		iteration++;
		HasChildren = true;
		}
	else
	{
		for (auto& t : Children)
		{
			t.CreateChildren();
		}
	}*/
}

void TriangleFractal::Control(Window* wnd)
{
	/*while (!wnd->IsKeyboardEventEmpty())
	{
		const auto e = wnd->ReadKeyEvent();
		if (e.Code == 'E' && e.Type == Window::KeyEvent::Event::Press)
		{
			CreateChildren();
		}
		if (e.Code == 'W' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale(Vertex{ 1.1, 1.1 });
		}
		if (e.Code == 'S' && e.Type == Window::KeyEvent::Event::Press)
		{
			Scale(Vertex{ 0.9, 0.9 });
		}
		if (e.Code == VK_UP && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ 0,-3 });
		}
		if (e.Code == VK_DOWN && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ 0, 3 });
		}
		if (e.Code == VK_LEFT && e.Type == Window::KeyEvent::Event::Press)
		{

			Translation(Vertex{ -3,0 });
		}
		if (e.Code == VK_RIGHT && e.Type == Window::KeyEvent::Event::Press)
		{
			Translation(Vertex{ 3, 0 });
		}

	}*/
}

void TriangleFractal::Scale(Vertex Scalar)
{


	/*BottomRight *= Scalar;
	BotomLeft *= Scalar;
	Top *= Scalar;

	for (auto& t : Children)
	{
		t.Scale(Scalar);
	}*/
}

void TriangleFractal::Translation(Vertex Trans)
{
	/*BottomRight += Trans;
	BotomLeft += Trans;
	Top += Trans;
	for (auto& t : Children)
	{
		t.Translation(Trans);
	}*/
}

