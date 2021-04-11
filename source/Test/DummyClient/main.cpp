#include <iostream>
#include <string>

#include "Core/Transport/SocketHelper.h"
#include "Core/Transport/UdpSocket.h"

#define DEFAULT_CLIENT_PORT 65001

// Really simple client that only tick every second and try to read and sent 1 time per tick
int main()
{
    uint16_t port = DEFAULT_CLIENT_PORT;
    Wave::IPEndPoint destination(127, 0, 0, 1, 65000);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket socket;

    Wave::SocketResult result = socket.Open(Wave::IPEndPoint(0, port));
    if (result != Wave::SocketResult::OK)
    {
        std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        return 0;
    }
    std::cout << "[CLIENT] Launching on port : " << port << std::endl;

    const char msgTest[] = "Hello from client !";
    char buffer[256] = { 0 };

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
                std::cout << "[CLIENT] " << std::to_string(bytesRead) << " bytes received from " << sender.GetAddressStr() << ":" << sender.GetPort();
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
            std::cout << "[CLIENT] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
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

