#pragma once

#include <chrono> // for m_maxFrameDelay
#include <tuple>

#include <FrameCore/Log.h>

struct GLFWwindow;

namespace Frame {

	class CShader;

	struct IApplication {
	protected:
		GLFWwindow * m_pWindow = nullptr;

	public:
		int EntryPoint(int argc, char ** argv) {
			if(!InitializeWindow("Framework", m_windowSize.first, m_windowSize.second)) {
				Log::Log(Log::ELevel::Fatal, "Can not initialize the window! The program will be terminated.");
				Terminate();
				return -1;
			}
			
			SetVSync(true);

			Initialize(argc, argv);
			Run();
			return 0;
		}

		void Terminate();

		const std::pair<int, int> & GetWindowSize() const {
			return m_windowSize;
		}
		void SetWindowSize(const std::pair<int, int> & siz);

	protected:

		bool InitializeWindow(const char * title, int windowWidth, int windowHeight);
		void Run();

		virtual void Initialize(int argc, char ** argv) = 0;

		virtual void MainLoopPriority() {}
		virtual void MainLoopLast() {}

		bool GetVSync() const { return m_bVSync; }
		void SetVSync(bool bEnable);

		int GetMaxFPS() const { return m_maxFPS; }
		// 0 = 无限大 | Infinite
		void SetMaxFPS(int fps) {
			m_maxFPS = fps > 0 ? fps : 0;

			if(m_maxFPS != 0) {
				m_maxFrameDelay = std::chrono::microseconds(1000000 / fps);
			}
		}

		int m_maxFPS = 0;

		bool m_quit = false;

	private:
		bool m_bVSync = true;
		std::chrono::microseconds m_maxFrameDelay { 0 };

		std::pair<int, int> m_windowSize { 800, 600 };

	};

}