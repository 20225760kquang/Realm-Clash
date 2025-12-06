// #include "Views/LobbyView.h"
#include "../Cores/Networks/MessageHandler.hpp"
#include "../Cores/CoreFunction.hpp" 
#include "../Cores/CoreIncluding.hpp" 
#include "../Cores/CoreDefinition.hpp"
#include "ClientDeclaration.hpp"

struct MessageData
{
    string text;
    string time;
};

void to_json(json& j, const MessageData& m)
{
    j = json{
        {"text", m.text},
        {"time", m.time}
    };
}

void from_json(const json& j, MessageData& m)
{
    m.text = j.at("text").get<string>();
    m.time = j.at("time").get<string>();
}

void ReceiveThread(int clientFD)
{
    while (true)
    {
        string msg = ReceiveMessage(clientFD);
        if (msg.empty()) break;
        cout << msg << endl;
    }
}

int main()
{
    ClientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (ClientFD < 0) 
    { 
        perror("socket"); 
        return 0; 
    }

    sockaddr_in serv = {};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, CLIENT_IP, &serv.sin_addr);

    if (connect(ClientFD, (sockaddr*)&serv, sizeof(serv)) < 0)
    {
        perror("connect");
        return 1;
    }

    thread(ReceiveThread, ClientFD).detach();

    while (true)
    {
        cout << "Enter message: ";
        string msg;
        getline(cin, msg);

        if (msg == "/quit") break;

        if (msg.rfind("MESSAGE ", 0) == 0)
        {
            string text = msg.substr(8);

            MessageData data;
            data.text = text;

            // generate time
            time_t now = time(nullptr);
            data.time = ctime(&now);
            if (!data.time.empty() && data.time.back() == '\n')
                data.time.pop_back();

            json j = data;

            SendMessage(ClientFD, "MESSAGE " + j.dump());
        }
        else
        {
            SendMessage(ClientFD, msg);
        }
    }

    close(ClientFD);
    return 1;
}