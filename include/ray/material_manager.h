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
#ifndef _H_MATERIAL_MANAGER_H_
#define _H_MATERIAL_MANAGER_H_

#include <ray/material.h>

_NAME_BEGIN

class EXPORT MaterialManager final
{
public:
	MaterialManager() noexcept;
	~MaterialManager() noexcept;

	bool setup(GraphicsDevicePtr device) noexcept;
	void close() noexcept;

	GraphicsDeviceType getDeviceType() const noexcept;
	
	MaterialPtr createMaterial(const std::string& name) noexcept;
	MaterialPtr getMaterial(const std::string& name) noexcept;
	void destroyMaterial(MaterialPtr& material) noexcept;
	void destroyMaterial(MaterialPtr&& material) noexcept;

	GraphicsStatePtr createRenderState(const GraphicsStateDesc& shaderDesc) noexcept;
	GraphicsShaderPtr createShader(const GraphicsShaderDesc& shaderDesc) noexcept;
	GraphicsProgramPtr createProgram(const GraphicsProgramDesc& programDesc) noexcept;

	GraphicsSamplerPtr createSampler(const std::string& name, const GraphicsSamplerDesc& samplerDesc) noexcept;
	void destroySampler(GraphicsSamplerPtr sampler) noexcept;
	void destroySampler(const std::string& name) noexcept;
	GraphicsSamplerPtr getSampler(const std::string& name) noexcept;

	GraphicsInputLayoutPtr createInputLayout(const std::string& name, GraphicsInputLayoutDesc& textureDesc) noexcept;
	void destroyInputLayout(GraphicsInputLayoutPtr texture) noexcept;
	void destroyInputLayout(const std::string& name) noexcept;
	GraphicsInputLayoutPtr getInputLayout(const std::string& name) noexcept;

private:
	MaterialManager(const MaterialManager&) = delete;
	MaterialManager& operator=(const MaterialManager&) = delete;

private:
	GraphicsDevicePtr _graphicsDevice;

	std::map<std::string, GraphicsShaderPtr> _shaders;
	std::map<std::string, GraphicsSamplerPtr> _samplers;
	std::map<std::string, GraphicsInputLayoutPtr> _inputLayouts;
	std::map<std::string, MaterialPtr> _materials;
};

_NAME_END

#endif