#ifndef CLIENT_INCLUDING
#define CLIENT_INCLUDING

#include "Models/Records/AccountRecord.hpp"
#include "Models/Records/LobbyRecord.hpp"

#include "Models/Entities/AccountEntity.hpp"
#include "Models/Entities/LobbyEntity.hpp"

int CurrentPhase = 0;
AccountRecord Account;
LobbyRecord Lobby;
int JoinRequestAmount = 0;
int TeamInviteRequest = 0;
int PendingJoinTick = 0;
int PendingInviteTick = 0;
string Log = FG_GREEN "";
int Team;
int Tick;

#include "Views/LobbyView.hpp"
#include "Views/WelcomeView.hpp"
#include "Views/GameView.hpp"
#include "Views/QuestionView.hpp"

#include "Handlers/Phases/PhaseWelcome.hpp"
#include "Handlers/Phases/PhaseLobby.hpp"
#include "Handlers/Phases/PhaseGame.hpp"

#endif