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
#ifndef _H_GUI_WIDGET_H_
#define _H_GUI_WIDGET_H_

#include <ray/gui_align.h>

_NAME_BEGIN

class EXPORT GuiWidgetImpl : public rtti::Interface
{
	__DeclareSubInterface(GuiWidget, rtti::Interface)
public:
	GuiWidgetImpl() noexcept;
	virtual ~GuiWidgetImpl() noexcept;

	virtual void create(const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name, void* widget) except = 0;
	virtual void destroy() noexcept = 0;

	virtual void setSkin(const std::string& skin) except = 0;
	virtual const std::string& getSkin() const noexcept = 0;

	virtual void setViewport(const Viewport& view) except = 0;
	virtual void getViewport(Viewport& view) const noexcept = 0;

	virtual GuiWidgetPtr createWieght(const rtti::Rtti* rtti, const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name = "") except = 0;
};

class EXPORT GuiWidget : public rtti::Interface
{
	__DeclareSubInterface(GuiWidget, rtti::Interface)
public:
	GuiWidget(GuiWidgetImpl& impl) noexcept;
	virtual ~GuiWidget() noexcept;

	GuiWidgetPtr createWieght(const rtti::Rtti* rtti, const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name = "") except;
	
	template<typename T>
	std::shared_ptr<T> createWieght(const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name = "") except
	{
		return std::dynamic_pointer_cast<T>(this->createWieght(T::getRtti(), skin, left, top, width, height, align, name));
	}
	
	void create(const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name = "") except;
	void create(const std::string& skin, int left, int top, int width, int height, GuiWidgetAlign align, const std::string& name, void* widget) except;
	void destroy() noexcept;

	void setSkin(const std::string& skin) except;
	const std::string& getSkin() const noexcept;

	void setViewport(const Viewport& view) except;
	void getViewport(Viewport& view) const noexcept;
private:

	GuiWidgetImpl& _impl;
};

_NAME_END

#endif