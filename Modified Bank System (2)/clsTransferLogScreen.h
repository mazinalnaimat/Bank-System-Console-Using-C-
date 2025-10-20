#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsBankClient.h"
#include "clsUserTransferLogScreen.h"
#include "clsClientTransferLogScreen.h"

using namespace std;

class clsTransferLogScreen  :protected clsUserScreen
{
private:

    enum enTransferLogMenueOptions {
        eUserTransferLog = 1, eClientTransferLog = 2, eShowTranferLogMenue = 3
    };

    static short ReadTransferLogMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 3]? ";
        short Choice = clsInputValidate::ReadNumberBetween(1, 6, "Enter Number between 1 to 3? ");
        return Choice;
    }

    static void _ShowUserTransferLogScreen()
    {
        clsUserTransferLogScreen::ShowTransferLogScreen();

    }

   static void _ShowClientTransferLogScreen()
    {
        clsClientTransferLogScreen::ShowClientTransferLogScreen();

    }
   


    static void _GoBackToTransferLogScreen()
    {
        cout << "\n\nPress any key to go back to Transfer Menue...";
        system("pause>0");
        ShowTransferLogScreen();

    }

    static void _PerformTransferLogMenueOption(enTransferLogMenueOptions TransferLogMenueOptions)
    {
        switch (TransferLogMenueOptions)
        {
            case enTransferLogMenueOptions::eUserTransferLog:
            {
                system("cls");
                _ShowUserTransferLogScreen();
                _GoBackToTransferLogScreen();
                break;
            }

            case enTransferLogMenueOptions::eClientTransferLog:
            {
                system("cls");
                _ShowClientTransferLogScreen();
                _GoBackToTransferLogScreen();
                break;
            }


            case enTransferLogMenueOptions::eShowTranferLogMenue:
            {
                break;
            }

        }
    }


public:
	
	static void ShowTransferLogScreen()
	{
      
            system("cls");
            _DrawScreenHeader("\tTransfer Login Record Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Transfer Login Record Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] User Transfer Log.\n";
            cout << setw(37) << left << "" << "\t[2] Client Transfer Log.\n";
            cout << setw(37) << left << "" << "\t[3] Transactions Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerformTransferLogMenueOption((enTransferLogMenueOptions)ReadTransferLogMenueOption());
        }
	
};

