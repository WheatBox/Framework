#include <FrameCore/IApplication.h>
#include <FrameCore/Globals.h>
#include <FrameRender/Renderer.h>
#include <FrameEntity/EntitySystem.h>
#include <FrameInput/Input.h>
#include <FrameAudio/AudioPlayer.h>
#include <FrameCore/Camera.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

namespace Frame {

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

	void IApplication::SetWindowSize(const Frame::Vec2i & siz) {
		glfwSetWindowSize(m_pWindow, siz.x, siz.y);
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
			std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

			gInput->Process();
			gAudioPlayer->Process();

			gRenderer->RenderBegin();

			MainLoopPriority();
			/* ------------- Main Loop ------------- */

			float _frameTime = static_cast<float>(frameTime.count());
			gEntitySystem->ProcessBeforeUpdateEvent(_frameTime);
			gEntitySystem->ProcessUpdateEvent(_frameTime);
			gEntitySystem->ProcessAfterUpdateEvent(_frameTime);

			gEntitySystem->ProcessRenderEvent();

			/* ------------------------------------- */
			MainLoopLast();

			gRenderer->RenderEnd();

			glfwSwapBuffers(m_pWindow);
			glfwPollEvents();

			if(!m_bVSync && m_maxFPS != 0) {
				// https://github.com/erincatto/box2d/blob/main/testbed/main.cpp

				// Throttle to cap at 60Hz. This adaptive using a sleep adjustment. This could be improved by
				// using mm_pause or equivalent for the last millisecond.
				std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
				std::chrono::duration<double> timeUsed = t2 - t1;
				std::chrono::duration<double> sleepTime = m_targetFrameTime - timeUsed + sleepAdjust;
				if (sleepTime > std::chrono::duration<double>(0))
				{
					std::this_thread::sleep_for(sleepTime);
				}

				std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
				frameTime = t3 - t1;

				// Compute the sleep adjustment using a low pass filter
				sleepAdjust = 0.9 * sleepAdjust + 0.1 * (m_targetFrameTime - frameTime);
			} else {
				frameTime = std::chrono::steady_clock::now() - t1;
			}
		}

		Terminate();
	}

	void IApplication::SetVSync(bool bEnable) {
		m_bVSync = bEnable;
		glfwSwapInterval(bEnable);
	}

}