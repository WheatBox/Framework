#pragma once

#include <chrono> // for m_maxFrameDelay

#include <FrameCore/Log.h>
#include <FrameMath/Vector2.h>

struct GLFWwindow;

namespace Frame {

	class CShader;

	struct IApplication {
	protected:
		GLFWwindow * m_pWindow = nullptr;

	public:
		int EntryPoint(const char * title, const Frame::Vec2i & windowSize) {
			if(!InitializeWindow(title, windowSize)) {
				Log::Log(Log::ELevel::Fatal, "Can not initialize the window! The program will be terminated.");
				Terminate();
				return -1;
			}
			
			SetVSync(true);

			Initialize();
			Run();
			return 0;
		}

		void Terminate();

		Frame::Vec2i GetWindowSize() const;
		void SetWindowSize(const Frame::Vec2i & siz);

	protected:

		bool InitializeWindow(const char * title, const Frame::Vec2i & windowSize);
		void Run();

		virtual void Initialize() = 0;

		virtual void MainLoopPriority() {}
		virtual void MainLoopLast() {}

		bool GetVSync() const { return m_bVSync; }
		void SetVSync(bool bEnable);

		int GetMaxFPS() const { return m_maxFPS; }
		// 0 = 无限大 | Infinite
		void SetMaxFPS(int fps) {
			m_maxFPS = fps > 0 ? fps : 0;

			if(m_maxFPS != 0) {
				m_targetFrameTime = std::chrono::duration<double> { 1.0 / static_cast<double>(fps) };
			}
		}

		int m_maxFPS = 0;

		bool m_quit = false;

	private:
		bool m_bVSync = true;
		std::chrono::duration<double> m_targetFrameTime { 0.0 };

	};

}