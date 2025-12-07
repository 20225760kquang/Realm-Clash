#ifndef CLIENT_INCLUDING
#define CLIENT_INCLUDING

#include "Models/Entities/AccountEntity.hpp"
#include "Models/Records/AccountRecord.hpp"

int CurrentPhase = 0;
AccountRecord Account;

#include "Views/LobbyView.hpp"
#include "Views/WelcomeView.hpp"

#include "Handlers/Phases/PhaseWelcome.hpp"
#include "Handlers/Phases/PhaseLobby.hpp"

#endif