#include "IApplication.h"

#include "../FrameCore/Globals.h"
#include "../FrameRender/Renderer.h"
#include "../FrameEntity/EntitySystem.h"
#include "../FrameInput/Input.h"
#include "../FrameAudio/AudioPlayer.h"
#include "../FrameCore/Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace Frame {

	int __maxFPS = 0;
	bool __bVSync = true;
	std::chrono::duration<double> __targetFrameTime { 0.0 };
	float __frameTime = 0.f, __maxFrameTime = 1.f;

	bool GetVSync() {
		return __bVSync;
	}

	void SetVSync(bool bEnable) {
		__bVSync = bEnable;
		glfwSwapInterval(bEnable);
	}

	int GetMaxFPS() {
		return __maxFPS;
	}

	void SetMaxFPS(int fps) {
		__maxFPS = fps > 0 ? fps : 0;

		if(__maxFPS != 0) {
			__targetFrameTime = std::chrono::duration<double> { 1.0 / static_cast<double>(fps) };
		}
	}

	float GetFrameTime(bool ignoreMaxFrameTime) {
		if(ignoreMaxFrameTime) {
			return __frameTime;
		}
		return Min(__frameTime, __maxFrameTime);
	}

	void SetMaxFrameTime(float time) {
		__maxFrameTime = time;
	}

	float GetMaxFrameTime() {
		return __maxFrameTime;
	}

	void IApplication::Terminate() {
		delete gRenderer;
		gRenderer = nullptr;

		delete gEntitySystem;
		gEntitySystem = nullptr;

		delete gInput;
		gInput = nullptr;

		delete gAudioPlayer;
		gAudioPlayer = nullptr;

		glfwTerminate();
	}

	Frame::Vec2i IApplication::GetWindowSize() const {
		int w = 0, h = 0;
		glfwGetWindowSize(m_pWindow, & w, & h);
		return { w, h };
	}

	void IApplication::SetWindowSize(const Frame::Vec2i & siz) const {
		glfwSetWindowSize(m_pWindow, siz.x, siz.y);
	}

	void IApplication::SetCursorMode(ECursorMode mode) const {
		switch(mode) {
		case ECursorMode::Normal:
			glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case ECursorMode::Hidden:
			glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case ECursorMode::Disabled:
			glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		}
	}

	IApplication::ECursorMode IApplication::GetCursorMode() const {
		switch(glfwGetInputMode(m_pWindow, GLFW_CURSOR)) {
		case GLFW_CURSOR_NORMAL:
			return ECursorMode::Normal;
		case GLFW_CURSOR_HIDDEN:
			return ECursorMode::Hidden;
		case GLFW_CURSOR_DISABLED:
			return ECursorMode::Disabled;
		}
		return ECursorMode::Normal;
	}

	bool IApplication::InitializeWindow(const char * title, const Frame::Vec2i & windowSize) {
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_pWindow = glfwCreateWindow(windowSize.x, windowSize.y, title, NULL, NULL);
		if(!m_pWindow) {
			Log::Log(Log::ELevel::Fatal, "Failed to create the window \"%s\"", title);
			return false;
		}
		glfwMakeContextCurrent(m_pWindow);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Log::Log(Log::ELevel::Fatal, "Failed to initialize GLAD");
			return false;
		}

		gRenderer->Initialize();
		glfwSetFramebufferSizeCallback(m_pWindow,
			[](GLFWwindow *, int width, int height) {
				gCamera->__SetWindowSize({ width, height });
			}
		);

		gInput->Initialize(m_pWindow);
		gAudioPlayer->Initialize();
		gCamera->__SetWindowSize(windowSize);
		gCamera->SetViewSize(windowSize);

		return true;
	}

	void IApplication::Run() {
		std::chrono::duration<double> frameTime(0.0);
		std::chrono::duration<double> sleepAdjust(0.0);
		while(!glfwWindowShouldClose(m_pWindow)) {
			
			__frameTime = static_cast<float>(frameTime.count());

			std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

			gInput->Process();
			gAudioPlayer->Process();

			gRenderer->RenderBegin();

			MainLoopPriority();
			/* ------------- Main Loop ------------- */

			gEntitySystem->__ProcessBeforeUpdateEvent();
			gEntitySystem->__ProcessUpdateEvent();
			gEntitySystem->__ProcessAfterUpdateEvent();

			gEntitySystem->__ProcessRenderEvent();

			/* ------------------------------------- */
			MainLoopLast();

			gRenderer->RenderEnd();

			gEntitySystem->__AddAddingComponents();
			gEntitySystem->__RemoveRemovingEntitiesComponents();
			gEntitySystem->__RemoveRemovingComponents();
			gEntitySystem->__RemoveRemovingEntities();

			glfwSwapBuffers(m_pWindow);
			glfwPollEvents();

			if(!__bVSync && __maxFPS != 0) {
				// https://github.com/erincatto/box2d/blob/main/testbed/main.cpp

				// Throttle to cap at 60Hz. This adaptive using a sleep adjustment. This could be improved by
				// using mm_pause or equivalent for the last millisecond.
				std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
				std::chrono::duration<double> timeUsed = t2 - t1;
				std::chrono::duration<double> sleepTime = __targetFrameTime - timeUsed + sleepAdjust;
				if (sleepTime > std::chrono::duration<double>(0))
				{
					std::this_thread::sleep_for(sleepTime);
				}

				std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
				frameTime = t3 - t1;

				// Compute the sleep adjustment using a low pass filter
				sleepAdjust = 0.9 * sleepAdjust + 0.1 * (__targetFrameTime - frameTime);
			} else {
				frameTime = std::chrono::steady_clock::now() - t1;
			}
		}

		Terminate();
	}

}