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
#ifndef _H_NDK_INPUT_DEVICE_H_
#define _H_NDK_INPUT_DEVICE_H_

#include <ray/input_device_base.h>

_NAME_BEGIN

class EXPORT NDKInputDevice : public InputDevice
{
	__DeclareSubInterface(NDKInputDevice, InputDevice)
public:
	NDKInputDevice() noexcept;

	virtual void setCaptureObject(CaptureObject window) noexcept;
	virtual CaptureObject getCaptureObject() const noexcept;

	virtual bool injectTouchMove(int _absx, int _absy, InputButton::Code _id) noexcept;
	virtual bool injectTouchPress(int _absx, int _absy, InputButton::Code _id) noexcept;
	virtual bool injectTouchRelease(int _absx, int _absy, InputButton::Code _id) noexcept;
	virtual bool injectTouchCancel(InputButton::Code _id) noexcept;

	virtual bool injectCharacter(InputKey::Code _key, std::uint32_t _char) noexcept;

	virtual bool peekEvents(InputEvent& event) noexcept;
	virtual bool pollEvents(InputEvent& event) noexcept;
	virtual bool waitEvents(InputEvent& event) noexcept;
	virtual bool waitEvents(InputEvent& event, int timeout) noexcept;
	virtual void flushEvent() noexcept;

private:
	NDKInputDevice(const NDKInputDevice&) noexcept = delete;
	NDKInputDevice& operator=(const NDKInputDevice&) noexcept = delete;

private:

	bool _isButtonPress;

	int _button[InputButton::Code::NumButtonCodes];

	int _mouseX[InputButton::Code::NumButtonCodes];
	int _mouseY[InputButton::Code::NumButtonCodes];
};

_NAME_END

#endif