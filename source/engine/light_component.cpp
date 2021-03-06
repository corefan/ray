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
#if defined(_BUILD_RENDERER)
#include <ray/light_component.h>
#include <ray/skybox_component.h>
#include <ray/game_server.h>
#include <ray/render_feature.h>

_NAME_BEGIN

__ImplementSubClass(LightComponent, RenderComponent, "Light")

LightComponent::LightComponent() noexcept
	: _onSkyBoxChange(std::bind(&LightComponent::onSkyBoxChange, this))
	, _onSkyLightingDiffuseChange(std::bind(&LightComponent::onSkyLightingDiffuseChange, this))
	, _onSkyLightingSpecularChange(std::bind(&LightComponent::onSkyLightingSpecularChange, this))
	, _onEnableSkyBox(std::bind(&LightComponent::onEnableSkyBox, this, std::placeholders::_1))
	, _onEnableSkyLighting(std::bind(&LightComponent::onEnableSkyLighting, this, std::placeholders::_1))
{
	_light = std::make_shared<Light>();
	_light->setOwnerListener(this);
}

LightComponent::LightComponent(const archivebuf& reader) noexcept
	: LightComponent()
{
	this->load(reader);
}

LightComponent::~LightComponent() noexcept
{
	_light->setRenderScene(nullptr);
}

void
LightComponent::setVisible(bool visible) noexcept
{
	_light->setVisible(visible);
}

bool
LightComponent::getVisible() const noexcept
{
	return _light->getVisible();
}

void
LightComponent::setLightRange(float range) noexcept
{
	_light->setLightRange(range);
}

void
LightComponent::setLightIntensity(float intensity) noexcept
{
	_light->setLightIntensity(intensity);
}

void
LightComponent::setLightAttenuation(const float3& atten) noexcept
{
	return _light->setLightAttenuation(atten);
}

void
LightComponent::setSpotInnerCone(float value) noexcept
{
	_light->setSpotInnerCone(value);
}

void
LightComponent::setSpotOuterCone(float value) noexcept
{
	_light->setSpotOuterCone(value);
}

float
LightComponent::getLightRange() const noexcept
{
	return _light->getLightRange();
}

float
LightComponent::getLightIntensity() const noexcept
{
	return _light->getLightIntensity();
}

const float3&
LightComponent::getLightAttenuation() const noexcept
{
	return _light->getLightAttenuation();
}

const float2&
LightComponent::getSpotInnerCone() const noexcept
{
	return _light->getSpotInnerCone();
}

const float2&
LightComponent::getSpotOuterCone() const noexcept
{
	return _light->getSpotOuterCone();
}

void
LightComponent::setShadowMode(ShadowMode shadow) noexcept
{
	_light->setShadowMode(shadow);
}

ShadowMode
LightComponent::getShadowMode() const noexcept
{
	return _light->getShadowMode();
}

void
LightComponent::setShadowBias(float bias) noexcept
{
	_light->setShadowBias(bias);
}

float
LightComponent::getShadowBias() const noexcept
{
	return _light->getShadowBias();
}

void
LightComponent::setGlobalIllumination(bool enable) noexcept
{
	_light->setGlobalIllumination(enable);
}

bool
LightComponent::getGlobalIllumination() const noexcept
{
	return _light->getGlobalIllumination();
}

void
LightComponent::setLightColor(const float3& color) noexcept
{
	_light->setLightColor(color);
}

const float3&
LightComponent::getLightColor() const noexcept
{
	return _light->getLightColor();
}

void
LightComponent::setLightType(LightType type) noexcept
{
	_light->setLightType(type);
}

LightType
LightComponent::getLightType() const noexcept
{
	return _light->getLightType();
}

void
LightComponent::load(const archivebuf& reader) noexcept
{
	GameComponent::load(reader);

	const auto& inner_cone = reader["inner_cone"];
	const auto& outer_cone = reader["outer_cone"];
	const auto& lightIntensity = reader["intensity"];
	const auto& lightRange = reader["range"];
	const auto& lightColor = reader["color"];
	const auto& lightAtten = reader["atten"];
	const auto& lightType = reader["type"];
	const auto& enableGI = reader["GI"];
	const auto& shadowBias = reader["bias"];
	const auto& shadowMode = reader["shadow"];

	if (lightRange.is_numeric())
		this->setLightRange(lightRange.get<archive::number_float_t>());

	if (lightIntensity.is_numeric())
		this->setLightIntensity(lightIntensity.get<archive::number_float_t>());

	if (inner_cone.is_numeric())
		this->setSpotInnerCone(inner_cone.get<archive::number_float_t>());

	if (outer_cone.is_numeric())
		this->setSpotOuterCone(outer_cone.get<archive::number_float_t>());

	if (shadowBias.is_numeric())
		this->setShadowBias(shadowBias.get<archive::number_float_t>());

	if (enableGI.is_boolean())
		this->setGlobalIllumination(enableGI.get<archive::boolean_t>());

	if (lightColor.is_array())
	{
		float3 color;

		const auto& values = lightColor.get<archive::array_t>();
		for (std::uint8_t i = 0; i < 3; ++i)
			color[i] = values[i].get<archive::number_float_t>();

		this->setLightColor(color);
	}

	if (lightAtten.is_array())
	{
		float3 atten;

		const auto& values = lightAtten.get<archive::array_t>();
		for (std::uint8_t i = 0; i < 3; ++i)
			atten[i] = values[i].get<archive::number_float_t>();

		this->setLightAttenuation(atten);
	}

	if (lightType.is_string())
	{
		const auto& name = lightType.get<archive::string_t>();

		if (name == "sun")
			this->setLightType(LightType::LightTypeSun);
		else if (name == "directional")
			this->setLightType(LightType::LightTypeDirectional);
		else if (name == "point")
			this->setLightType(LightType::LightTypePoint);
		else if (name == "spot")
			this->setLightType(LightType::LightTypeSpot);
		else if (name == "ambient")
			this->setLightType(LightType::LightTypeAmbient);
		else if (name == "environment")
			this->setLightType(LightType::LightTypeEnvironment);
		else
			this->setLightType(LightType::LightTypePoint);
	}

	if (shadowMode.is_string())
	{
		const auto& name = shadowMode.get<archive::string_t>();

		if (name == "hard")
			this->setShadowMode(ShadowMode::ShadowModeHard);
		else if (name == "soft")
			this->setShadowMode(ShadowMode::ShadowModeSoft);
		else
			this->setShadowMode(ShadowMode::ShadowModeNone);
	}
}

