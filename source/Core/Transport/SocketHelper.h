#pragma once
#include "Core/Common/WaveDefines.h"

namespace Wave
{
	namespace SocketHelper
	{
		static bool InitializeSocket()
		{
#if PLATFORM == PLATFORM_WINDOWS
			WSADATA WsaData;
			return WSAStartup(MAKEWORD(2, 2),
				&WsaData)
				== NO_ERROR;
#else
			return true;
#endif
		}

		static void ShutdownSocket()
		{
#if PLATFORM == PLATFORM_WINDOWS
			WSACleanup();
#endif
		}
	}
}