#ifndef CORE_FUNCTION
#define CORE_FUNCTION

#include "CoreIncluding.hpp"

void ClearScreen() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
struct MessageData
{
    string text;
    string time;
};

void to_json(json& j, const MessageData& m)
{
    j = json{
        {"text", m.text},
        {"time", m.time}
    };
}

void from_json(const json& j, MessageData& m)
{
    m.text = j.at("text").get<string>();
    m.time = j.at("time").get<string>();
}

#endif