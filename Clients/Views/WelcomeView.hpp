#ifndef VIEW_WELCOME
#define VIEW_WELCOME

/*
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃                                                                    ┃
┃   ░█▀▀▀▄░█▀▀▀ ▄▀▀▀▄░█    ░█▄ ▄█    ▄▀▀▀▄░█     ▄▀▀▀▄ ▄▀▀▀▄░█  ░█   ┃
┃   ░█▄▄▄▀░█▀▀▀░█▄▄▄█░█    ░█░▀░█   ░█    ░█    ░█▄▄▄█  ▀▀▄ ░█▀▀▀█   ┃
┃   ░█  ░█░█▄▄▄░█  ░█░█▄▄▄▄░█  ░█    ▀▄▄▄▀░█▄▄▄▄░█  ░█ ▀▄▄▄▀░█  ░█   ┃
┃                                                                    ┃
┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃ • 1 <email> <password>: Sign up                                    ┃
┃ • 2 <email> <password>: Log in                                     ┃
┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃                                                                    ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void ShowWelcomeView(string code)
{
    ClearScreen();

    string log = FG_GREEN "";
    
    if (code == RS_SIGN_UP_S)
    {
        log = FG_GREEN "Sign up successfully!";
    }
    else if (code == RS_SIGN_UP_F_ACCOUNT_EXISTED)
    {
        log = FG_RED "Sign up failed: Account existed!";
    }
    else if (code == RS_LOG_IN_S)
    {
        log = FG_GREEN "Log in successfully!";
    }
    else if (code == RS_LOG_IN_F_WRONG_PASSWORD)
    {
        log = FG_RED "Log in failed: Wrong password!";
    }
    else if (code == RS_LOG_IN_F_ACCOUNT_NOT_EXISTED)
    {
        log = FG_RED "Log in failed: Account not existed!";
    }
    else if (code == RS_LOG_IN_F_ACCOUNT_HAS_BEEN_USED)
    {
        log = FG_RED "Log in failed: Account has been used!";
    }

    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                                                                    ┃\n";
    cout << "┃   ░█▀▀▀▄░█▀▀▀ ▄▀▀▀▄░█    ░█▄ ▄█    ▄▀▀▀▄░█     ▄▀▀▀▄ ▄▀▀▀▄░█  ░█   ┃\n";
    cout << "┃   ░█▄▄▄▀░█▀▀▀░█▄▄▄█░█    ░█░▀░█   ░█    ░█    ░█▄▄▄█  ▀▀▄ ░█▀▀▀█   ┃\n";
    cout << "┃   ░█  ░█░█▄▄▄░█  ░█░█▄▄▄▄░█  ░█    ▀▄▄▄▀░█▄▄▄▄░█  ░█ ▀▄▄▄▀░█  ░█   ┃\n";
    cout << "┃                                                                    ┃\n";
    cout << BOLD "┣━ OPTION ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n" RESET;
    cout << BOLD "┃ • 1 <email> <password>: Sign up                                    ┃\n" RESET;
    cout << BOLD "┃ • 2 <email> <password>: Log in                                     ┃\n" RESET;
    cout << BOLD "┣━ CONSOLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n" RESET;
    cout << "┃ " << BOLD << log << RESET << string(72 - log.length(), ' ') << "┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
}

#endif