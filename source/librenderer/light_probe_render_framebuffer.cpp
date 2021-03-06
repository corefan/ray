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
#include <ray/light_probe_render_framebuffer.h>
#include <ray/render_system.h>
#include <ray/graphics_texture.h>
#include <ray/graphics_framebuffer.h>

_NAME_BEGIN

__ImplementSubInterface(LightProbeRenderFramebuffer, RenderPipelineFramebuffer, "LightProbeRenderFramebuffer")

LightProbeRenderFramebuffer::LightProbeRenderFramebuffer() noexcept
{
}

LightProbeRenderFramebuffer::LightProbeRenderFramebuffer(std::uint32_t probeMapSize)
{
	this->setup(probeMapSize);
}

LightProbeRenderFramebuffer::~LightProbeRenderFramebuffer() noexcept
{
}

bool
LightProbeRenderFramebuffer::setup(std::uint32_t probeMapSize)
{
	GraphicsFormat probeColorFormat;
	GraphicsFormat probeNormalFormat;

	if (RenderSystem::instance()->isTextureSupport(GraphicsFormat::GraphicsFormatR8G8B8UNorm))
		probeColorFormat = probeNormalFormat = GraphicsFormat::GraphicsFormatR8G8B8UNorm;
	else
		return false;

	GraphicsTextureDesc probeColorDesc;
	probeColorDesc.setWidth(probeMapSize);
	probeColorDesc.setHeight(probeMapSize);
	probeColorDesc.setTexDim(GraphicsTextureDim::GraphicsTextureDimCube);
	probeColorDesc.setTexFormat(probeColorFormat);
	probeColorDesc.setSamplerFilter(GraphicsSamplerFilter::GraphicsSamplerFilterNearest, GraphicsSamplerFilter::GraphicsSamplerFilterNearest);
	_probeColorMap = RenderSystem::instance()->createTexture(probeColorDesc);
	if (!_probeColorMap)
		return false;

	GraphicsTextureDesc probeNormalDesc;
	probeNormalDesc.setWidth(probeMapSize);
	probeNormalDesc.setHeight(probeMapSize);
	probeNormalDesc.setTexDim(GraphicsTextureDim::GraphicsTextureDimCube);
	probeNormalDesc.setTexFormat(probeNormalFormat);
	probeNormalDesc.setSamplerFilter(GraphicsSamplerFilter::GraphicsSamplerFilterNearest, GraphicsSamplerFilter::GraphicsSamplerFilterNearest);
	_probeNormalMap = RenderSystem::instance()->createTexture(probeNormalDesc);
	if (!_probeNormalMap)
		return false;

	return true;
}

_NAME_END