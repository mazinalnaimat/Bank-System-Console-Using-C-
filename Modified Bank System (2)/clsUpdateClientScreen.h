#pragma once
#include <iostream>
#include "clsUserScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsUserScreen

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

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<double>();

        cout << "\nEnter The List of  Safe Question [1 - 5]: \n";

        vector <string> vQuestion = Client.Questions();

        int CountQuestion = 0;

        for (string& Question : vQuestion)
        {
            CountQuestion++;
            cout << "\n[" << CountQuestion << "] " << Question;
        }


        cout << "\n\nEnter The Number of Safe Question [1 - 5]: ";
        short Answer = clsInputValidate::ReadNumberBetween<short>(1, 5);
        Client.SafeQuestion = vQuestion[Answer - 1];

        cout << "\nEnter the answer of Safe Question : ";
        Client.AnswerOfSafeQuestion = clsInputValidate::ReadString();
        cout << "\nEnter Permission: ";
        Client.Permissions = _ReadPermissionsToSet();
    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';

        string Symbols = "YN";
        cout << "\nDo you want to give full access? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nDeposit ? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[1]*/  Permissions += clsBankClient::enPermissions::pDeposit;
        }

        cout << "\nWithdraw ? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[2]*/  Permissions += clsBankClient::enPermissions::pWithdraw;
        }

        cout << "\nShow Balance? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[3]*/ Permissions += clsBankClient::enPermissions::pShowBalance;
        }

        cout << "\nTransfer? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[4]*/ Permissions += clsBankClient::enPermissions::pTransfer;
        }

        cout << "\nCLient Info? y/n? ";
        Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[5]*/ Permissions += clsBankClient::enPermissions::pTransfer;
        }

        return Permissions;

    }

public:

    static void ShowUpdateClientScreen()
    {
       /* if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
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

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            _ReadClientInfo(Client1);

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

