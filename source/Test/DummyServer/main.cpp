#include <iostream>
#include <string>

#include "Core/Transport/SocketHelper.h"
#include "Core/Transport/UdpSocket.h"

#define DEFAULT_SERVER_PORT 65000

// Really simple server that only tick every second and try to read and sent 1 time per tick
int main()
{
    uint16_t port = DEFAULT_SERVER_PORT;
    Wave::IPEndPoint destination(127, 0, 0, 1, 65001);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket socket;
    Wave::SocketResult result = socket.Open(Wave::IPEndPoint(0, port));
    if (result != Wave::SocketResult::OK)
    {
        std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        return 0;
    }
    const char msgTest[] = "Hello from server !";

    std::cout << "[SERVER] Launching on port : " << port << std::endl;

    Wave::IPEndPoint sender;
    unsigned char buffer[256];

    // receive packets
    while (true)
    {
        Wave::IPEndPoint sender;

        // Try to read packet
        int32_t bytesRead;
        result = socket.Receive(sender, buffer, sizeof(buffer), bytesRead);
        if (result == Wave::SocketResult::OK)
        {
            if (bytesRead > 0)
            {
                std::cout << "[SERVER] " << std::to_string(bytesRead) << " bytes received from " << sender.GetAddressStr() << ":" << sender.GetPort();
                std::cout << " | Message : " << buffer << std::endl;
            }
        }
        else
        {
            std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        }

        // Then send one
        result = socket.Send(destination, msgTest, sizeof(msgTest));
        if (result == Wave::SocketResult::OK)
        {
            std::cout << "[SERVER] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
        }
        else
        {
            std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        }

        // Wait for 1 sec
        Sleep(1000);
    }

    // close
    socket.Close();

    Wave::SocketHelper::ShutdownSocket();
    return 0;
}

