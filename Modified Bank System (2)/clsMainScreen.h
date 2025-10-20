#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUserLoginScreen.h"
#include "clsClientLoginScreen.h"

class clsMainScreen 
{
private:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {

        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tPerson: \n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";

    }

    enum enMainMenueOptions {
        eUserLoginScreen = 1, eClientLoginScreen = 2, eExitScreen = 3
    };
    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 3]? ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 3, "Enter Number between 1 to 3? ");
        return Choice;
    }
    static void _ShowUserMainScreen()
    {
        clsUserLoginScreen::ShowUserLoginScreen();

    }

    static void _ShowClientMainScreen()
    {
        clsClientLoginScreen::ShowCleintLoginScreen();
    }

    static void _ShowExitScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";

    }

    static void _PerfromMainMenuOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eUserLoginScreen:
        {
            system("cls");
            _ShowUserMainScreen();
            break;
        }
        case enMainMenueOptions::eClientLoginScreen:
            system("cls");
            _ShowClientMainScreen();
            break;

        case enMainMenueOptions::eExitScreen:
            system("cls");
            _ShowExitScreen();
            break;

        
        }

    }

public:
    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show User Login.\n";
        cout << setw(37) << left << "" << "\t[2] Show Client Login.\n";
        cout << setw(37) << left << "" << "\t[3] Exit.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenuOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};

