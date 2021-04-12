#pragma once
#include "Wave/Common/WaveDefines.h"

namespace Wave
{
    namespace SocketHelper
    {
        /**
         * \brief Initialize our socket system
         *
         * \return true if we successfully init our socket system
         */
        static bool InitializeSocket()
        {
#if PLATFORM == PLATFORM_WINDOWS
            WSADATA WsaData;
            return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
            return true;
#endif
        }

        /**
         * \brief Shutdown our socket system
         *
         * \return true if we successfully init our socket system
         */
        static void ShutdownSocket()
        {
#if PLATFORM == PLATFORM_WINDOWS
            WSACleanup();
#endif
        }
    }
}