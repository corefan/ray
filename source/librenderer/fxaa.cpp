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
#include "fxaa.h"
#include <ray/material.h>
#include <ray/graphics_texture.h>
#include <ray/graphics_framebuffer.h>
#include <ray/render_pipeline.h>

_NAME_BEGIN

FXAA::FXAA() noexcept
{
}

FXAA::~FXAA() noexcept
{
}

void
FXAA::onActivate(RenderPipeline& pipeline) noexcept
{
	_fxaa = pipeline.createMaterial("sys:fx/fxaa.fxml");
	_fxaaTech = _fxaa->getTech("fxaa");

	_texelStep = _fxaa->getParameter("texelStep");
	_texelSource = _fxaa->getParameter("texelSource");
}

void
FXAA::onDeactivate(RenderPipeline& pipeline) noexcept
{
	if (_fxaa)
	{
		_fxaa.reset();
		_fxaa = nullptr;
	}

	_fxaaTech = nullptr;
	_texelStep = nullptr;
}

bool
FXAA::onRender(RenderPipeline& pipeline, RenderQueue queue, const GraphicsFramebufferPtr& source, const GraphicsFramebufferPtr& swap) noexcept
{
	if (queue != RenderQueue::RenderQueuePostprocess)
		return false;

	auto texture = source->getGraphicsFramebufferDesc().getColorAttachment(0).getBindingTexture();

	auto& textureDesc = texture->getGraphicsTextureDesc();
	_texelStep->uniform2f(float2(1.0f / textureDesc.getWidth(), 1.0f / textureDesc.getHeight()));
	_texelSource->uniformTexture(texture);

	pipeline.setFramebuffer(swap);
	pipeline.discardFramebuffer(0);
	pipeline.drawScreenQuad(*_fxaaTech);

	return true;
}

_NAME_END