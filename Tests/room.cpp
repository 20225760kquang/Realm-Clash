#include "../Cores/CoreFunction.hpp" 
#include "../Cores/CoreIncluding.hpp" 
#include "../Cores/CoreDefinition.hpp" 
#include "../Servers/ServerDeclaration.hpp" 
using namespace std;

// ------------------------------------------------------------------------------------
// OLD UI STRUCT (used ONLY for drawing UI)
// ------------------------------------------------------------------------------------
struct UIRoom {
    int id;        
    string name;
    int current;
    int max;
    bool inMatch;
};

string GetDotColor(const UIRoom& r) {
    if (r.inMatch)
        return "\033[31m●\033[0m"; // Red = match started
    if (r.current == r.max)
        return "\033[33m●\033[0m"; // Yellow = full
    return "\033[32m●\033[0m";     // Green = available
}

// ------------------------------------------------------------------------------------
// CONVERT NEW LOBBY ROOMS → UI ROOMS
// ------------------------------------------------------------------------------------
vector<UIRoom> ConvertLobbyRooms(const Lobby& lobby) {
    vector<UIRoom> ui;
    ui.reserve(lobby.Rooms.size());

    // Sort rooms by ID ascending
    vector<pair<int, Room>> sortedRooms(lobby.Rooms.begin(), lobby.Rooms.end());
    sort(sortedRooms.begin(), sortedRooms.end(),
         [](auto& a, auto& b){ return a.first < b.first; });

    for (const auto& pair : sortedRooms) {
        const Room& r = pair.second;

        UIRoom u;
        u.id = r.ID;
        u.name = r.Name;
        u.current = r.Members.size();
        u.max = 15;
        u.inMatch = r.InMatch;

        ui.push_back(u);
    }

    return ui;
}

