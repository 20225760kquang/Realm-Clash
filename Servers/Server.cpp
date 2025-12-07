#include "../Commons/CommonDefinition.hpp"
#include "../Commons/CommonIncluding.hpp"
#include "../Commons/CoreFunction.hpp"
#include "../Commons/Networks/MessageHandler.hpp"
#include "../Commons/Models/Lobby2.hpp"
#include "ServerNetwork.hpp"
#include "ServerDefinition.hpp"
#include "ServerIncluding.hpp"

void HandleClient(int clientFD)
{
    {
        lock_guard<mutex> lock(ClientsMutex);
    }

    SendMessage(clientFD, RS_NETWORK_CONNECTED);

    while (true)
    {
        string msg = ReceiveMessage(clientFD);
        if (msg.empty()) break;

        cout << FG_YELLOW "■" RESET " Client " << clientFD << ": " << msg << endl;

        auto parts = SplitBySpace(msg);
        string code = parts[0];
        string response = msg;

        if (code == RQ_SIGN_UP)
        {
            HandleSignUp(clientFD, parts[1]);
        }
        else if (code == RQ_LOG_IN)
        {
            HandleLogIn(clientFD, parts[1]);
        }
        else if (code == RQ_UPDATE_LOBBY)
        {
            HandleUpdateLobby(clientFD);
        }
    }

    {
        lock_guard<mutex> lock(ClientsMutex);
    }

    close(clientFD);
    cout << FG_RED "●" RESET " Client " << clientFD << " disconnected.\n";
}

int main()
{
    ClearScreen();

    int serverFD = CreateSocket();

    while (true)
    {
        int clientFD = AcceptClient(serverFD);
        if (clientFD < 0) 
        {
            continue;
        }

        thread(HandleClient, clientFD).detach();
    }

    close(serverFD);
    return 1;
}