#pragma once
#include "Wave/Common/Log/Log.h"

namespace Wave
{
    namespace LogHelper
    {
        static inline std::string GetLevelStr(ELogLevel logLevel)
        {
			switch (logLevel)
			{
			case Wave::ELogLevel::Info:
				return "Info";
			case Wave::ELogLevel::Warning:
				return "Warning";
			case Wave::ELogLevel::Error:
				return "Error";
			default:
				return "Unknown";
			}
        }

        static inline char GetLevelShortStr(ELogLevel logLevel)
		{
			switch (logLevel)
			{
			case Wave::ELogLevel::Info:
				return 'I';
			case Wave::ELogLevel::Warning:
				return 'W';
			case Wave::ELogLevel::Error:
				return 'E';
			default:
				return '?';
			}
		}
    }
}

