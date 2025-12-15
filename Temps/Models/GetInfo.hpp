#ifndef PART
#define PART
using namespace std;
#include <iostream>
#include "InGame.hpp"
extern unordered_map<int,Team> Teams;

void GetCastleInfo(Building b, int castleId)
{
    Castle tmp = b.Castles[castleId];
    if(tmp.ownerTeamID != -1){
        auto it = Teams.find(tmp.ownerTeamID);
        string ownerName = (it->second).Name;
        int defensePoints = tmp.defensePoints;
        cout << "Castle " << castleId << " is occupied by " << "Team " << ownerName << "!" << endl;
        cout << "Defense point is " << defensePoints << " !" << endl;
    }
    else{
        cout << "Castle " << castleId << "is not be occupied by any teams !" << endl;
    }
}

void GetTeamResourceInfo(int teamId)
{
    auto it = Teams.find(teamId);
    Team tmp = it->second;
    if (it == Teams.end()){
        cout << "Invalid team !" << endl;
    }
    else{
        cout << "Team " << tmp.Name << " has " << (tmp.ResourceQuantity.find(Resources::Wood))->second << " wood unit(s) !" << endl;
        cout << "Team " << tmp.Name << " has " << (tmp.ResourceQuantity.find(Resources::Stone))->second << " stone unit(s) !" << endl;
        cout << "Team " << tmp.Name << " has " << (tmp.ResourceQuantity.find(Resources::Iron))->second << " iron unit(s) !" << endl;
        cout << "Team " << tmp.Name << " has " << (tmp.ResourceQuantity.find(Resources::Gold))->second << " gold unit(s) !" << endl;
    }
}

int GetTeamResult(int teamId)
{
    auto it = Teams.find(teamId);
    Team tmp = it->second;
    if (it == Teams.end()){
        cout << "Invalid team !" << endl;
        return -1;
    }
    auto wood = tmp.ResourceQuantity.find(Resources::Gold)->second;
    auto stone = tmp.ResourceQuantity.find(Resources::Stone)->second;
    auto iron = tmp.ResourceQuantity.find(Resources::Iron)->second;
    auto gold = tmp.ResourceQuantity.find(Resources::Gold)->second;
    int total = gold*10 + wood + stone*2 + iron*3;
    return total;
}
int GameResult()
{
    int maxPoint = -1;
    int winnerTeamId = -1;
    for (const auto& teamPair : Teams)
    {
        int teamId = teamPair.first;
        int teamPoint = GetTeamResult(teamId);
        if (teamPoint > maxPoint)
        {
            maxPoint = teamPoint;
            winnerTeamId = teamId;
        }
    }
    return winnerTeamId;
}
#endif