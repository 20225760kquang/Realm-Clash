#ifndef VIEW_LOBBY
#define VIEW_LOBBY

/*
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ playerA ━┓
┣━ LOBBY ━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┫
┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃
┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃
┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃
┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃
┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃
┣━ PAGE ━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┫
┃                              < 1/2 >                               ┃
┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃ • 1: Go to previous page        ┃ • 2: Go to next page             ┃
┃ • 3 <room name>: Create room    ┃ • 4 <room id>: Join a room       ┃
┃ • 5 <name>: Change name         ┃ • 6 <password>: Change password  ┃
┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                                                                    ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

string MakeTitle(const std::string& playerName)
{
    const int totalLen = 70;

    string left  = "┏";
    string right = " ━┓";

    string bar = "━";

    int fillLen = totalLen - playerName.length() - 5;

    string fill;
    fill.reserve(fillLen * bar.length());

    for (int i = 0; i < fillLen; ++i)
    {
        fill += bar;
    }

    return left + fill + " " + playerName + right;
}

void ShowLobbyView()
{
    ClearScreen();

    cout << MakeTitle(Account.Name) << "\n";
    cout <<
    // "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ U000000001 ━┓\n"
    "┣━ LOBBY ━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━┫\n"
    "┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃\n"
    "┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃\n"
    "┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃\n"
    "┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃\n"
    "┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃ ● 1 | RoomA    10/15 ┃\n"
    "┣━ PAGE ━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┫\n"
    "┃                              < 1/2 >                               ┃\n"
    "┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
    "┃ • 1: Go to previous page        ┃ • 2: Go to next page             ┃\n"
    "┃ • 3 <room name>: Create room    ┃ • 4 <room id>: Join a room       ┃\n"
    "┃ • 5 <name>: Change name         ┃ • 6 <password>: Change password  ┃\n"
    "┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
    "┃                                                                    ┃\n"
    "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
}


#endif