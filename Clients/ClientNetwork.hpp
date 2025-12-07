#ifndef CLIENT_NETWORK
#define CLIENT_NETWORK

int CreateSocket()
{
    int clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFD < 0) 
    { 
        perror("socket"); 
        return -1; 
    }

    sockaddr_in serv = {};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, CLIENT_IP, &serv.sin_addr);

    if (connect(clientFD, (sockaddr*)&serv, sizeof(serv)) < 0)
    {
        perror("connect");
        return -1;
    }

    return clientFD;
}

#endif