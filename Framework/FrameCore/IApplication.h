#pragma once

#include <chrono> // for m_maxFrameDelay

#include "../FrameCore/Log.h"
#include "../FrameMath/Vector2.h"

struct GLFWwindow;

namespace Frame {

	bool GetVSync();
	void SetVSync(bool bEnable);

	int GetMaxFPS();
	// 0 = 无限大 | Infinite
	void SetMaxFPS(int fps);

	float GetFrameTime(bool ignoreMaxFrameTime = false);
	
	void SetMaxFrameTime(float time); // 设定 GetFrameTime() 的最大值，默认为 1.f，防止卡顿产生一些异常的 BUG
	float GetMaxFrameTime();

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

		bool m_quit = false;

	};

}