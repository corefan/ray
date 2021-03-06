// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
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
#ifndef _H_EGL2_FRAMEBUFFER_H_
#define _H_EGL2_FRAMEBUFFER_H_

#include "egl2_types.h"

_NAME_BEGIN

class EGL2FramebufferLayout final : public GraphicsFramebufferLayout
{
	__DeclareSubClass(EGL2FramebufferLayout, GraphicsFramebufferLayout)
public:
	EGL2FramebufferLayout() noexcept;
	~EGL2FramebufferLayout() noexcept;

	bool setup(const GraphicsFramebufferLayoutDesc& framebufferDesc) noexcept;
	void close() noexcept;

	const GraphicsFramebufferLayoutDesc& getGraphicsFramebufferLayoutDesc() const noexcept;

private:
	friend class EGL2Device;
	void setDevice(GraphicsDevicePtr device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

private:
	EGL2FramebufferLayout(const EGL2FramebufferLayout&) noexcept = delete;
	EGL2FramebufferLayout& operator=(const EGL2FramebufferLayout&) noexcept = delete;

private:
	GraphicsDeviceWeakPtr _device;
	GraphicsFramebufferLayoutDesc _framebufferLayoutDesc;
};

class EGL2Framebuffer final : public GraphicsFramebuffer
{
	__DeclareSubClass(EGL2Framebuffer, GraphicsFramebuffer)
public:
	EGL2Framebuffer() noexcept;
	~EGL2Framebuffer() noexcept;

	bool setup(const GraphicsFramebufferDesc& framebufferDesc) noexcept;
	void close() noexcept;

	GLuint getInstanceID() noexcept;

	const GraphicsFramebufferDesc& getGraphicsFramebufferDesc() const noexcept;

private:
	bool bindRenderTexture(GraphicsTexturePtr target, GLenum attachment, GLint level, GLint layer) noexcept;

private:
	friend class EGL2Device;
	void setDevice(GraphicsDevicePtr device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

private:
	EGL2Framebuffer(const EGL2Framebuffer&) noexcept = delete;
	EGL2Framebuffer& operator=(const EGL2Framebuffer&) noexcept = delete;

private:
	GLuint _fbo;

	GraphicsDeviceWeakPtr _device;
	GraphicsFramebufferDesc _framebufferDesc;
};

_NAME_END

#endif