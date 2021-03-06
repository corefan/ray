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
#ifndef _H_MEMORY_H_
#define _H_MEMORY_H_

#include <memory>

namespace std
{
#if defined(__MINGW64__) || defined(__MINGW32__) || defined(__LINUX__) || defined(__ANDROID__)
	template<class _Ty,
	class... _Types> inline
		typename std::enable_if<!std::is_array<_Ty>::value,
		std::unique_ptr<_Ty> >::type make_unique(_Types&&... _Args)
	{    // make a unique_ptr
		return (std::unique_ptr<_Ty>(new _Ty(std::forward<_Types>(_Args)...)));
	}

	template<class _Ty> inline
		typename std::enable_if<std::is_array<_Ty>::value && std::extent<_Ty>::value == 0,
		std::unique_ptr<_Ty> >::type make_unique(std::size_t _Size)
	{    // make a unique_ptr
		typedef typename std::remove_extent<_Ty>::type _Elem;
		return (std::unique_ptr<_Ty>(new _Elem[_Size]()));
	}
#endif
}

#endif