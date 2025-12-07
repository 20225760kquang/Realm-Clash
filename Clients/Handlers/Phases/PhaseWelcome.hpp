#ifndef CLIENT_HANDLER_PHASE_WELCOME
#define CLIENT_HANDLER_PHASE_WELCOME

void HandleWelcomeInput(int clientFD, vector<string> split)
{
    string message;
    int code = atoi(split[0].c_str());

    if (code == 1)
    {
        AccountEntity acc { split[1], split[2] };
        SendMessage(clientFD, string(RQ_SIGN_UP) + " " + acc.Serialize());
    }
    else if (code == 2)
    {
        AccountEntity acc { split[1], split[2] };
        SendMessage(clientFD, string(RQ_LOG_IN) + " " + acc.Serialize());
    }
}

#endif