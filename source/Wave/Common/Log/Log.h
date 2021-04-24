#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

#define LOG_MAX_SIZE 254

#ifdef _DEBUG
#define WAVE_LOG(Type, FormatMessage, ...) \
	do { \
		char msg[LOG_MAX_SIZE];	\
		snprintf(msg, LOG_MAX_SIZE, FormatMessage, __VA_ARGS__);	\
		Wave::Log::GetInstance().Write(Type, __FILE__, __LINE__, msg);\
	}while(0)
#else
#define WAVE_LOG(Type, FormatMessage, ...)  do {} while (0)
#endif

#define WAVE_INFO(FormatMessage, ...)       WAVE_LOG(Wave::ELogLevel::Info, FormatMessage, __VA_ARGS__);
#define WAVE_WARNING(FormatMessage, ...)    WAVE_LOG(Wave::ELogLevel::Warning, FormatMessage, __VA_ARGS__);
#define WAVE_ERROR(FormatMessage, ...)      WAVE_LOG(Wave::ELogLevel::Error, FormatMessage, __VA_ARGS__);
namespace Wave
{

    /**
     * \enum ELogLevel
     * \brief The level of our log from debug info to errors, this logger is NOT threadsafe
     */
    enum class ELogLevel : uint8_t
    {
        Info = 0,
        Warning,
        Error,
    };

    /**
     * \class ILogOutput
     * \brief Define an interface for log outputs : in file, in cmd etc
     */
    class ILogOutput
    {
    public:
        /**
         * \brief Write the log line passed as argument, this function has to be implemented by the children to provide a specific way to write log
         * \param logLevel The level of the current log (info, warning, error...)
         * \param timestamp The current time for the log
         * \param file The file where the log comes from
         * \param line The line number where the log comes from
         * \param message The real content we cant to log
         * \sa Wave::ELogLevel
         */
        virtual void WriteLine(ELogLevel logLevel, uint64_t timestamp, const char* file, int32_t line, const char* message) = 0;
    };

    /**
     * \class Simple singleton logger class (not thread safe)
     * Logger class that will centralize the write of the logs
     * & dispatch them to the configured outputs
     * \sa ILogOutput, Log::LogInfo, Log::ELevel
     */
    class Log
    {
    public:
        static Log& GetInstance();
        static bool HasInstance();

        /**
         * \brief Write the log : pass the log to the log's outputs currently registered so they can write the log
         * \param logLevel The level of the current log (info, warning, error...)
         * \param file The file where the log comes from
         * \param line The line number where the log comes from
         * \param message The real content we cant to log
         * \sa Wave::ILogOutput, Wave::ELogLevel
         */
        void Write(ELogLevel logLevel, const char* file, int32_t line, const char* message);

        /**
         * \brief Add a new log's ouput that will be able to interpret the log message
         * \param newLogOutput The ptr to the log's output you want to add, this logger will claim the ownership !
         * \sa Wave::ILogOutput, Wave::ELogLevel
         */
        void RegisterLogOutput(std::unique_ptr<ILogOutput> newLogOutput);
    private:
        Log();
        static Log* m_instance;

        // All the log outputs we have, it could be CMD writer, file writer...
        std::vector<std::unique_ptr<ILogOutput>> m_outputs;
    };

}
