#ifndef CLIENT_HANDLER_PHASE_LOBBY
#define CLIENT_HANDLER_PHASE_LOBBY

void HandleLobbyInput(int clientFD, vector<string> a)
{
    SendMessage(clientFD, "HEHEHEHE");
}

#endif