#ifdef SERVER_HANDLER_GAME
#define SERVER_HANDLER_PHASE_GAME
#include "../../../Temps/Models/InGameServer.hpp"
#include "../../ServerIncluding.hpp"
#include "../../../Commons/CommonDefinition.hpp"
#include "../../Temps/Models/Participant.hpp"

void HandleRequestSpot(int clientFD, const string& spotID){
    ///....
}
void HandleAnswerSpot(int clientFD, const string& spotID, const string& answer){
    ///....
}
void HandleRequestCastle(int clientFD, const string& castleID){
    ///....
}
void HandleAnswerCastle(int clientFD, const string& castleID, const string& answer){
    ///....
}
void HandleBuyDefense(int clientFD, const string& spotID, Items defense){
    ///....
}
void HandleBuyWeapon(int clientFD, const string& spotID){
    ///....
}
void HandleAttackCastle(int clientFD, const string& castleID, Items weapon){
    ///....
}
void HandleGetStatus(int clientFD){
    ///....
}


