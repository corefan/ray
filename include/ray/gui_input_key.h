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
#ifndef _H_GUI_INPUT_KEY_H_
#define _H_GUI_INPUT_KEY_H_

#include <ray/gui_types.h>

_NAME_BEGIN

class GuiInputKey
{
public:
	enum Code
	{
		None = 0x00,
		Escape = 0x01,
		One = 0x02,
		Two = 0x03,
		Three = 0x04,
		Four = 0x05,
		Five = 0x06,
		Six = 0x07,
		Seven = 0x08,
		Eight = 0x09,
		Nine = 0x0A,
		Zero = 0x0B,
		Minus = 0x0C,    /* - on main keyboard */
		Equals = 0x0D,
		Backspace = 0x0E,    /* Backspace */
		Tab = 0x0F,
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		LeftBracket = 0x1A,
		RightBracket = 0x1B,
		Return = 0x1C,    /* Enter on main keyboard */
		LeftControl = 0x1D,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		Semicolon = 0x27,
		Apostrophe = 0x28,
		GraveAccent = 0x29,    /* Accent grave ( ~ ) */
		LeftShift = 0x2A,
		Backslash = 0x2B,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,
		Comma = 0x33,
		Period = 0x34,    /* . on main keyboard */
		Slash = 0x35,    /* '/' on main keyboard */
		RightShift = 0x36,
		Multiply = 0x37,    /* * on numeric keypad */
		LeftAlt = 0x38,    /* Left Alt */
		Space = 0x39,
		Capital = 0x3A,
		F1 = 0x3B,
		F2 = 0x3C,
		F3 = 0x3D,
		F4 = 0x3E,
		F5 = 0x3F,
		F6 = 0x40,
		F7 = 0x41,
		F8 = 0x42,
		F9 = 0x43,
		F10 = 0x44,
		NumLock = 0x45,
		ScrollLock = 0x46,    /* Scroll Lock */
		Numpad7 = 0x47,
		Numpad8 = 0x48,
		Numpad9 = 0x49,
		Subtract = 0x4A,    /* - on numeric keypad */
		Numpad4 = 0x4B,
		Numpad5 = 0x4C,
		Numpad6 = 0x4D,
		Add = 0x4E,    /* + on numeric keypad */
		Numpad1 = 0x4F,
		Numpad2 = 0x50,
		Numpad3 = 0x51,
		Numpad0 = 0x52,
		Decimal = 0x53,    /* . on numeric keypad */
		OEM_102 = 0x56,    /* < > | on UK/Germany keyboards */
		F11 = 0x57,
		F12 = 0x58,
		F13 = 0x64,    /*                     (NEC PC98) */
		F14 = 0x65,    /*                     (NEC PC98) */
		F15 = 0x66,    /*                     (NEC PC98) */
		Kana = 0x70,    /* (Japanese keyboard)            */
		ABNT_C1 = 0x73,    /* / ? on Portugese (Brazilian) keyboards */
		Convert = 0x79,    /* (Japanese keyboard)            */
		NoConvert = 0x7B,    /* (Japanese keyboard)            */
		Yen = 0x7D,    /* (Japanese keyboard)            */
		ABNT_C2 = 0x7E,    /* Numpad . on Portugese (Brazilian) keyboards */
		NumpadEquals = 0x8D,    /* = on numeric keypad (NEC PC98) */
		PrevTrack = 0x90,    /* Previous Track (KC_CIRCUMFLEX on Japanese keyboard) */
		At = 0x91,    /*                     (NEC PC98) */
		Colon = 0x92,    /*                     (NEC PC98) */
		Underline = 0x93,    /*                     (NEC PC98) */
		Kanji = 0x94,    /* (Japanese keyboard)            */
		Stop = 0x95,    /*                     (NEC PC98) */
		AX = 0x96,    /*                     (Japan AX) */
		Unlabeled = 0x97,    /*                        (J3100) */
		NextTrack = 0x99,    /* Next Track */
		NumpadEnter = 0x9C,    /* Enter on numeric keypad */
		RightControl = 0x9D,
		Mute = 0xA0,
		Calculator = 0xA1,
		PlayPause = 0xA2,    /* Play / Pause */
		MediaStop = 0xA4,    /* Media Stop */
		VolumeDown = 0xAE,    /* Volume - */
		VolumeUp = 0xB0,    /* Volume + */
		WebHome = 0xB2,    /* Web home */
		NumpadComma = 0xB3,    /* , on numeric keypad (NEC PC98) */
		Divide = 0xB5,    /* / on numeric keypad */
		SysRq = 0xB7,
		RightAlt = 0xB8,    /* Right Alt */
		Pause = 0xC5,
		Home = 0xC7,    /* Home on arrow keypad */
		ArrowUp = 0xC8,    /* UpArrow on arrow keypad */
		PageUp = 0xC9,    /* PgUp on arrow keypad */
		ArrowLeft = 0xCB,    /* LeftArrow on arrow keypad */
		ArrowRight = 0xCD,    /* RightArrow on arrow keypad */
		End = 0xCF,    /* End on arrow keypad */
		ArrowDown = 0xD0,    /* DownArrow on arrow keypad */
		PageDown = 0xD1,    /* PgDn on arrow keypad */
		Insert = 0xD2,    /* Insert on arrow keypad */
		Delete = 0xD3,    /* Delete on arrow keypad */
		LeftWindows = 0xDB,    /* Left Windows key */
		RightWindow = 0xDC,    /* Right Windows key */
		RightWindows = 0xDC,    /* Right Windows key - Correct spelling :) */
		AppMenu = 0xDD,    /* AppMenu key */
		Power = 0xDE,    /* System Power */
		Sleep = 0xDF,    /* System Sleep */
		Wake = 0xE3,    /* System Wake */
		WebSearch = 0xE5,
		WebFavorites = 0xE6,
		WebRefresh = 0xE7,
		WebStop = 0xE8,
		WebForward = 0xE9,
		WebBack = 0xEA,
		MyComputer = 0xEB,
		Mail = 0xEC,
		MediaSelect = 0xED
	};
};

