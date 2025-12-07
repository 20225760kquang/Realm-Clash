#include "../Commons/Models/Lobby2.hpp"
#include "../Commons/Networks/MessageHandler.hpp"
#include "../Commons/CoreFunction.hpp" 
#include "../Commons/CommonIncluding.hpp" 
#include "../Commons/CommonDefinition.hpp"
#include "../Commons/Definitions/TextStyle.hpp"
#include "ClientNetwork.hpp"
#include "ClientDefinition.hpp"
#include "ClientIncluding.hpp"

void CallPhase(int phase, int clientFD, const vector<string>& args)
{
    static void (*funcs[])(int, vector<string>) = 
    { 
        HandleWelcomeInput, 
        HandleLobbyInput
    };

    funcs[phase](clientFD, args);
}

void ReceiveThread(int clientFD)
{
    while (true)
    {
        string msg = ReceiveMessage(clientFD);
        if (msg.empty()) break;

        auto split = SplitBySpace(msg);
        auto code = split[0];

        if (code == RS_NETWORK_CONNECTED ||
            code == RS_SIGN_UP_F_ACCOUNT_EXISTED ||
            code == RS_LOG_IN_F_WRONG_PASSWORD ||
            code == RS_LOG_IN_F_ACCOUNT_NOT_EXISTED ||
            code == RS_LOG_IN_F_ACCOUNT_HAS_BEEN_USED)
        {
            ShowWelcomeView(code);
        }
        else if (code == RS_SIGN_UP_S ||
            code == RS_LOG_IN_S)
        {
            Account = AccountRecord::Deserialize(split[1]);
            CurrentPhase = PHASE_LOBBY;

            ShowLobbyView();

            SendMessage(clientFD, string(RQ_UPDATE_LOBBY));

        }
    }
}

int main()
{
    ClearScreen();

    int clientFD = CreateSocket();

    thread(ReceiveThread, clientFD).detach();

    while (true)
    {
        string command;
        getline(cin, command);

        auto split = SplitBySpace(command);
        
        CallPhase(CurrentPhase, clientFD, split);
    }

    close(clientFD);
    return 1;
}