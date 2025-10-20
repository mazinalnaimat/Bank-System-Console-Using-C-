

#pragma once
#include <iostream>
#include "clsUserScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUnlockClientAccountScreen :protected clsUserScreen

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

    static void ShowUnlockClientAccountScreen()
    {
       /* if (!CheckAccessRights(clsUser::enPermissions::pUnlockClientAccount))
        {
            return;// this will exit the function and it will not continue
        }*/

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        if (Client1.FailedLoginCount != 3)
        {
            cout << "\nThe Client Account Is Unlock\n";
                return;
        }

        cout << "\nAre you sure you weant to unlock to this Client Acconut ? (Y - N)  ";

        char Answer = clsInputValidate::ReadCharAnswer("YN");
  
        if (Answer == 'y' || Answer == 'Y')
        {

            Client1.FailedLoginCount = 0;
            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";

                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;

            }

            }

        }

    }
};

