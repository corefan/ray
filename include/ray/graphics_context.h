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
#ifndef _H_GRAPHICS_CONTEXT_H_
#define _H_GRAPHICS_CONTEXT_H_

#include <ray/graphics_child.h>

_NAME_BEGIN

class EXPORT GraphicsIndirect final
{
public:
	GraphicsIndirect() noexcept;

	std::int32_t startVertice;
	std::int32_t startIndice;
	std::int32_t startInstances;
	std::int32_t numVertices;
	std::int32_t numIndices;
	std::int32_t numInstances;
	GraphicsIndexType indexType;
};

class EXPORT GraphicsContextDesc final
{
public:
	GraphicsContextDesc() noexcept;
	~GraphicsContextDesc() noexcept;

	void setDebugMode(bool mode) noexcept;
	bool getDebugMode() const noexcept;

	void setSwapchain(GraphicsSwapchainPtr swapchain) noexcept;
	GraphicsSwapchainPtr getSwapchain() const noexcept;

private:
	bool _debugMode;
	GraphicsSwapchainPtr _swapchain;
};

class EXPORT GraphicsContext : public GraphicsChild
{
	__DeclareSubInterface(GraphicsContext, GraphicsChild)
public:
	GraphicsContext() noexcept;
	virtual ~GraphicsContext() noexcept;

	virtual void renderBegin() noexcept = 0;
	virtual void renderEnd() noexcept = 0;

	virtual void setViewport(const Viewport& viewport) noexcept = 0;
	virtual const Viewport& getViewport() const noexcept = 0;

	virtual void setScissor(const Scissor& scissor) noexcept = 0;
	virtual const Scissor& getScissor() const noexcept = 0;

	virtual void setStencilCompare(GraphicsStencilFace face, GraphicsCompareFunc func) noexcept = 0;
	virtual GraphicsCompareFunc getStencilCompare(GraphicsStencilFace face) noexcept = 0;

	virtual void setStencilReference(GraphicsStencilFace face, std::uint32_t reference) noexcept = 0;
	virtual std::uint32_t getStencilReference(GraphicsStencilFace face) noexcept = 0;

	virtual void setStencilFrontWriteMask(GraphicsStencilFace face, std::uint32_t mask) noexcept = 0;
	virtual std::uint32_t getStencilFrontWriteMask(GraphicsStencilFace face) noexcept = 0;

	virtual void setRenderPipeline(GraphicsPipelinePtr pipeline) noexcept = 0;
	virtual GraphicsPipelinePtr getRenderPipeline() const noexcept = 0;

	virtual void setDescriptorSet(GraphicsDescriptorSetPtr descriptorSet) noexcept = 0;
	virtual GraphicsDescriptorSetPtr getDescriptorSet() const noexcept = 0;

	virtual void setVertexBufferData(GraphicsDataPtr data) noexcept = 0;
	virtual GraphicsDataPtr getVertexBufferData() const noexcept = 0;

	virtual void setIndexBufferData(GraphicsDataPtr data) noexcept = 0;
	virtual GraphicsDataPtr getIndexBufferData() const noexcept = 0;

	virtual void setFramebuffer(GraphicsFramebufferPtr target) noexcept = 0;
	virtual void setFramebuffer(GraphicsFramebufferPtr target, const float4& color, float depth, std::int32_t stencil) noexcept = 0;
	virtual void clearFramebuffer(GraphicsClearFlags flags, const float4& color, float depth, std::int32_t stencil) noexcept = 0;
	virtual void discardFramebuffer() noexcept = 0;
	virtual void blitFramebuffer(GraphicsFramebufferPtr src, const Viewport& v1, GraphicsFramebufferPtr dest, const Viewport& v2) noexcept = 0;
	virtual void readFramebuffer(GraphicsFramebufferPtr source, GraphicsFormat pfd, std::size_t w, std::size_t h, std::size_t bufsize, void* data) noexcept = 0;
	virtual GraphicsFramebufferPtr getFramebuffer() const noexcept = 0;

	virtual void drawRenderMesh(const GraphicsIndirect& renderable) noexcept = 0;
	virtual void drawRenderMesh(const GraphicsIndirect renderable[], std::size_t first, std::size_t count) noexcept = 0;

	virtual bool isTextureSupport(GraphicsFormat format) noexcept = 0;
	virtual bool isTextureDimSupport(GraphicsTextureDim dimension) noexcept = 0;
	virtual bool isVertexSupport(GraphicsFormat format) noexcept = 0;
	virtual bool isShaderSupport(GraphicsShaderStage stage) noexcept = 0;

	virtual void present() noexcept = 0;

private:
	GraphicsContext(const GraphicsContext&) noexcept = delete;
	GraphicsContext& operator=(const GraphicsContext&) noexcept = delete;
};

class EXPORT GraphicsContext2 : public GraphicsContext
{
	__DeclareSubInterface(GraphicsContext2, GraphicsContext)
public:
	GraphicsContext2() noexcept;
	virtual ~GraphicsContext2() noexcept;

	virtual void clearFramebufferIndexed(GraphicsClearFlags flags, const float4& color, float depth, std::int32_t stencil, std::uint32_t i) noexcept = 0;

private:
	GraphicsContext2(const GraphicsContext2&) noexcept = delete;
	GraphicsContext2& operator=(const GraphicsContext2&) noexcept = delete;
};

_NAME_END

#endif