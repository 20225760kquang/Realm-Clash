#include "Cores/CoreIncluding.hpp"
#include "Cores/CoreDefinition.hpp"
#include "Cores/CoreFunction.hpp"
#include "Servers/ServerDeclaration.hpp"
#include "Cores/Networks/MessageHandler.hpp"

void BroadcastMessage(const string &msg, int sender_fd)
{
    lock_guard<mutex> lock(ClientsMutex);
    for (int fd : Clients)
    {
        if (fd != sender_fd)
        {
            SendMessage(fd, msg);
        }
    }
}

void ProcessMessage(const string& msg, int client_fd)
{
    string cmd;
    string data;

    // split first word
    {
        stringstream ss(msg);
        ss >> cmd;
        getline(ss, data);
        if (!data.empty() && data[0] == ' ') data.erase(0, 1);
    }

    if (cmd == "MESSAGE")
    {
        try
        {
            json j = json::parse(data);
            MessageData m = j.get<MessageData>();

            string out = "[Client " + to_string(client_fd) + "] " +
                         m.text + " (" + m.time + ")";

            BroadcastMessage(out, client_fd);
        }
        catch (...)
        {
            SendMessage(client_fd, "Invalid JSON MESSAGE");
        }
    }
    else if (cmd == "SCORE")
    {
        BroadcastMessage("[Client " + to_string(client_fd) + "] Score " + data, client_fd);
    }
    else
    {
        SendMessage(client_fd, "Unknown command");
    }
}

void HandleClient(int client_fd)
{
    {
        lock_guard<mutex> lock(ClientsMutex);
        Clients.push_back(client_fd);
    }

    SendMessage(client_fd, "Welcome to the chat!");

    while (true)
    {
        string msg = ReceiveMessage(client_fd);
        if (msg.empty()) break;

        cout << "[Client " << client_fd << "] raw: " << msg << endl;

        ProcessMessage(msg, client_fd);
    }

    {
        lock_guard<mutex> lock(ClientsMutex);
        Clients.erase(remove(Clients.begin(), Clients.end(), client_fd), Clients.end());
    }

    close(client_fd);
    cout << "[Client " << client_fd << "] disconnected.\n";
}

int main(int argc, char *argv[])
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (sockaddr*)&serv, sizeof(serv)) < 0) { perror("bind"); return 1; }
    if (listen(server_fd, 10) < 0) { perror("listen"); return 1; }

    cout << "Server listening on port " << SERVER_PORT << "...\n";

    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &addrlen);
        if (client_fd < 0) { perror("accept"); continue; }

        cout << "[+] Client " << client_fd << " connected.\n";
        thread(HandleClient, client_fd).detach();
    }

    close(server_fd);
    return 0;
}