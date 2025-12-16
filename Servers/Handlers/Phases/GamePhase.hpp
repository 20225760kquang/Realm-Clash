#ifndef SERVER_HANDLER_PHASE_GAME
#define SERVER_HANDLER_PHASE_GAME

#include "../../../Temps/Models/InGameServer.hpp"
#include "../../ServerIncluding.hpp"
#include "../../../Commons/CommonDefinition.hpp"
#include "/Handlers/Handlers/GameHandler.hpp"
#include "../../Temps/Models/InGameServer.hpp"
#include "../../Temps/Models/GetInfo.hpp"

void HandleGamePhase(int clientFD, const string& code, const vector<string>& parts)
{
    if (code == RQ_START_GAME)
    {
        CreateMap();
        BroadcastMessage(clientFD, string(RS_UPDATE_GAME_STARTED), false);
    } else if (code == RQ_REQUEST_SPOT)
    {
        HandleRequestSpot(clientFD, parts[1]);
    }
    else if (code == RQ_ANSWER_SPOT)
    {
        HandleAnswerSpot(clientFD, parts[1], parts[2]);
    }
    else if (code == RQ_REQUEST_CASTLE)
    {
        HandleRequestCastle(clientFD, parts[1]);
    }
    else if (code == RQ_ANSWER_CASTLE)
    {
        HandleAnswerCastle(clientFD, parts[1], parts[2]);
    }
    else if (code == RQ_BUY_DEFENSE)
    {
        HandleBuyDefense(clientFD, parts[1], parts[2]);
    }
    else if (code == RQ_BUY_WEAPON)
    {
        HandleBuyWeapon(clientFD, parts[1]);
    }
    else if (code == RQ_ATTACK_CASTLE)
    {
        HandleAttackCastle(clientFD, parts[1], parts[2]);
    }
    else if (code == RQ_GET_STATUS)
    {
        HandleGetStatus(clientFD);
    }
}

#endif