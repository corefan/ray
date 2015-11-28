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
#ifndef _H_MYGUI_BUTTON_H_
#define _H_MYGUI_BUTTON_H_

#include <ray/mygui_widget.h>

_NAME_BEGIN

class MyGuiButtonImpl final : public MyGuiWidget
{
	__DeclareSubClass(MyGuiButton, GuiWidget)
public:
	MyGuiButtonImpl() noexcept;
	virtual ~MyGuiButtonImpl() noexcept;

	bool create() except;

	Viewport getTextRegion() noexcept;
	void getTextSize(int& w, int& h) noexcept;

	void setText(const std::string& _value) noexcept;
	const std::string& getText() const noexcept;

	void setFontName(const std::string& _value) noexcept;
	const std::string& getFontName() noexcept;

	void setFontHeight(int _value) noexcept;
	int getFontHeight() noexcept;

	void setTextAlign(GuiWidgetAlign _value) noexcept;
	GuiWidgetAlign getTextAlign() noexcept;

	void setTextColour(const float4& value) noexcept;
	float4 getTextColour() noexcept;

	void setTextWithReplacing(const std::string& _value) noexcept;

	void setTextShadowColour(const float4& value) noexcept;
	float4 getTextShadowColour() noexcept;

	void setTextShadow(bool _value) noexcept;
	bool getTextShadow() const noexcept;

	void setStateSelected(bool value) noexcept;
	bool getStateSelected() const noexcept;

	void setModeImage(bool value) noexcept;
	bool getModeImage() const noexcept;

	void setImageResource(const std::string& name) noexcept;
	void setImageGroup(const std::string& name) noexcept;
	void setImageName(const std::string& name) noexcept;

private:

	std::string _caption;
	MyGUI::Button* _button;
	MyGUI::Widget* _parent;
};

class MyGuiButton final : public GuiButton
{
	__DeclareSubClass(MyGuiButton, GuiButton)
public:
	MyGuiButton() noexcept;
	virtual ~MyGuiButton() noexcept;

	virtual Viewport getTextRegion() noexcept;
	virtual void getTextSize(int& w, int& h) noexcept;

	virtual void setText(const std::string& _value) noexcept;
	virtual const std::string& getText() const noexcept;

	virtual void setFontName(const std::string& _value) noexcept;
	virtual const std::string& getFontName() noexcept;

	virtual void setFontHeight(int _value) noexcept;
	virtual int getFontHeight() noexcept;

	virtual void setTextAlign(GuiWidgetAlign _value) noexcept;
	virtual GuiWidgetAlign getTextAlign() noexcept;

	virtual void setTextColour(const float4& value) noexcept;
	virtual float4 getTextColour() noexcept;

	virtual void setTextWithReplacing(const std::string& _value) noexcept;

	virtual void setTextShadowColour(const float4& value) noexcept;
	virtual float4 getTextShadowColour() noexcept;

	virtual void setTextShadow(bool _value) noexcept;
	virtual bool getTextShadow() const noexcept;

	virtual void setStateSelected(bool value) noexcept;
	virtual bool getStateSelected() const noexcept;

	virtual void setModeImage(bool value) noexcept;
	virtual bool getModeImage() const noexcept;

	virtual void setImageResource(const std::string& name) noexcept;
	virtual void setImageGroup(const std::string& name) noexcept;
	virtual void setImageName(const std::string& name) noexcept;

private:

	MyGuiButtonImpl _impl;
};

_NAME_END

#endif