/*
GuiInputButton::Code ButtonCodeToGuiButton(InputButton::Code button) noexcept
{
	switch (button)
	{
	case InputButton::LEFT:
		return GuiInputButton::Code::Left;
	case InputButton::RIGHT:
		return GuiInputButton::Code::Right;
	case InputButton::MIDDLE:
		return GuiInputButton::Code::Middle;
	case InputButton::MOUSE3:
		return GuiInputButton::Code::Button3;
	case InputButton::MOUSE4:
		return GuiInputButton::Code::Button4;
	case InputButton::MOUSE5:
		return GuiInputButton::Code::Button5;
	case InputButton::MOUSE6:
		return GuiInputButton::Code::Button6;
	case InputButton::MOUSE7:
		return GuiInputButton::Code::Button7;
	case InputButton::MOUSE8:
	case InputButton::MOUSELAST:
	case InputButton::MOUSEWHEEL:
	case InputButton::MOUSEX:
	case InputButton::MOUSEY:
	case InputButton::MOUSEZ:
		return GuiInputButton::Code::None;
	default:
		return GuiInputButton::Code::None;
	}
}

GuiInputKey::Code KeyCodetoGuiKey(InputKey::Code key) noexcept
{
	switch (key)
	{
	case InputKey::None:
		return GuiInputKey::Code::None;
	case InputKey::Backspace:
		return GuiInputKey::Code::Backspace;
	case InputKey::Tab:
		return GuiInputKey::Code::Tab;
	case InputKey::Enter:
		return GuiInputKey::Code::Return;
	case InputKey::Pause:
		return GuiInputKey::Code::Pause;
	case InputKey::Escape:
		return GuiInputKey::Code::Escape;
	case InputKey::Space:
		return GuiInputKey::Code::Space;
	case InputKey::PageDown:
		return GuiInputKey::Code::NextTrack;
	case InputKey::End:
		return GuiInputKey::Code::End;
	case InputKey::Home:
		return GuiInputKey::Code::Home;
	case InputKey::Left:
		return GuiInputKey::Code::ArrowLeft;
	case InputKey::Right:
		return GuiInputKey::Code::ArrowRight;
	case InputKey::Up:
		return GuiInputKey::Code::ArrowUp;
	case InputKey::Down:
		return GuiInputKey::Code::ArrowDown;
	case InputKey::Insert:
		return GuiInputKey::Code::Insert;
	case InputKey::Delete:
		return GuiInputKey::Code::Delete;
	case InputKey::KP_0:
		return GuiInputKey::Code::Numpad0;
	case InputKey::KP_1:
		return GuiInputKey::Code::Numpad1;
	case InputKey::KP_2:
		return GuiInputKey::Code::Numpad2;
	case InputKey::KP_3:
		return GuiInputKey::Code::Numpad3;
	case InputKey::KP_4:
		return GuiInputKey::Code::Numpad4;
	case InputKey::KP_5:
		return GuiInputKey::Code::Numpad5;
	case InputKey::KP_6:
		return GuiInputKey::Code::Numpad6;
	case InputKey::KP_7:
		return GuiInputKey::Code::Numpad7;
	case InputKey::KP_8:
		return GuiInputKey::Code::Numpad8;
	case InputKey::KP_9:
		return GuiInputKey::Code::Numpad9;
	case InputKey::KP_Multiply:
		return GuiInputKey::Code::Multiply;
	case InputKey::KP_Add:
		return GuiInputKey::Code::Add;
	case InputKey::KP_Subtract:
		return GuiInputKey::Code::Subtract;
	case InputKey::KP_Decimal:
		return GuiInputKey::Code::Decimal;
	case InputKey::KP_Divide:
		return GuiInputKey::Code::Divide;
	case InputKey::F1:
		return GuiInputKey::Code::F1;
	case InputKey::F2:
		return GuiInputKey::Code::F2;
	case InputKey::F3:
		return GuiInputKey::Code::F3;
	case InputKey::F4:
		return GuiInputKey::Code::F4;
	case InputKey::F5:
		return GuiInputKey::Code::F5;
	case InputKey::F6:
		return GuiInputKey::Code::F6;
	case InputKey::F7:
		return GuiInputKey::Code::F7;
	case InputKey::F8:
		return GuiInputKey::Code::F8;
	case InputKey::F9:
		return GuiInputKey::Code::F9;
	case InputKey::F10:
		return GuiInputKey::Code::F10;
	case InputKey::F11:
		return GuiInputKey::Code::F11;
	case InputKey::F12:
		return GuiInputKey::Code::F12;
	case InputKey::F13:
		return GuiInputKey::Code::F13;
	case InputKey::F14:
		return GuiInputKey::Code::F14;
	case InputKey::F15:
		return GuiInputKey::Code::F15;
	case InputKey::NumLock:
		return GuiInputKey::Code::NumLock;
	case InputKey::ScrollLock:
		return GuiInputKey::Code::ScrollLock;
	case InputKey::Semicolon:
		return GuiInputKey::Code::Semicolon;
	case InputKey::Slash:
		return GuiInputKey::Code::Slash;
	case InputKey::GraveAccent:
		return GuiInputKey::Code::GraveAccent;
	case InputKey::LeftBracket:
		return GuiInputKey::Code::LeftBracket;
	case InputKey::RightBracket:
		return GuiInputKey::Code::RightBracket;
	case InputKey::Backslash:
		return GuiInputKey::Code::Backslash;
	case InputKey::Comma:
		return GuiInputKey::Code::Comma;
	case InputKey::Minus:
		return GuiInputKey::Code::Minus;
	case InputKey::Period:
		return GuiInputKey::Code::Period;
	case InputKey::Equal:
		return GuiInputKey::Code::Equals;
	case InputKey::LeftShift:
		return GuiInputKey::Code::LeftShift;
	case InputKey::RightShift:
		return GuiInputKey::Code::RightShift;
	case InputKey::LeftControl:
		return GuiInputKey::Code::LeftControl;
	case InputKey::RightControl:
		return GuiInputKey::Code::RightControl;
	case InputKey::LeftSuper:
		return GuiInputKey::Code::LeftWindows;
	case InputKey::RightSuper:
		return GuiInputKey::Code::RightWindows;
	case InputKey::VolumeDown:
		return GuiInputKey::Code::VolumeDown;
	case InputKey::VolumeUp:
		return GuiInputKey::Code::VolumeUp;
	case InputKey::Key0:
		return GuiInputKey::Code::Zero;
	case InputKey::Key1:
		return GuiInputKey::Code::One;
	case InputKey::Key2:
		return GuiInputKey::Code::Two;
	case InputKey::Key3:
		return GuiInputKey::Code::Three;
	case InputKey::Key4:
		return GuiInputKey::Code::Four;
	case InputKey::Key5:
		return GuiInputKey::Code::Five;
	case InputKey::Key6:
		return GuiInputKey::Code::Six;
	case InputKey::Key7:
		return GuiInputKey::Code::Seven;
	case InputKey::Key8:
		return GuiInputKey::Code::Eight;
	case InputKey::Key9:
		return GuiInputKey::Code::Nine;
	case InputKey::A:
		return GuiInputKey::Code::A;
	case InputKey::B:
		return GuiInputKey::Code::B;
	case InputKey::C:
		return GuiInputKey::Code::C;
	case InputKey::D:
		return GuiInputKey::Code::D;
	case InputKey::E:
		return GuiInputKey::Code::E;
	case InputKey::F:
		return GuiInputKey::Code::F;
	case InputKey::G:
		return GuiInputKey::Code::G;
	case InputKey::H:
		return GuiInputKey::Code::H;
	case InputKey::I:
		return GuiInputKey::Code::I;
	case InputKey::J:
		return GuiInputKey::Code::J;
	case InputKey::K:
		return GuiInputKey::Code::K;
	case InputKey::L:
		return GuiInputKey::Code::L;
	case InputKey::M:
		return GuiInputKey::Code::M;
	case InputKey::N:
		return GuiInputKey::Code::N;
	case InputKey::O:
		return GuiInputKey::Code::O;
	case InputKey::P:
		return GuiInputKey::Code::P;
	case InputKey::Q:
		return GuiInputKey::Code::Q;
	case InputKey::R:
		return GuiInputKey::Code::R;
	case InputKey::S:
		return GuiInputKey::Code::S;
	case InputKey::T:
		return GuiInputKey::Code::T;
	case InputKey::U:
		return GuiInputKey::Code::U;
	case InputKey::V:
		return GuiInputKey::Code::V;
	case InputKey::W:
		return GuiInputKey::Code::W;
	case InputKey::X:
		return GuiInputKey::Code::X;
	case InputKey::Y:
		return GuiInputKey::Code::Y;
	case InputKey::Z:
		return GuiInputKey::Code::Z;
	default:
		return GuiInputKey::Code::None;
	}
}
*/

_NAME_END

#endif