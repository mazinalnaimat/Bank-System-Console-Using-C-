
#pragma once
#include <iostream>
#include "clsClientScreen.h"
#include "clsBankClient.h"

class clsClientInfoScreen : protected clsClientScreen
{



    static void _PrintFullClientInfo(clsBankClient Client)
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
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\n_______________________________________\n";

    }

public:
	static void ShowClientInfoScreen()
	{
        system("cls");
        _DrawScreenHeader("\t\tATM");
        _PrintFullClientInfo(CurrentClient);
	}

	
};

