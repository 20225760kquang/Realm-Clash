#ifndef SERVER_HANDLER_GAME
#define SERVER_HANDLER_GAME

void RequestStopServerTick()
{
	ServerTicking.store(false);
}

void HandleStartGame(int clientFD)
{
	//if (Lobby.CountTeam() < 3)
	//{
	//	WriteLog(LogType::Failure, clientFD, "START GAME : Not enough teams.", "Current team: " + to_string(Lobby.CountTeam()));
	//	SendMessage(clientFD, string(RS_START_GAME_F_NOT_ENOUGH_TEAMS));
	//	
	//	return;
	//}

    for (auto& team : Lobby.Teams)
    {
        if (team.CountMember() == 0) continue;

        int teamIndex = (int)Teams.size();
        Teams.emplace_back();
        auto& gameTeam = Teams.back();

        for (auto& member : team.Members)
        {
            if (member.ID == 0) continue;

            Accounts[member.ID].GameTeam = teamIndex;
            gameTeam.Members.push_back(member.ID);

        }
    }

    WriteLog(LogType::Success, clientFD, "START GAME");
	BroadcastToClient(clientFD, string(RS_UPDATE_GAME_START), true);

    StartTickOnServer(
        [](int tick)
        {
			BroadcastToClient(-1, string(RS_UPDATE_GAME_TICK) + " " + to_string(tick));
        },
        []()
        {
            cout << "Tick end" << endl;
        }
    );

}

#endif