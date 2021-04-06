#include <iostream>
#include <string>

#include "Core/Transport/SocketHelper.h"
#include "Core/Transport/UdpSocket.h"

#define DEFAULT_SERVER_PORT 65000

// Really simple server that only tick every second and try to read and sent 1 time per tick
int main()
{
    unsigned short port = DEFAULT_SERVER_PORT;
    Wave::Address destination(127, 0, 0, 1, 65001);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket socket;
    if (!socket.Open(port))
    {
        std::cout << "Couldn't create socket" << std::endl;
        return 0;
    }
    const char msgTest[] = "Hello from server !";

    std::cout << "[SERVER] Launching on port : " << port << std::endl;

    Wave::Address sender;
    unsigned char buffer[256];

    // receive packets
    while (true)
    {
        // Try to read packet
        int bytesRead = socket.Receive(sender, buffer, sizeof(buffer));
        if (bytesRead > 0)
        {
            std::cout << "[SERVER] " << std::to_string(bytesRead) << " bytes received from " << sender.GetAddressStr() << ":" << sender.GetPort();
            std::cout << " | Message : " << buffer << std::endl;
        }

        // Then send one
        if (socket.Send(destination, msgTest, sizeof(msgTest)))
        {
            std::cout << "[SERVER] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
        }

        // Wait for 1 sec
        Sleep(1000);
    }

    // close
    socket.Close();

    Wave::SocketHelper::ShutdownSocket();
    return 0;
}

