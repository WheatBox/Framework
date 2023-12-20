#include <FrameCore/Log.h>

#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace Frame::Log {

	std::pair<std::tm *, int> GetTimeStamp() {
#ifdef _WIN32
		static std::tm tm;
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

	const char * GetTimeStampString(char dateDelimiter, char date_clock_Delimiter, char clockDelimiter) {
		auto [tm, msec] = GetTimeStamp();
		static char buffer[256] = { };

		snprintf(buffer, 256, "%04d%c%02d%c%02d%c%02d%c%02d%c%02d%c%03d",
			tm->tm_year + 1900, dateDelimiter, tm->tm_mon + 1, dateDelimiter, tm->tm_mday,
			date_clock_Delimiter,
			tm->tm_hour, clockDelimiter, tm->tm_min, clockDelimiter, tm->tm_sec, clockDelimiter, (int)msec
		);
		return buffer;
	}

	constexpr const char * const __szDefaultLogPath = "./Logs/";

	constexpr size_t __bufSize = 512;

	std::ofstream __fsLogOut;

	std::queue<std::string> __logStrsQueue {};

	std::thread __thread {
		[]() {
			while(true) {
				if(__logStrsQueue.empty()) {
					continue;
				}

				std::cout << __logStrsQueue.front() << std::endl;
				__fsLogOut << __logStrsQueue.front() << std::endl;
				__fsLogOut.flush();

				__logStrsQueue.pop();
			}
		}
	};
	bool __threadDetached = false;

	bool Open(std::string pathName) {
		if(!__threadDetached) {
			__thread.detach();
			__threadDetached = true;
		}

		if(__fsLogOut.is_open()) {
			__fsLogOut.close();
		}
		
		if(std::filesystem::path path { pathName }; !std::filesystem::exists(path)) {
			if(!std::filesystem::create_directories(path)) {
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

		char szMessage[__bufSize] { '\0' };

		va_list argList;
		va_start(argList, szFormat);
		vsnprintf(szMessage, __bufSize - 1, szFormat, argList);
		va_end(argList);

		char szLogBuf[__bufSize] { '\0' };
		snprintf(szLogBuf, __bufSize - 1, "[%s] %s} %s",
			GetLevelName(level), GetTimeStampString('-', ' ', ':'), szMessage
		);

		__logStrsQueue.push({ szLogBuf });
	}

}