#include "ServerDeclaration.hpp"
#include "ServerNetwork.hpp"
#include "../Cores/CoreDefinition.hpp"
#include "../Cores/CoreIncluding.hpp"
#include "../Cores/CoreFunction.hpp"
#include "../Cores/Networks/MessageHandler.hpp"
#include "../Cores/Models/Lobby.hpp"

void HandleClient(int clientFD)
{
    {
        lock_guard<mutex> lock(ClientsMutex);
        Clients.push_back(clientFD);
    }

    SendMessage(clientFD, "Welcome to the chat!");

    while (true)
    {
        string msg = ReceiveMessage(clientFD);
        if (msg.empty()) break;

        cout << "[Client " << clientFD << "] raw: " << msg << endl;

        BroadcastMessage(msg, clientFD);
    }

    {
        lock_guard<mutex> lock(ClientsMutex);
        Clients.erase(remove(Clients.begin(), Clients.end(), clientFD), Clients.end());
    }

    close(clientFD);
    cout << "[Client " << clientFD << "] disconnected.\n";
}

int main()
{
    ServerFD = CreateSocket();

    while (true)
    {
        int clientFD = AcceptClient(ServerFD);
        if (clientFD < 0) 
        {
            continue;
        }

        thread(HandleClient, clientFD).detach();
    }

    close(ServerFD);
    return 1;
}