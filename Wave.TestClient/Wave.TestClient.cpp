// Wave.TestClient.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "../Wave.Core/SocketHelper.h"

int main()
{
	Wave::SocketHelper::InitializeSockets();
	std::cout << "test" << std::endl;
	Wave::SocketHelper::ShutdownSockets();
    return 0;
}

