#include <iostream>

#include "Core/Transport/SocketHelper.h"

int main()
{
    Wave::SocketHelper::InitializeSocket();
    std::cout << "I'm a server !" << std::endl;
    Wave::SocketHelper::ShutdownSocket();
    return 0;
}