void
LightComponent::save(archivebuf& write) noexcept
{
	RenderComponent::save(write);
}

GameComponentPtr
LightComponent::clone() const noexcept
{
	auto result = std::make_shared<LightComponent>();
	result->setName(this->getName());
	result->setActive(this->getActive());
	return result;
}

void
LightComponent::onActivate() noexcept
{
	this->addComponentDispatch(GameDispatchType::GameDispatchTypeMoveAfter, this);

	_light->setRenderScene(GameServer::instance()->getFeature<RenderFeature>()->getRenderScene());
	_light->setTransform(this->getGameObject()->getWorldTransform(), this->getGameObject()->getWorldTransformInverse());
}

void
LightComponent::onDeactivate() noexcept
{
	this->removeComponentDispatch(GameDispatchType::GameDispatchTypeMoveAfter, this);

	_light->setRenderScene(nullptr);
}

void
LightComponent::onAttachComponent(const GameComponentPtr& component) noexcept
{
	if (component->isInstanceOf<SkyboxComponent>())
	{
		auto skyboxComponent = component->downcast<SkyboxComponent>();
		skyboxComponent->addSkyBoxChangeListener(&_onSkyBoxChange);
		skyboxComponent->addSkyLightingDiffuseChangeListener(&_onSkyLightingDiffuseChange);
		skyboxComponent->addSkyLightingSpecularChangeListener(&_onSkyLightingSpecularChange);
		skyboxComponent->addEnableSkyBoxListener(&_onEnableSkyBox);
		skyboxComponent->addEnableSkyLightingListener(&_onEnableSkyLighting);

		if (skyboxComponent->getSkyboxEnable())
		{
			_light->setVisible(skyboxComponent->getSkyLightingEnable());
			_light->setSkyBox(skyboxComponent->getSkyBox());
			_light->setSkyLightingDiffuse(skyboxComponent->getSkyLightDiffuse());
			_light->setSkyLightingSpecular(skyboxComponent->getSkyLightSpecular());
		}
		else
		{
			_light->setSkyBox(nullptr);
		}
	}
}

void
LightComponent::onDetachComponent(const GameComponentPtr& component) noexcept
{
	if (component->isInstanceOf<SkyboxComponent>())
	{
		auto skyboxComponent = component->downcast<SkyboxComponent>();
		skyboxComponent->removeSkyBoxChangeListener(&_onSkyBoxChange);
		skyboxComponent->removeSkyLightingDiffuseChangeListener(&_onSkyLightingDiffuseChange);
		skyboxComponent->removeSkyLightingSpecularChangeListener(&_onSkyLightingSpecularChange);
		skyboxComponent->removeEnableSkyBoxListener(&_onEnableSkyBox);
		skyboxComponent->removeEnableSkyLightingListener(&_onEnableSkyLighting);

		_light->setVisible(false);
		_light->setSkyBox(nullptr);
		_light->setSkyLightingDiffuse(nullptr);
		_light->setSkyLightingSpecular(nullptr);
	}
}

void
LightComponent::onMoveAfter() noexcept
{
	_light->setTransform(this->getGameObject()->getWorldTransform(), this->getGameObject()->getWorldTransformInverse());
}

void
LightComponent::onEnableSkyBox(bool enable) noexcept
{
}

void
LightComponent::onEnableSkyLighting(bool enable) noexcept
{
	auto component = this->getGameObject()->getComponent<SkyboxComponent>();
	if (component)
	{
		_light->setVisible(enable);
		_light->setSkyLightingDiffuse(component->getSkyLightDiffuse());
		_light->setSkyLightingSpecular(component->getSkyLightSpecular());
	}
	else
	{
		_light->setVisible(false);
		_light->setSkyLightingDiffuse(nullptr);
		_light->setSkyLightingSpecular(nullptr);
	}
}

void
LightComponent::onSkyBoxChange() noexcept
{
	auto component = this->getGameObject()->getComponent<SkyboxComponent>();
	if (component)
		_light->setSkyBox(component->getSkyBox());
}

void
LightComponent::onSkyLightingDiffuseChange() noexcept
{
	auto component = this->getGameObject()->getComponent<SkyboxComponent>();
	if (component)
		_light->setSkyLightingDiffuse(component->getSkyLightDiffuse());
}

void
LightComponent::onSkyLightingSpecularChange() noexcept
{
	auto component = this->getGameObject()->getComponent<SkyboxComponent>();
	if (component)
		_light->setSkyLightingSpecular(component->getSkyLightSpecular());
}

_NAME_END

#endif