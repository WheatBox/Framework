#include <FrameCore/Log.h>

#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <filesystem>
#include <cstdarg>
#include <condition_variable>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace Frame::Log {

	std::pair<tm *, int> GetTimeStamp() {
#ifdef _WIN32
		static tm tm;
		SYSTEMTIME wtm;
		GetLocalTime(&wtm);

		tm.tm_year = wtm.wYear - 1900;
		tm.tm_mon = wtm.wMonth - 1;
		tm.tm_mday = wtm.wDay;
		tm.tm_hour = wtm.wHour;
		tm.tm_min = wtm.wMinute;
		tm.tm_sec = wtm.wSecond;

		return std::make_pair(&tm, wtm.wMilliseconds);
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);

		return std::make_pair(std::localtime(&tv.tv_sec), tv.tv_usec / 1000);
#endif // _WIN32
	}

	std::string GetTimeStampString(char dateDelimiter, char date_clock_Delimiter, char clockDelimiter) {
		auto [tm, msec] = GetTimeStamp();
		char buffer[256] = { };
		snprintf(buffer, 256, "%04d%c%02d%c%02d%c%02d%c%02d%c%02d%c%03d",
			tm->tm_year + 1900, dateDelimiter, tm->tm_mon + 1, dateDelimiter, tm->tm_mday,
			date_clock_Delimiter,
			tm->tm_hour, clockDelimiter, tm->tm_min, clockDelimiter, tm->tm_sec, clockDelimiter, (int)msec
		);
		return buffer;
	}

	constexpr const char * const __szDefaultLogPath = "./Logs/";

	std::ofstream __fsLogOut;

	std::queue<std::string> __logStrsQueue {};

	std::mutex mut;
	std::condition_variable cv;

	bool Open(std::string pathName) {
		if(__fsLogOut.is_open()) {
			__fsLogOut.close();
		}
		
		if(std::filesystem::path path { pathName }; !std::filesystem::exists(path)) {
			std::filesystem::create_directories(path);
			if(!std::filesystem::exists(path)) {
				printf("Can not open or create directory: %s\n", pathName.c_str());
				return false;
			}
		}

		pathName = pathName + GetTimeStampString('-', '_', '-') + ".log";

		__fsLogOut.open(pathName);
		if(!__fsLogOut.is_open()) {
			printf("Can not open or create log file: %s\n", pathName.c_str());
			return false;
		}
		return true;
	}

	void Log(ELevel level, const char * const szFormat, ...) {
		if(!__fsLogOut.is_open()) {
			if(!Open(__szDefaultLogPath)) {
				return;
			}
		}

		va_list argList;

		va_start(argList, szFormat);
		int len = vsnprintf(nullptr, 0, szFormat, argList);
		va_end(argList);

		if(len <= 0) {
			return;
		}

		std::string head = "[" + std::string { GetLevelName(level) } + "] " + GetTimeStampString('-', ' ', ':') + "} ";

		char * szMessage = (char *)malloc(sizeof(char) * (len + 1));

		va_start(argList, szFormat);
		vsnprintf(szMessage, len + 1, szFormat, argList);
		va_end(argList);

		__logStrsQueue.push(head + szMessage);

		free(szMessage);

		cv.notify_one();
	}

	struct __SLogInit {
		__SLogInit() {
			m_thread.detach();
		}
		std::thread m_thread {
			[]() {
				while(true) {
					if(__logStrsQueue.empty()) {
						std::unique_lock lock { mut };
						cv.wait(lock);
					}

					std::cout << __logStrsQueue.front() << std::endl;
					__fsLogOut << __logStrsQueue.front() << std::endl;
					__fsLogOut.flush();

					__logStrsQueue.pop();
				}
			}
		};
	} __logInit {};

}
