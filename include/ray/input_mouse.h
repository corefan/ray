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
#ifndef _H_INPUT_MOUSE_H_
#define _H_INPUT_MOUSE_H_

#include <ray/input_mouse_base.h>

_NAME_BEGIN

class EXPORT DefaultInputMouse : public InputMouse
{
	__DeclareSubClass(DefaultInputMouse, InputMouse)
public:
	DefaultInputMouse() noexcept;
	virtual ~DefaultInputMouse() noexcept;

	void lockMouse() noexcept;
	void unlockMouse() noexcept;
	bool isLockedMouse() const noexcept;

	void showMouse() noexcept;
	void hideMouse() noexcept;
	bool isShowMouse() noexcept;

	void setPosition(int x, int y) noexcept;
	void getPosition(int& x, int& y) const noexcept;

	bool getButtonDown(InputButton::Code key) const noexcept;
	bool getButtonUp(InputButton::Code key) const noexcept;

	bool getButton(InputButton::Code key) const noexcept;

protected:
	void onFrameBegin() noexcept;
	void onFrameEnd() noexcept;

	void onObtainCapture() noexcept;
	void onReleaseCapture() noexcept;

	void onInputEvent(const InputEvent& event) noexcept;

private:
	virtual void onShowMouse() noexcept = 0;
	virtual void onHideMouse() noexcept = 0;

	virtual void onChangePosition(int x, int y) noexcept = 0;

private:
	DefaultInputMouse(const DefaultInputMouse&) noexcept = delete;
	DefaultInputMouse& operator=(const DefaultInputMouse&) noexcept = delete;

private:

	bool _isMouseLock;
	bool _isMouseLocked;

	bool _isMouseHide;

	int _lockX;
	int _lockY;

	int _mouseX;
	int _mouseY;

	struct ButtonState
	{
		bool down;
		bool up;
		bool pressed;
		bool click;
	};

	ButtonState _buttonState[InputButton::NumButtonCodes];
};

_NAME_END

#endif