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

#endif