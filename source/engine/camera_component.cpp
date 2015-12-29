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
#if defined(_BUILD_RENDERER)
#include <ray/camera_component.h>
#include <ray/render_feature.h>
#include <ray/game_server.h>

_NAME_BEGIN

__ImplementSubClass(CameraComponent, GameComponent, "Camera")

CameraComponent::CameraComponent() noexcept
{
	_camera = std::make_shared<Camera>();
	_camera->setOwnerListener(this);
	_camera->setCameraOrder(CameraOrder::CO_MAIN);
}

CameraComponent::~CameraComponent() noexcept
{
	_camera->setRenderScene(nullptr);
}

void
CameraComponent::makeLookAt(const Vector3& pos, const Vector3& lookat, const Vector3& up) noexcept
{
	_camera->makeLookAt(pos, lookat, up);
}

void
CameraComponent::makeOrtho(float left, float right, float bottom, float top, float znear, float zfar) noexcept
{
	_camera->makeOrtho(left, right, bottom, top, znear, zfar);
}

void
CameraComponent::makePerspective(float aperture, float znear, float zfar) noexcept
{
	_camera->makePerspective(aperture, znear, zfar);
}

const Matrix4x4&
CameraComponent::getView() const noexcept
{
	return _camera->getView();
}

const Matrix4x4&
CameraComponent::getViewInverse() const noexcept
{
	return _camera->getViewInverse();
}

const Matrix4x4&
CameraComponent::getViewInverseTranspose() const noexcept
{
	return _camera->getViewInverseTranspose();
}

const Matrix4x4&
CameraComponent::getProject() const noexcept
{
	return _camera->getProject();
}

const Matrix4x4&
CameraComponent::getProjectInverse() const noexcept
{
	return _camera->getProjectInverse();
}

const Matrix4x4&
CameraComponent::getViewProject() const noexcept
{
	return _camera->getViewProject();
}

const Matrix4x4&
CameraComponent::getViewProjectInverse() const noexcept
{
	return _camera->getViewProjectInverse();
}

Vector3
CameraComponent::worldToScreen(const Vector3& pos) const noexcept
{
	return _camera->worldToScreen(pos);
}

Vector3
CameraComponent::screenToWorld(const Vector3& pos) const noexcept
{
	return _camera->screenToWorld(pos);
}

Vector3
CameraComponent::screenToDirection(const Vector2& pos) const noexcept
{
	return _camera->screenToDirection(pos);
}

void
CameraComponent::setViewport(const Viewport& viewport) noexcept
{
	_camera->setViewport(viewport);
}

const Viewport&
CameraComponent::getViewport() const noexcept
{
	return _camera->getViewport();
}

void
CameraComponent::setCameraType(CameraType type) noexcept
{
	_camera->setCameraType(type);
}

void
CameraComponent::setCameraOrder(CameraOrder order) noexcept
{
	_camera->setCameraOrder(order);
}

CameraType
CameraComponent::getCameraType() const noexcept
{
	return _camera->getCameraType();
}

CameraOrder
CameraComponent::getCameraOrder() const noexcept
{
	return _camera->getCameraOrder();
}

void
CameraComponent::load(iarchive& reader) noexcept
{
	std::string type;
	float aperture = 70.0;
	float znear = 0.1;
	float zfar = 1000.0;
	float4 viewport = float4::Zero;
	float4 ortho = float4::Zero;

	GameComponent::load(reader);

	reader >> make_archive(type, "type");
	reader >> make_archive(aperture, "aperture");
	reader >> make_archive(znear, "znear");
	reader >> make_archive(zfar, "zfar");
	reader >> make_archive(viewport, "viewport");
	reader >> make_archive(ortho, "ortho");

	this->setViewport(Viewport(viewport.x, viewport.y, viewport.z, viewport.w));

	if (type == "ortho")
	{
		this->setCameraType(CameraType::CT_ORTHO);
		this->makeOrtho(ortho.x, ortho.y, ortho.z, ortho.w, znear, zfar);
	}
	else
	{
		this->setCameraType(CameraType::CT_PERSPECTIVE);
		this->makePerspective(aperture, znear, zfar);
	}
}

void
CameraComponent::save(oarchive& write) noexcept
{
}

void
CameraComponent::onActivate() noexcept
{
	auto renderer = this->getGameObject()->getGameServer()->getFeature<RenderFeature>();
	if (renderer)
	{
		auto renderScene = renderer->getRenderScene(this->getGameObject()->getGameScene());
		if (renderScene)
		{
			_camera->makeLookAt(
				this->getGameObject()->getTranslate(),
				this->getGameObject()->getLookAt(),
				this->getGameObject()->getUpVector()
				);
			_camera->setRenderScene(renderScene);
		}
	}
}

void
CameraComponent::onDeactivate() noexcept
{
	_camera->setRenderScene(nullptr);
}

void
CameraComponent::onMoveAfter() noexcept
{
	_camera->makeLookAt(
		this->getGameObject()->getTranslate(),
		this->getGameObject()->getLookAt(),
		this->getGameObject()->getUpVector()
		);
}

GameComponentPtr
CameraComponent::clone() const noexcept
{
	auto instance = std::make_shared<CameraComponent>();
	instance->setName(this->getName());
	instance->_camera = _camera->clone();

	return instance;
}

_NAME_END
#endif