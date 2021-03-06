// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
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
#ifndef _H_TERRAIN_MAP_H_
#define _H_TERRAIN_MAP_H_

#include "terrain_types.h"

#define EMPTY_ENTRY (-1)

class TerrainData
{
public:
	TerrainData() noexcept
		: x(EMPTY_ENTRY)
		, y(EMPTY_ENTRY)
		, z(EMPTY_ENTRY)
		, instanceID(0)
	{
	}

	TerrainData(BlockPosition xx, BlockPosition yy, BlockPosition zz, InstanceID id = 0) noexcept
		: x(xx)
		, y(yy)
		, z(zz)
		, instanceID(id)
	{
	}

	bool empty() const noexcept
	{
		return
			x == EMPTY_ENTRY ||
			y == EMPTY_ENTRY ||
			z == EMPTY_ENTRY ? true : false;
	}

	BlockPosition x;
	BlockPosition y;
	BlockPosition z;

	InstanceID instanceID;
};

class TerrainMap final
{
public:
	TerrainMap() noexcept;
	TerrainMap(std::size_t mask) noexcept;
	~TerrainMap() noexcept;

	void create(std::size_t mask) noexcept;
	void clear() noexcept;

	bool set(const TerrainData& data) noexcept;
	bool get(TerrainData& data) noexcept;

	void grow() noexcept;

	std::size_t count() const noexcept;

	TerrainDatas& data() noexcept;

private:
	TerrainMap(const TerrainMap&) noexcept = delete;
	TerrainMap& operator=(const TerrainMap&) noexcept = delete;

private:

	std::size_t _mask;
	std::size_t _count;

	std::vector<TerrainData> _data;
};

#endif