#pragma once
#include <iostream>
//#include "clsUserScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsUserLogInRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"
#include "clsClientLogInRegisterScreen.h"
#include "clsUnlockClientAccountScreen.h"

using namespace std;

class clsUserMainScreen :protected clsUserScreen
{


private:
    enum enUserMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eUserLogInRegister = 8, eClientLogInRegister = 9, eUnlockClientAccountScreen = 10,
        eCurrencyExchangeMenue = 11, eExit = 12
    };

    static short _ReadUserMainMenueOption(short NumberOfLastOption)
    {
       
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to " << NumberOfLastOption << "] ? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, NumberOfLastOption, "Enter Number between 1 to " + to_string(NumberOfLastOption) + " ? ");

        short AvailableOptionCount = 0;
        short Count = 0;
   
        for (int i = 1; i <= clsUser::enPermissions::pChangeCurrency; i = i * 2)
        {

           ++Count;
            if (CheckUserAccessRights(clsUser::enPermissions(i)))
            {
                AvailableOptionCount++;
            }
            if (AvailableOptionCount == Choice)
                return Count;
        }

        return ++Count;
        
    }

    static  void _GoBackToMainMenue()
    {
        cout << "\n" << setw(37) << left << "" << "Press any key to go back to Main Menue...\n";

        system("pause>0");
        ShowUserMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        //  cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();


    }

    static void _ShowAddNewClientsScreen()
    {
        // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();

    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();


    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenu()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowUserLogInRegisterScreen()
    {
        clsUserLogInRegisterScreen::ShowUserLogInRegisterScreen();
    }

    static void _ShowClientLogInRegisterScreen()
    {
        clsClientLogInRegisterScreen::ShowClientLogInRegisterScreen();
    }

    static void _ShowUnlockClientAccountScreen()
    {
        clsUnlockClientAccountScreen::ShowUnlockClientAccountScreen();
    }

    static void _ShowCurrencyExchangeMenue()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenue();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");

    }

    static void _PerfromUserMainMenuOption(enUserMainMenueOptions UserMainMenueOption)
    {
        switch (UserMainMenueOption)
        {
        case enUserMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enUserMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eUserLogInRegister:
            system("cls");
            _ShowUserLogInRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eClientLogInRegister:
            system("cls");
            _ShowClientLogInRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eUnlockClientAccountScreen:
            system("cls");
            _ShowUnlockClientAccountScreen();
            _GoBackToMainMenue();
            break;

        case enUserMainMenueOptions::eCurrencyExchangeMenue:
            system("cls");
            _ShowCurrencyExchangeMenue();
            _GoBackToMainMenue();
            break;


        case enUserMainMenueOptions::eExit:
            system("cls");
            _Logout();

            break;
        }

    }

    static vector <string> _GetAvailableOptionsInMainMenue()
    {
        vector <string> vOption;

        /*[1] */  vOption.push_back("Show Client List");
        /*[2] */  vOption.push_back("Add New Client");
        /*[3] */  vOption.push_back("Delete Client");
        /*[4] */  vOption.push_back("Update Client Info");
        /*[5] */  vOption.push_back("Find Client");
        /*[6] */  vOption.push_back("Transactions");
        /*[7] */  vOption.push_back("Manage Users");
        /*[8] */  vOption.push_back("User Login Rgister");
        /*[9] */  vOption.push_back("Client Login Rgister");
        /*[10]*/  vOption.push_back("Unlock Client Account");
        /*[11]*/  vOption.push_back("Currency Exchange");

        return vOption;
    }

public:


    static void ShowUserMainMenue()
    {
        short  Count = 1;
        short NumberOfLastOption = 1;
        system("cls");
        _DrawScreenHeader("\t  User Main Screen");

        vector <string> vOption = _GetAvailableOptionsInMainMenue();

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t User Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";

        for (int i = 1; i <= clsUser::enPermissions::pChangeCurrency; i = i * 2)
        {
          

              if (CheckUserAccessRights(clsUser::enPermissions(i)))

              {
                  if (NumberOfLastOption < 10)
                  {
                      cout << setw(37) << left << "" << "\t [" << NumberOfLastOption << "] " << vOption[Count - 1] << ".\n";
                  }
                  else
                  {
                      cout << setw(37) << left << "" << "\t[" << NumberOfLastOption << "] " << vOption[Count - 1] << ".\n";

                  }
                  NumberOfLastOption++;
              }
              Count++;
        }

   

        if (NumberOfLastOption < 10)
        {
            cout << setw(37) << left << "" << "\t [" << NumberOfLastOption <<  "] Logout.\n";
        }
        else
        {
            cout << setw(37) << left << "" << "\t[" << NumberOfLastOption << "] Logout.\n";

        }

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromUserMainMenuOption((enUserMainMenueOptions)_ReadUserMainMenueOption(NumberOfLastOption));
    }

};

