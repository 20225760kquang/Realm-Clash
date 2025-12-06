#ifndef SERVER_DECLARATION
#define SERVER_DECLARATION

#include "../Cores/CoreIncluding.hpp"

int ServerFD;

vector<int> Clients;
mutex ClientsMutex;

#endif