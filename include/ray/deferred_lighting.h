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
#ifndef _H_DEFERRED_LIGHTING_H_
#define _H_DEFERRED_LIGHTING_H_

#include <ray/render_pipeline.h>

_NAME_BEGIN

class DeferredLighting final : public RenderPipeline
{
public:
    DeferredLighting() noexcept;
    ~DeferredLighting() noexcept;

    void setup(std::size_t width, std::size_t height) except;
    void close() noexcept;

    void render() noexcept;

private:

    void renderShadow() noexcept;

    void renderOpaquesDepthOhly() noexcept;
    void renderOpaques() noexcept;
    void renderOpaquesShading() noexcept;

    void renderTransparentDepthOhly() noexcept;
    void renderTransparent() noexcept;
    void renderTransparentShading() noexcept;

    void renderFinal() noexcept;

    void renderLights() noexcept;
    void renderSunLight(const Light& light) noexcept;
    void renderPointLight(const Light& light) noexcept;
    void renderSpotLight(const Light& light) noexcept;
    void renderHemiSphereLight(const Light& light) noexcept;
    void renderAreaLight(const Light& light) noexcept;

private:

    MaterialPtr _shadow;
    MaterialPassPtr _shadowGenerate;
    MaterialPassPtr _shadowBlurX;
    MaterialPassPtr _shadowBlurY;

    MaterialPtr _deferredLighting;
    MaterialPassPtr _deferredDepthOhly;
    MaterialPassPtr _deferredDepthLinear;
    MaterialPassPtr _deferredSunLight;
    MaterialPassPtr _deferredSpotLight;
    MaterialPassPtr _deferredPointLight;
    MaterialPassPtr _deferredShading;
    MaterialPassPtr _deferredCombine;

    ShaderParamPtr _texDepth;
    ShaderParamPtr _texDiffuse;
    ShaderParamPtr _texNormal;
    ShaderParamPtr _texLight;
    ShaderParamPtr _texOpaques;
    ShaderParamPtr _texTransparent;

    ShaderParamPtr _shadowDecal;
    ShaderParamPtr _shadowChannel;
    ShaderParamPtr _shadowMap;
    ShaderParamPtr _shadowLitFactor;
    ShaderParamPtr _shadowFactor;
    ShaderParamPtr _shadowMatrix;
    ShaderParamPtr _shadowOffset;
    ShaderParamPtr _shadowWeight;

    RenderTexturePtr _deferredDepthMap;
    RenderTexturePtr _deferredGraphicMap;
    RenderTexturePtr _deferredNormalMap;
    RenderTexturePtr _deferredLightMap;
    RenderTexturePtr _deferredShadingMap;

    MultiRenderTexturePtr _deferredGraphicMaps;
};

_NAME_END

#endif