#include "Wave/Common/Log/Log.h"

namespace Wave
{
	Log* Log::m_instance = nullptr;

	Log::Log()
	{
	}

	Log& Log::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Log;
		}
		return *m_instance;
	}

	bool Log::HasInstance()
	{
		return m_instance != nullptr;
	}

	void Log::Write(ELogLevel logLevel, const char* file, int32_t line, const char* message)
	{
		// TODO : get the real timestamp
		uint64_t timestamp = 0;

		// TODO : Filter logs depending on level based on some config

		// Write log in output
		for (size_t i = 0; i < m_outputs.size(); ++i)
		{
			m_outputs[i]->WriteLine(logLevel, timestamp, file, line, message);
		}
	}

	void Log::RegisterLogOutput(std::unique_ptr<ILogOutput> newLogOutput)
	{
		// this will claim the ownership
		m_outputs.push_back(std::move(newLogOutput));
	}
}
