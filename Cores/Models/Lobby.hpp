#ifndef MODEL_LOBBY
#define MODEL_LOBBY

struct Client
{
    int FD; 
    std::string Name;   
    int RoomID = -1;    
    bool IsHost = false;    
};

struct Room 
{
    int ID;
    std::string Name;
    int HostFD;
    std::vector<int> Members;
    bool InMatch;
};

struct Lobby 
{
    std::unordered_map<int, Client> Clients;
    std::unordered_map<int, Room> Rooms;
    int NextRoomID = 1;
};

Room CreateRoom(Lobby &lobby, int creatorFd, const std::string& roomName) 
{
    Room room;
    room.ID = lobby.NextRoomID++;
    room.Name = roomName;
    room.HostFD = creatorFd;
    room.Members.push_back(creatorFd);
    room.InMatch = false;

    lobby.Clients[creatorFd].RoomID = room.ID;
    lobby.Clients[creatorFd].IsHost = true;
    lobby.Rooms[room.ID] = room;
    return room;
}

bool JoinRoom(Lobby &lobby, int fd, int roomId) 
{
    auto it = lobby.Rooms.find(roomId);
    if (it == lobby.Rooms.end()) return false;
    Room &room = it->second;
    if ((int)room.Members.size() >= 15) return false;

    room.Members.push_back(fd);
    lobby.Clients[fd].RoomID = roomId;
    lobby.Clients[fd].IsHost = false;
    return true;
}

void LeaveRoom(Lobby &lobby, int fd) 
{
    int roomId = lobby.Clients[fd].RoomID;
    if (roomId == -1) return;
    Room &room = lobby.Rooms[roomId];

    room.Members.erase(
        remove(room.Members.begin(), room.Members.end(), fd),
        room.Members.end()
    );
    lobby.Clients[fd].RoomID = -1;
    lobby.Clients[fd].IsHost = false;

    if (fd == room.HostFD && !room.Members.empty()) {
        room.HostFD = room.Members[0];
        lobby.Clients[room.HostFD].IsHost = true;
    }

    if (room.Members.empty()) {
        lobby.Rooms.erase(roomId);
    }
}

#endif