// ------------------------------------------------------------------------------------
// CREATE, JOIN, LEAVE
// ------------------------------------------------------------------------------------
Room CreateRoom(Lobby &lobby, int creatorFd, const std::string& roomName) {
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

bool JoinRoom(Lobby &lobby, int fd, int roomId) {
    auto it = lobby.Rooms.find(roomId);
    if (it == lobby.Rooms.end()) return false;
    Room &room = it->second;
    if ((int)room.Members.size() >= 15) return false;

    room.Members.push_back(fd);
    lobby.Clients[fd].RoomID = roomId;
    lobby.Clients[fd].IsHost = false;
    return true;
}

void LeaveRoom(Lobby &lobby, int fd) {
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

// ------------------------------------------------------------------------------------
// SPLIT INPUT
// ------------------------------------------------------------------------------------
void SplitCommand(const std::string& input, std::string& data1, std::string& data2) {
    std::istringstream iss(input);
    iss >> data1;
    std::getline(iss, data2);
    if (!data2.empty() && data2[0]==' ') data2.erase(0,1);
}

// ------------------------------------------------------------------------------------
// DRAW UI (MULTICOLUMN LAYOUT)
// ------------------------------------------------------------------------------------
void DrawUI(const vector<UIRoom>& rooms, const string& playerName, int page, int maxPage) {
    ClearScreen();

    int columns = 3;
    int rowsPerPage = 5;
    int start = page * rowsPerPage * columns;

    string bar = "━";
    string title = bar + " " + playerName + " " + bar;
    const int totalWidth = 96; // wide enough for 3 columns
    int remaining = totalWidth - (int)title.size();
    if (remaining < 0) remaining = 0;

    cout << "┏" << title;
    for (int i=0; i<remaining; i++) cout << bar;
    cout << "┓\n";

    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━ ROOM LIST ━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n";

    for (int row=0; row<rowsPerPage; row++)
    {
        for (int col=0; col<columns; col++) 
        {
            int index = start + row*columns + col;
            if (index < (int)rooms.size()) 
            {
                const UIRoom& r = rooms[index];
                string dot = GetDotColor(r);
                string label = to_string(r.id) + " | " + r.name;

                cout << "┃ " << dot << " "
                     << left << setw(19) << setfill(' ') << label
                     << right << setw(2) << r.current
                     << " / "
                     << setw(2) << r.max << " ";
            } 
            else 
            {
                cout << "┃ " << string(26,' ') << "   ";
            }
        }
        cout << "┃\n";
    }

    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n";
    cout << "┃ Page: " << (page+1) << " / " << maxPage << setw(totalWidth-16) << " " << "┃\n";
    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n";
    cout << "┃ 1 : Go to previous page                         2 : Go to next page                        ┃\n";
    cout << "┃ 3 <room name> : Create new room                 4 <room id> : Join a room                  ┃\n";
    cout << "┃ 5 <new name> : Change player's name                                                        ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
}

// ------------------------------------------------------------------------------------
// MAIN
// ------------------------------------------------------------------------------------
int main() {
    Lobby lobby;
    string playerName = "playerA";

    int myFD = 999;
    // Add some sample rooms
    CreateRoom(lobby, myFD, "RoomA");
    CreateRoom(lobby, myFD, "RoomB");
    CreateRoom(lobby, myFD, "RoomC");
    CreateRoom(lobby, myFD, "RoomD");
    CreateRoom(lobby, myFD, "RoomE");
    CreateRoom(lobby, myFD, "RoomF");
    CreateRoom(lobby, myFD, "RoomG");

    int page = 0;

    while(true) {
        vector<UIRoom> rooms = ConvertLobbyRooms(lobby);
        int totalPages = ((int)rooms.size() + 14)/15; // 5 rows * 3 columns = 15 rooms per page

        DrawUI(rooms, playerName, page, totalPages);

        cout << "\nEnter option: ";
        string input;
        getline(cin, input);

        string cmd, data;
        SplitCommand(input, cmd, data);
        int cmdID = atoi(cmd.c_str());

        if (cmdID == 1) {
            if (page > 0) page--;
        } 
        else if (cmdID == 2) {
            if (page < totalPages - 1) page++;
        } 
        else if (cmdID == 3) {
            string id, roomName;
            SplitCommand(data, id, roomName);
            Room room = CreateRoom(lobby, atoi(id.c_str()), roomName);
        } 
        else if (cmdID == 4) {
            string fd, roomID;
            SplitCommand(data, fd, roomID);
            JoinRoom(lobby, atoi(fd.c_str()), atoi(roomID.c_str()));
        } 
        else if (cmdID == 5) {
            LeaveRoom(lobby, atoi(data.c_str()));
        }
    }

    return 0;
}

/*
┏━ playerA ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┣━━━━━━━━━━━━━━━ ROOM LIST ━━━━━━━━━━━━━━┫
┃ ● 1 ┃ RoomA                    10 / 15 ┃
┃ ● 2 ┃ RoomB                     6 / 15 ┃
┃ ● 3 ┃ RoomC                     1 / 15 ┃
┃ ● 4 ┃ RoomD                    15 / 15 ┃
┃ ● 5 ┃ RoomE                     8 / 15 ┃
┣━━━━━━━━━━━━━━━━ OPTIONS ━━━━━━━━━━━━━━━┫
┃ Page: 1 / 2                            ┃
┃                                        ┃
┃ Q / q : Previous Page                  ┃
┃ E / e : Next Page                      ┃
┃ 3 <room name> : Create Room            ┃
┃ 4 <room id> : Join Room                ┃
┃ 5 <new name> : Rename                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

┏━ playerA ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━ ROOM LIST ━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃
┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃
┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃
┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃
┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃ ● 1 | RoomA          10 / 15 ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                                         <  1/2  >                                          ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃ 1 : Go to previous page                         2 : Go to next page                        ┃
┃ 3 <room name> : Create new room                 4 <room id> : Join a room                  ┃
┃ 5 <new name> : Change player's name                                                        ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
Enter command:

┏━ ■ ■ ■ ■ ■ ━━━ ■ playerA ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 00:00:00 ━┓
┣━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━┫
┃   W: 100.000 (+30)   ┃   S: 100.000 (+10)   ┃   I: 100.000 (+10)   ┃   G: 100.000 (+1)   ┃
┣━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┫
┃           ┣╋━╋━╋━╋┫                    ┣╋━╋━╋━╋┫                     ┣╋━╋━╋━╋┫           ┃
┃           ┗╋━┻━┻━╋┛                    ┗╋━┻━┻━╋┛                     ┗╋━┻━┻━╋┛           ┃
┃            ┃  ■  ┃                      ┃  ■  ┃                       ┃  ■  ┃            ┃
┃            ┃  ■  ┃                      ┃  ■  ┃                       ┃  ■  ┃            ┃
┃            ┗━━━━━┛                      ┗━━━━━┛                       ┗━━━━━┛            ┃
┃           CASTLE 01                    CASTLE 02                     CASTLE 03           ┃
┃              ■■■                          ■■■                           ■■■              ┃
┃                                                                                          ┃
┃    ┣━━┻━━┫        ┣━━┻━━┫        ┣━━┻━━┫        ┣━━┻━━┫        ┣━━┻━━┫        ┣━━┻━━┫    ┃
┃    ┃ ■■■ ┃        ┃ ■■■ ┃        ┃ ■■■ ┃        ┃ ■■■ ┃        ┃ ■■■ ┃        ┃ ■■■ ┃    ┃
┃    ┗━━━━━┛        ┗━━━━━┛        ┗━━━━━┛        ┗━━━━━┛        ┗━━━━━┛        ┗━━━━━┛    ┃
┃    SPOT 01        SPOT 02        SPOT 03        SPOT 04        SPOT 05        SPOT 06    ┃
┃     ■ ■ ■          ■ ■ ■          ■ ■ ■          ■ ■ ■          ■ ■ ■          ■ ■ ■     ┃
┃                                                                                          ┃
┣━━━━━━━━━━━ OPTIONS ━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━ CONSOLE ━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                               ┃                                                          ┃ 
┃ 1: Answer spot question       ┃                                                          ┃
┃ 2: Answer castle question     ┃                                                          ┃
┃                               ┃                                                          ┃
┃ 0: Quit match                 ┃                                                          ┃
┃                               ┃                                                          ┃ 
┃                               ┃                                                          ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/