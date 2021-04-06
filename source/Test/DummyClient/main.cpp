#include <iostream>
#include <string>

#include "Core/Transport/SocketHelper.h"
#include "Core/Transport/UdpSocket.h"

#define DEFAULT_CLIENT_PORT 65001

// Really simple client that only tick every second and try to read and sent 1 time per tick
int main()
{
    unsigned short port = DEFAULT_CLIENT_PORT;
    Wave::Address destination(127, 0, 0, 1, 65000);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket socket;
    if (!socket.Open(port))
    {
        std::cout << "Couldn't create socket" << std::endl;
        return 0;
    }
    std::cout << "[CLIENT] Launching on port : " << port << std::endl;

    const char msgTest[] = "Hello from client !";
    char buffer[256] = { 0 };

    while (true)
    {
        Wave::Address sender;

        // Try to read packet
        int bytesRead = socket.Receive(sender, buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            std::cout << "[CLIENT] " << std::to_string(bytesRead) << " bytes received from " << sender.GetAddressStr() << ":" << sender.GetPort();
            std::cout << " | Message : " << buffer << std::endl;
        }
        
        // Then send one
        if (socket.Send(destination, msgTest, sizeof(msgTest)))
        {
            std::cout << "[CLIENT] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
        }

        // Wait for 1 sec
        Sleep(1000);
    }

    // close
    socket.Close();

    Wave::SocketHelper::ShutdownSocket();
    return 0;
}

