#ifndef VIEW_GAME
#define VIEW_GAME

/*
┏━ ■ Team 1 ━ U0000001 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 00:00:00 ━┓
┃ Wood : 00000000 | Rock : 00000000 | Iron : 00000000 | Gold : 00000 ┃
┣━ GAME ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┫
┃ 🎪 Spot 1 |  Wood [1]   Rock [2]    Iron [3]	┃  🏰 Castle 1 [ ]	 ┃
┃ 🎪 Spot 2 |  Wood [1]   Rock [2]    Iron [3]	┃					 ┃
┃ 🎪 Spot 1 |  Wood [1]   Rock [2]    Iron [3]	┃  🏰 Castle 1 [ ]	 ┃
┃ 🎪 Spot 3 |  Wood [1]   Rock [2]    Iron [3]	┃					 ┃
┃ 🎪 Spot 1 |  Wood [1]   Rock [2]    Iron [3]	┃  🏰 Castle 1 [ ]	 ┃
┃ 🎪 Spot 4 |  Wood [1]   Rock [2]    Iron [3]	┃					 ┃
┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┫
┃ • 1 <teamID>: Create/Join team                                     ┃
┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                                                                    ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

string ToTimeFormat(int tick)
{
	int hours = tick / 3600;
	int minutes = (tick % 3600) / 60;
	int seconds = tick % 60;
	stringstream ss;
	ss << setfill('0') << setw(2) << hours << ":"
		<< setfill('0') << setw(2) << minutes << ":"
		<< setfill('0') << setw(2) << seconds;
	return ss.str();
}

string GetGameTitle()
{
    string playerName = Account.Name;
	int teamID = Team + 1;
    string teamDot = GetTeamColor(teamID) + SQUARE + RESET;
	string teamBadge = GetTeamColor(teamID) + " Team " + to_string(teamID) + RESET + " ━ " + playerName + " ";
	string timeStamp = FG_BRIGHT_YELLOW " " + ToTimeFormat(Tick) + RESET;

    int fillLength = WINDOW_WIDTH - 35;
    stringstream ss;

	for (int i = 0; i < fillLength; ++i) ss << "━";

	return "┏━ " + teamDot + teamBadge + ss.str() + timeStamp + " ━┓\n";
}

string GetGameOption()
{
    if (CurrentPhase == PHASE_GAME_START_GAME)
    {
        return
            "┃ • 1 <spot>: Occupy the spot      | • 2 <castle>: Occupy the castle ┃\n";
    }

    return "";
}

void ShowGameView()
{
	ClearScreen();

	cout << GetGameTitle() <<
        "┃ Wood : 00000000 | Rock : 00000000 | Iron : 00000000 | Gold : 00000 ┃\n"
        "┣━ GAME ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┫\n"
        "┃ 🎪 Spot 1 |  Wood [1]   Rock [2]    Iron [3]  ┃  🏰 Castle 1 [ ]   ┃\n"
        "┃ 🎪 Spot 2 |  Wood [1]   Rock [2]    Iron [3]  ┃                    ┃\n"
        "┃ 🎪 Spot 3 |  Wood [1]   Rock [2]    Iron [3]  ┃  🏰 Castle 2 [ ]   ┃\n"
        "┃ 🎪 Spot 4 |  Wood [1]   Rock [2]    Iron [3]  ┃                    ┃\n"
        "┃ 🎪 Spot 5 |  Wood [1]   Rock [2]    Iron [3]  ┃  🏰 Castle 3 [ ]   ┃\n"
        "┃ 🎪 Spot 6 |  Wood [1]   Rock [2]    Iron [3]  ┃                    ┃\n"
        "┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┫\n"
            << GetGameOption() <<
        "┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
        "┃ " << BOLD << Log << RESET << string(72 - Log.length(), ' ') << "┃\n"
        "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
}

void ShowGameLog(string log)
{
	Log = log;

	ShowGameView();
}
#endif