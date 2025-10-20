#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"


class clsLoginScreen  :protected clsScreen
{

private:


    static  bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 0;

        string Username, Password;
        do
        {
         

            if (LoginFaild)
            {
                FaildLoginCount++;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You Have " << 3 - FaildLoginCount
                    << " Trials to login.\n";
            }
            if (FaildLoginCount == 3)
            {
                cout << "\n You are Locked after 3 failed trails\n";
                return false;
            }

            cout << "\n\nEnter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;
            
            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild );

      
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

    }
    
public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
       return _Login();
        

    }

};

