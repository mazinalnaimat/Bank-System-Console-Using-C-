#pragma once
#include <iostream>
#include "clsUserScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen :protected clsUserScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n______________________________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\nPermissions : " << Client.Permissions;

        if (Client.FailedLoginCount == 3)
            cout << "\nLock        : 1";
        else
            cout << "\nLock        : 0";

        cout << "\nFailed Login: " << Client.FailedLoginCount;
        cout << "\n______________________________________\n";

    }

public:

    static void ShowFindClientScreen()
    {
       /*if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }*/

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);

    }

};

