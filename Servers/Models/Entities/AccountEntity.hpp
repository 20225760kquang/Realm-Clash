#ifndef SERVER_MODEL_ENTITY_ACCOUNT
#define SERVER_MODEL_ENTITY_ACCOUNT

struct AccountEntity
{
    int ID;
    string Name;

    int FD;
    int RoomID;
    bool IsHost;

    string Serialize() const
    {
        json j;
        j["ID"] = ID;
        j["Name"] = Name;

        return j.dump();
    }
};

#endif