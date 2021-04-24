#include "CmdLogger.h"

#include <iostream>
#include <Windows.h>

#include "Wave/Common/Log/LogHelper.h"

namespace Wave
{
    void WindowsCmdLogger::WriteLine(ELogLevel logLevel, uint64_t timestamp, const char* file, int32_t line, const char* message)
    {
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (logLevel)
        {
        case Wave::ELogLevel::Warning:
            SetConsoleTextAttribute(hConsole, 14);
            break;
        case Wave::ELogLevel::Error:
            SetConsoleTextAttribute(hConsole, 12);
            break;
        case Wave::ELogLevel::Info:
        default:
            SetConsoleTextAttribute(hConsole, 7);
            break;
        }

        printf("[%c][%llu] %s\n", LogHelper::GetLevelShortStr(logLevel), timestamp, message);
    }
}
