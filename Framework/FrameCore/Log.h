﻿#pragma once

#include <string>

struct tm;

namespace Frame::Log {

	enum ELevel {
		Debug = 0,
		Info,
		Warn,
		Error,
		Fatal
	};

	std::pair<tm *, int> GetTimeStamp();
	std::string GetTimeStampString(char dateDelimiter, char date_clock_Delimiter, char clockDelimiter);

	constexpr const char * GetLevelName(ELevel level) {
		switch(level) {
		case ELevel::Debug:
			return "Debug";
		case ELevel::Info:
			return "Info";
		case ELevel::Warn:
			return "Warn";
		case ELevel::Error:
			return "Error";
		case ELevel::Fatal:
			return "Fatal";
		}
		return "Unknown";
	}

	bool Open(std::string pathName = "./Logs/");
	void Log(ELevel level, const char * const szFormat, ...);

}
