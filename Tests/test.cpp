#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

using namespace std;

void MoveUp(int n) {
    cout << "\033[" << n << "A";
}

void ClearLine() {
    cout << "\033[2K\r";  // Erase entire line
}

int main() {
    int tick = 0;

    const int UI_LINES = 6;

    // Print empty lines first (layout)
    for (int i = 0; i < UI_LINES; i++)
        cout << "\n";

    while (true) {
        // Get time
        auto now = chrono::system_clock::now();
        time_t tt = chrono::system_clock::to_time_t(now);
        tm* local = localtime(&tt);

        char timeStr[32];
        strftime(timeStr, sizeof(timeStr), "%I:%M:%S %p", local);

        // Colors
        const char* cyan   = "\033[36m";
        const char* yellow = "\033[33m";
        const char* green  = "\033[32m";
        const char* reset  = "\033[0m";

        // Go up to UI start
        MoveUp(UI_LINES);

        // Draw stable-width UI
        ClearLine(); cout << cyan   << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << reset << "\n";
        ClearLine(); cout << green  << "┃        TIMER STATUS        ┃" << reset << "\n";
        ClearLine(); cout << cyan   << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << reset << "\n";

        // Pad dynamic text so line length is stable
        string t = string("┃ Current Time: ") + timeStr;
        t.resize(31, ' ');
        t += "┃";

        string k = string("┃ Current Tick: ") + to_string(tick);
        k.resize(31, ' ');
        k += "┃";

        ClearLine(); cout << yellow << t << reset << "\n";
        ClearLine(); cout << yellow << k << reset << "\n";

        ClearLine(); cout << cyan   << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << reset << "\n";

        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
        tick++;
    }
}


/*
// vector<UIRoom> ConvertLobbyRooms(const Lobby& lobby) 
// {
//     vector<UIRoom> ui;
//     ui.reserve(lobby.Rooms.size());

//     // Sort rooms by ID ascending
//     vector<pair<int, Room>> sortedRooms(lobby.Rooms.begin(), lobby.Rooms.end());
//     sort(sortedRooms.begin(), sortedRooms.end(),
//          [](auto& a, auto& b){ return a.first < b.first; });

//     for (const auto& pair : sortedRooms) {
//         const Room& r = pair.second;

//         UIRoom u;
//         u.id = r.ID;
//         u.name = r.Name;
//         u.current = r.Members.size();
//         u.max = 15;
//         u.inMatch = r.InMatch;

//         ui.push_back(u);
//     }

//     return ui;
// }

void PrintRoomList(const vector<MyUIRoom>& rooms) 
{
    for (const auto& room : rooms) 
    {
        cout << room.ID << " " << room.Name << " - " << room.Host << endl;
    }
}
*/

/*
┏━ playerA ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                        ┃
┣━━━━━━━━━━━━━━━━━ STATUS ━━━━━━━━━━━━━━━┫
┃ Room: RoomA     6/15                   ┃
┃ Role: Member                           ┃
┣━━━━━━━━━━━━━━━━ OPTIONS ━━━━━━━━━━━━━━━┫
┃ 1 : Exit room                          ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

┏━ playerA ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                        ┃
┣━━━━━━━━━━━━━━━━━ STATUS ━━━━━━━━━━━━━━━┫
┃ Room: RoomA     6/15                   ┃
┃ Role: Host                             ┃
┣━━━━━━━━━━━━━━━━ OPTIONS ━━━━━━━━━━━━━━━┫
┃ 1 : Exit room                          ┃
┃ 2 : Start match                        ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

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