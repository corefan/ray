// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include "LightMapPack.h"

#include <sstream>
#include <UVAtlas/UVAtlas.h>
#include <DirectXMesh/DirectXMesh.h>

_NAME_BEGIN

LightMapPack::LightMapPack() noexcept
	: _lightMapListener(std::make_shared<LightMapListener>())
{
}

LightMapPack::LightMapPack(LightMapListenerPtr listener) noexcept
	: _lightMapListener(listener)
{
}

LightMapPack::~LightMapPack() noexcept
{
}

void
LightMapPack::setLightMapListener(LightMapListenerPtr pointer) noexcept
{
	if (_lightMapListener != pointer)
	{
		if (_lightMapListener)
			_lightMapListener->onListenerChangeBefore();

		_lightMapListener = pointer;

		if (_lightMapListener)
			_lightMapListener->onListenerChangeAfter();
	}
}

LightMapListenerPtr
LightMapPack::getLightMapListener() const noexcept
{
	return _lightMapListener;
}

bool
LightMapPack::atlasUV(PMX& model, std::uint32_t w, std::uint32_t h, std::uint32_t chart, float stretch, float margin, std::function<HRESULT(float)> progress) noexcept
{
	if (_lightMapListener)
		_lightMapListener->onUvmapperStart();

	std::vector<float3> atlasVertices;
	std::vector<std::uint32_t> atlasIndices;

	for (std::size_t i = 0; i < model.numVertices; i++)
		atlasVertices.push_back(model.vertices[i].position);

	std::vector<uint32_t> adj(model.numIndices);

	if (model.header.sizeOfIndices == 1)
	{
		if (_lightMapListener)
			_lightMapListener->onMessage("Failed to GenerateAdjacencyAndPointReps.");
		return false;
	}
	else if (model.header.sizeOfIndices == 2)
	{
		HRESULT hr = DirectX::GenerateAdjacencyAndPointReps((std::uint16_t*)model.indices.data(), model.numIndices / 3, (DirectX::XMFLOAT3*)atlasVertices.data(), model.numVertices, 0.0, nullptr, adj.data());
		if (FAILED(hr))
		{
			if (_lightMapListener)
				_lightMapListener->onMessage("Failed to GenerateAdjacencyAndPointReps.");
			return false;
		}
	}
	else
	{
		HRESULT hr = DirectX::GenerateAdjacencyAndPointReps((std::uint32_t*)model.indices.data(), model.numIndices / 3, (DirectX::XMFLOAT3*)atlasVertices.data(), model.numVertices, 0.0, nullptr, adj.data());
		if (FAILED(hr))
		{
			if (_lightMapListener)
				_lightMapListener->onMessage("Failed to GenerateAdjacencyAndPointReps.");
			return false;
		}
	}

	std::vector<DirectX::UVAtlasVertex> vb;
	std::vector<uint8_t> ib;
	std::vector<uint32_t> remap;

	auto callback = [&](float percentComplete) -> HRESULT
	{
		if (_lightMapListener)
			_lightMapListener->onUvmapperProgressing(percentComplete);

		return S_OK;
	};

	if (model.header.sizeOfIndices == 1)
		return false;
	else if (model.header.sizeOfIndices == 2)
	{
		HRESULT hr = DirectX::UVAtlasCreate(
			(DirectX::XMFLOAT3*)atlasVertices.data(),
			atlasVertices.size(),
			model.indices.data(),
			DXGI_FORMAT::DXGI_FORMAT_R16_UINT,
			model.numIndices / 3, chart, stretch, w, h, margin, adj.data(), 0, 0,
			progress ? progress : callback,
			1.0,
			DirectX::UVATLAS_DEFAULT,
			vb, ib, 0, &remap);

		if (FAILED(hr))
		{
			if (_lightMapListener)
				_lightMapListener->onMessage("Failed to UV Atlas.");
			return false;
		}
	}
	else
	{
		HRESULT hr = DirectX::UVAtlasCreate(
			(DirectX::XMFLOAT3*)atlasVertices.data(),
			atlasVertices.size(),
			model.indices.data(),
			DXGI_FORMAT::DXGI_FORMAT_R32_UINT,
			model.numIndices / 3, chart, stretch, w, h, margin, adj.data(), 0, 0,
			progress ? progress : callback,
			1.0,
			DirectX::UVATLAS_DEFAULT,
			vb, ib, 0, &remap);

		if (FAILED(hr))
		{
			if (_lightMapListener)
				_lightMapListener->onMessage("Failed to UV Atlas.");
			return false;
		}
	}

	std::vector<PMX_Vertex> newVertices;
	newVertices.resize(vb.size());

	for (int i = 0; i < vb.size(); i++)
	{
		PMX_Vertex v = model.vertices[remap[i]];
		v.addCoord->x = vb[i].uv.x;
		v.addCoord->y = vb[i].uv.y;

		newVertices[i] = v;
	}

	model.header.addUVCount = 1;
	model.numVertices = newVertices.size();
	model.vertices = newVertices;
	model.indices = ib;

	if (_lightMapListener)
		_lightMapListener->onUvmapperEnd();

	return true;
}

std::uint32_t
LightMapPack::getFace(const PMX& model, std::size_t n) noexcept
{
	std::uint8_t* data = (std::uint8_t*)model.indices.data();

	if (model.header.sizeOfIndices == 1)
		return *(std::uint8_t*)(data + n * model.header.sizeOfIndices);
	else if (model.header.sizeOfIndices == 2)
		return *(std::uint16_t*)(data + n * model.header.sizeOfIndices);
	else if (model.header.sizeOfIndices == 4)
		return *(std::uint32_t*)(data + n * model.header.sizeOfIndices);
	else
		return false;
}

std::uint32_t
LightMapPack::getFace(const PMX& model, std::size_t n, std::uint32_t firstIndex) noexcept
{
	std::uint8_t* data = (std::uint8_t*)model.indices.data() + firstIndex;

	if (model.header.sizeOfIndices == 1)
		return *(std::uint8_t*)(data + n * model.header.sizeOfIndices);
	else if (model.header.sizeOfIndices == 2)
		return *(std::uint16_t*)(data + n * model.header.sizeOfIndices);
	else if (model.header.sizeOfIndices == 4)
		return *(std::uint32_t*)(data + n * model.header.sizeOfIndices);
	else
		return false;
}

_NAME_END