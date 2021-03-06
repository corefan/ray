// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
// +----------------------------------------------------------------------
// | * Redistribution and use of _renderThread software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, _renderThread list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, _renderThread list of conditions and the
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
#if defined(_BUILD_GUI)
#include <ray/gui_button_component.h>
#include <ray/gui_label_component.h>
#include <ray/gui_button.h>
#include <ray/gui_system.h>

_NAME_BEGIN

__ImplementSubClass(GuiButtonComponent, GuiWidgetComponent, "GuiButton")

GuiButtonComponent::GuiButtonComponent() noexcept
{
	_button = GuiSystem::instance()->createWidget<GuiButton>();
	_button->create();

	_label = std::make_shared<GuiLabelComponent>(_button->getGuiTextBox());
	_labelObject = std::make_shared<GameObject>();
	_labelObject->addComponent(_label);

	this->setGuiWidget(_button);
}

GuiButtonComponent::GuiButtonComponent(GuiButtonPtr button) noexcept
	:_button(button)
{
	_label = std::make_shared<GuiLabelComponent>(_button->getGuiTextBox());
	_labelObject = std::make_shared<GameObject>();
	_labelObject->addComponent(_label);

	this->setGuiWidget(_button);
}

GuiButtonComponent::~GuiButtonComponent() noexcept
{
}

void
GuiButtonComponent::setStateSelected(bool value) noexcept
{
	assert(_button);
	_button->setStateSelected(value);
}

bool
GuiButtonComponent::getStateSelected() const noexcept
{
	assert(_button);
	return _button->getStateSelected();
}

void
GuiButtonComponent::setModeImage(bool value) noexcept
{
	assert(_button);
	_button->setModeImage(value);
}

bool
GuiButtonComponent::getModeImage() const noexcept
{
	assert(_button);
	return _button->getModeImage();
}

void
GuiButtonComponent::setImageResource(const std::string& name) noexcept
{
	assert(_button);
	_button->setImageResource(name);
}

void
GuiButtonComponent::setImageGroup(const std::string& name) noexcept
{
	assert(_button);
	_button->setImageGroup(name);
}

void
GuiButtonComponent::setImageName(const std::string& name) noexcept
{
	assert(_button);
	_button->setImageName(name);
}

void
GuiButtonComponent::onAttach() except
{
	assert(_labelObject);
	_labelObject->setParent(this->getGameObject());
}

void
GuiButtonComponent::onDetach() noexcept
{
	assert(_labelObject);
	_labelObject->setParent(nullptr);
}

void
GuiButtonComponent::load(iarchive& reader) noexcept
{
	assert(_label);
	_label->load(reader);

	bool state = false;
	bool mode = false;
	std::string name, group, resource;

	reader >> make_archive(state, "state");
	reader >> make_archive(mode, "mode");
	reader >> make_archive(name, "name");
	reader >> make_archive(group, "group");
	reader >> make_archive(resource, "resource");

	this->setStateSelected(state);
	this->setModeImage(mode);
	this->setImageName(name);
	this->setImageGroup(group);
	this->setImageResource(resource);
}

void
GuiButtonComponent::save(oarchive& write) noexcept
{
	assert(_label);
	_label->save(write);

	bool state = this->getStateSelected();
	bool mode = this->getModeImage();
	std::string name, group, resource;

	write << make_archive(state, "state");
	write << make_archive(mode, "mode");
	write << make_archive(name, "name");
	write << make_archive(group, "group");
	write << make_archive(resource, "resource");
}

GameComponentPtr
GuiButtonComponent::clone() const noexcept
{
	return std::make_shared<GuiButtonComponent>();
}

_NAME_END

#endif