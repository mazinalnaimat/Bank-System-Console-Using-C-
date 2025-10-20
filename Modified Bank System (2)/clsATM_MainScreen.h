#pragma once
#include <iostream>
#include "clsClientScreen.h"
#include "clsInputValidate.h"
#include "clsClientDepositScreen.h"
#include "clsClientWithdrawScreen.h"
#include "clsClientTransferScreen.h"
#include "clsClientBalanceScreen.h"
#include "clsClientInfoScreen.h"


using namespace std;

class clsATM_MainScreen :protected clsClientScreen
{



private:
    enum enClientMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowBalance = 3, eTransfer = 4, eClientInfo = 5, 
        eShowExitScreen = 6
    };

    static short ReadClientMenueOption(short NumberOfLastOption)
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to " << NumberOfLastOption << "] ? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, NumberOfLastOption, "Enter Number between 1 to " + to_string(NumberOfLastOption) + " ? ");

        short AvailableOptionCount = 0;
        short Count = 0;

        for (int i = 1; i <= clsBankClient::enPermissions::pClientInfo; i = i * 2)
        {

            ++Count;
            if (CheckClientAccessRights(clsBankClient::enPermissions(i)))
            {
                AvailableOptionCount++;
            }
            if (AvailableOptionCount == Choice)
                return Count;
        }

        return ++Count;

    }

    static void _ShowClientDepositScreen()
    {
        //cout << "\n Deposit Screen will be here.\n";
        clsClientDepositScreen::ShowClientDepositScreen();
    }

    static void _ShowClientWithdrawScreen()
    {
        //cout << "\n Withdraw Screen will be here.\n";
        clsClientWithdrawScreen::ShowClientWithdrawScreen();
    }

    static void _ShowClientBalanceScreen()
    {
        // cout << "\n Balances Screen will be here.\n";
        clsClientBalanceScreen::ShowClientBalanceScreen();

    }

    static void _ShowClientInfoScreen()
    {
        // cout << "\n Balances Screen will be here.\n";
        clsClientInfoScreen::ShowClientInfoScreen();

    }

    static void _ShowClientTransferScreen()
    {
        // cout << "\n Balances Screen will be here.\n";
        clsClientTransferScreen::ShowClientTransferScreen();

    }

    static void _GoBackToATM_Menue()
    {
        cout << "\n\nPress any key to go back to ATM Menue...";
        system("pause>0");
        ShowATM_MainMenue();

    }

    static void _PerformClientMenueOption(enClientMenueOptions ClientMenueOptions)
    {
        switch (ClientMenueOptions)
        {
        case enClientMenueOptions::eDeposit:
        {
            system("cls");
            _ShowClientDepositScreen();
            _GoBackToATM_Menue();
            break;
        }

        case enClientMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowClientWithdrawScreen();
            _GoBackToATM_Menue();
            break;
        }


        case enClientMenueOptions::eShowBalance:
        {
            system("cls");
            _ShowClientBalanceScreen();
            _GoBackToATM_Menue();
            break;
        }

        case enClientMenueOptions::eTransfer:
        {
            system("cls");
            _ShowClientTransferScreen();
            _GoBackToATM_Menue();
            break;
        }
        case enClientMenueOptions::eClientInfo:
        {
            system("cls");
            _ShowClientInfoScreen();
            _GoBackToATM_Menue();
            break;
        }

    



        case enClientMenueOptions::eShowExitScreen:
        {
            //do nothing here the main screen will handle it :-) ;

        }
        }


    }

    static vector <string> _GetAvailableOptionsInMainMenue()
    {
        vector <string> vOption;
                 
       /*[1] */  vOption.push_back("Deposit");
       /*[2] */  vOption.push_back("Withdraw ");
       /*[3] */  vOption.push_back("Balance");
       /*[4] */  vOption.push_back("Transfer");
       /*[5] */  vOption.push_back("Client Info");

        return vOption;
    }

public:


    static void ShowATM_MainMenue()
    {
        short  Count = 1;
        short NumberOfLastOption = 1;
        vector <string> vOption = _GetAvailableOptionsInMainMenue();


        system("cls");
        _DrawScreenHeader("\t\tATM");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\t ATM \n";
        cout << setw(37) << left << "" << "===========================================\n";

        for (int i = 1; i <= clsBankClient::enPermissions::pClientInfo; i = i * 2)
        {


            if (CheckClientAccessRights(clsBankClient::enPermissions(i)))

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
            cout << setw(37) << left << "" << "\t [" << NumberOfLastOption << "] Logout.\n";
        }
        else
        {
            cout << setw(37) << left << "" << "\t[" << NumberOfLastOption << "] Logout.\n";

        }

        cout << setw(37) << left << "" << "===========================================\n";

        _PerformClientMenueOption((enClientMenueOptions)ReadClientMenueOption(NumberOfLastOption));
    }

};

