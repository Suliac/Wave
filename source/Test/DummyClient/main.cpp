#include <iostream>
#include <string>

#include "Wave/Common/Log/CmdLogger.h"

#include "Wave/Transport/Socket/SocketHelper.h"
#include "Wave/Transport/Socket/UdpSocket.h"

#define DEFAULT_CLIENT_PORT 65001

/**
  * Really simple client that only tick every second and try to read and sent 1 time per tick
  * The only purpose of this main is to debug & test, do not exept to find the nice way to doing things here
  */
int main()
{
    Wave::Log::GetInstance().RegisterLogOutput(std::make_unique<Wave::WindowsCmdLogger>());

    uint16_t port = DEFAULT_CLIENT_PORT;
    Wave::IPEndPoint destination(127, 0, 0, 1, 65000);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket_Windows socket;

    Wave::SocketResult result = socket.Open(Wave::IPEndPoint(0, port));
    if (result != Wave::SocketResult::OK)
    {
        WAVE_ERROR("Socket error : %u", static_cast<int16_t>(result));
        return 0;
    }

    WAVE_INFO("[CLIENT] Launching on port %i", port);

    const uint8_t msgTest[] = "Hello from client !";
    Wave::Datagram toSendData(sizeof(msgTest), destination); // TODO : remove the cpy of our endpoint struct
    toSendData.GetBuffer().Insert(msgTest, sizeof(msgTest));

    Wave::Datagram recvData(512);
    while (true)
    {
        // Try to read packet
        int32_t bytesRead;  
        result = socket.ReceiveFrom(recvData, bytesRead);
        if (result == Wave::SocketResult::OK)
        {
            if (bytesRead > 0)
            {
                WAVE_INFO("%lu bytes received from %s:%u | Message : %s", bytesRead, recvData.GetEndPoint().GetAddressStr().c_str(), recvData.GetPort(), (const char*)recvData.GetData());
            }
        }
        else
        {
            WAVE_ERROR("Socket error : %u", static_cast<int16_t>(result));
        }
        recvData.Reset();
        
        // Then send one
        result = socket.SendTo(toSendData);
        if (result == Wave::SocketResult::OK)
        {
            WAVE_INFO("%llu bytes sent to %s:%u", sizeof(msgTest), destination.GetAddressStr().c_str(), destination.GetPort());
        }
        else
        {
            WAVE_ERROR("Socket error : %u", static_cast<int16_t>(result));
        }

        // Wait for 1 sec
        Sleep(1000);
    }

    // close
    socket.Close();

    Wave::SocketHelper::ShutdownSocket();
    WAVE_INFO("[CLIENT] Stopping");
    return 0;
}

