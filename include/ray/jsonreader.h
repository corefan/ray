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
#ifndef _H_JSONREADER_H_
#define _H_JSONREADER_H_

#include <ray/ioarchive.h>

_NAME_BEGIN

class EXPORT JsonReader final : public iarchive
{
public:
	JsonReader() noexcept;
	JsonReader(StreamReader& stream) except;
	JsonReader(const std::string& path) except;
	~JsonReader() noexcept;

	JsonReader& open(StreamReader& stream) except;
	JsonReader& open(const std::string& path) except;

	bool is_open() const noexcept;

	void close() noexcept;

private:
	JsonReader(const JsonReader&) noexcept = delete;
	JsonReader& operator=(const JsonReader&) noexcept = delete;

private:
	archivebuf _json;
};

class EXPORT JsonWrite final : public oarchive
{
public:
	JsonWrite() noexcept;
	~JsonWrite() noexcept;

	JsonWrite& save(StreamWrite& stream) except;
	JsonWrite& save(const std::string& path) except;

	void close() noexcept;

	bool is_open() const noexcept;

private:
	JsonWrite(const JsonWrite&) noexcept = delete;
	JsonWrite& operator=(const JsonWrite&) noexcept = delete;

private:
	archivebuf _json;
};

_NAME_END

#endif