#ifndef SERVER_INCLUDING
#define SERVER_INCLUDING

#include "Models/Entities/AccountEntity.hpp"
#include "Models/Entities/LobbyEntity.hpp"

#include "Models/Records/AccountRecord.hpp"

mutex ClientsMutex;
unordered_map<int, AccountEntity> Accounts;
unordered_map<int, RoomEntity> Rooms;

#include "Handlers/AccountHandler.hpp"
#include "Handlers/LobbyHandler.hpp"

#endif