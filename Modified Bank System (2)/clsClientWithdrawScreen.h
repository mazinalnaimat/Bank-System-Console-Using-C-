#pragma once
#include <iostream>
#include "clsClientScreen.h"
#include "clsBankClient.h"

class clsClientWithdrawScreen : protected clsClientScreen
{


    static void _PrintClientInfo(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_______________________________________\n";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();

        /*cout << "\nPassword    : " << Client.PinCode;
         cout << "\nBalance     : " << Client.AccountBalance;
         cout << "\nPermissions : " << Client.AccountBalance;
         cout << "\nLock        : " << Client.AccountBalance;*/

        cout << "\n_______________________________________\n";

    }

public:
	static void ShowClientWithdrawScreen()
	{
        system("cls");
        _DrawScreenHeader("\t\tATM");
        _PrintClientInfo(CurrentClient);

        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadNumber<double>();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (CurrentClient.Withdraw(Amount))
            {
                CurrentClient.Withdraw(Amount);
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << CurrentClient.AccountBalance;
            }
            else
            {
                cout << "\nCan not withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << CurrentClient.AccountBalance;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

	}
};

