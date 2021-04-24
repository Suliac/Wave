#pragma once
#include "Wave/Common/Log/Log.h"

namespace Wave
{
	/**
	 * \class CmdLogger
	 * \Brief Very simple implementation of the CMD logger
	 */
	class WindowsCmdLogger : public ILogOutput
	{
	public:
		virtual void WriteLine(ELogLevel logLevel, uint64_t timestamp, const char* file, int32_t line, const char* message) override;
	};
}

