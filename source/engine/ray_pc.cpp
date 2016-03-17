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
#if defined(_BUILD_PLATFORM_WINDOWS)
#include <ray/ray.h>

#include <ray/game_application.h>

#include <ray/fcntl.h>

#include <ray/input_event.h>
#include <ray/input_feature.h>

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

RAY_C_LINKAGE int RAY_CALL ray_main(int argc, const char* argv[]);

GLFWwindow* _window = nullptr;
ray::GameApplicationPtr _gameApp;
ray::util::string _gameRootPath;
ray::util::string _gameScenePath;

void onWindowResize(GLFWwindow* glfwWindow, int w, int h)
{
	_gameApp->setWindowResolution(w, h);
}

void onWindowClose(GLFWwindow* glfwWindow)
{
	ray::InputEvent inputEvent;
	inputEvent.event = ray::InputEvent::AppQuit;

	auto event = ray::make_message<ray::InputMessage>();
	event->setEvent(inputEvent);

	_gameApp->sendMessage(event);
}

void onWindowFocus(GLFWwindow* glfwWindow, int focus)
{
	if (focus)
	{
		ray::InputEvent inputEvent;
		inputEvent.event = ray::InputEvent::GetFocus;

		auto event = ray::make_message<ray::InputMessage>();
		event->setEvent(inputEvent);

		_gameApp->sendMessage(event);
	}
	else
	{
		ray::InputEvent inputEvent;
		inputEvent.event = ray::InputEvent::LostFocus;

		auto event = ray::make_message<ray::InputMessage>();
		event->setEvent(inputEvent);

		_gameApp->sendMessage(event);
	}
}

void rayInit(const char* gamedir, const char* scenename) noexcept
{
	if (gamedir)
	{
		if (ray::fcntl::access(gamedir, 0) == 0)
			_gameRootPath = ray::util::directory(gamedir);
	}

	if (scenename)
		_gameScenePath = scenename;
}

void rayTerminate() noexcept
{
	rayCloseWindow();
	::glfwTerminate();
}

bool rayOpenWindow(const char* title, int w, int h) noexcept
{
	assert(!_gameApp && !_window);

	if (::glfwInit() == GL_FALSE)
		return false;

	_window = ::glfwCreateWindow(w, h, title, nullptr, nullptr);
	if (_window)
	{
		::glfwSetWindowUserPointer(_window, nullptr);
		::glfwSetWindowFocusCallback(_window, &onWindowFocus);
		::glfwSetWindowCloseCallback(_window, &onWindowClose);

		HWND hwnd = ::glfwGetWin32Window(_window);

		_gameApp = std::make_shared<ray::GameApplication>();
		_gameApp->setFileService(true);
		_gameApp->setFileServicePath(_gameRootPath);

		if (!_gameApp->open(hwnd, w, h))
			return false;

		if (!_gameScenePath.empty())
		{
			if (!_gameApp->openScene(_gameScenePath))
				return false;
		}			

		return true;
	}
	
	return false;
}

void rayCloseWindow() noexcept
{
	if (_gameApp)
	{
		_gameApp.reset();
		_gameApp = nullptr;
	}

	if (_window)
	{
		::glfwDestroyWindow(_window);
		_window = nullptr;
	}
	
	::glfwTerminate();
}

bool rayIsQuitRequest() noexcept
{
	return ::glfwWindowShouldClose(_window) ? true : false;
}

void rayUpdate() noexcept
{
	if (_gameApp)
		_gameApp->update();
}

int main(int argc, const char* argv[]) noexcept
{
	if (argc != 0)
	{
		if (ray::fcntl::access(argv[0], 0) == 0)
			_gameRootPath = ray::util::directory(argv[0]);
	}

	return ray_main(argc, argv);
}

#endif