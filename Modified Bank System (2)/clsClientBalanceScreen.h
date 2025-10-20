#pragma once
#include <iostream>
#include "clsClientScreen.h"
#include "clsBankClient.h"

class clsClientBalanceScreen : protected clsClientScreen
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
        cout << "\nBalance     : " << Client.AccountBalance;

       /*cout << "\nPassword    : " << Client.PinCode;
        /*cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\nPermissions : " << Client.AccountBalance;
        cout << "\nLock        : " << Client.AccountBalance;*/

        cout << "\n_______________________________________\n";


    }

public:
	static void ShowClientBalanceScreen()
	{
        system("cls");
        _DrawScreenHeader("\t\tATM");
        _PrintClientInfo(CurrentClient);
	}
};

