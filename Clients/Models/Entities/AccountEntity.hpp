#ifndef CLIENT_MODEL_ACCOUT_ENTITY
#define CLIENT_MODEL_ACCOUT_ENTITY

struct AccountEntity
{
    string Email;
    string Password;

    string Serialize() const
    {
        json j;
        j["Email"] = Email;
        j["Password"] = Password;

        return j.dump();
    }
};

#endif