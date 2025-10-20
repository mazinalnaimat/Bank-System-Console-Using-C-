

#pragma once
#include <iostream>
#include "clsClientScreen.h"
#include "clsBankClient.h"
#include "clsUserScreen.h"
#include "clsUser.h"

using namespace std;

class clsClientLogInRegisterScreen : protected clsUserScreen
{
private:

    static void _PrintClientLogInRegisterRecordLine(clsBankClient::stClientLoginRegisterRecord ClientLoginRegister)
    {
        cout << setw(8) << left << "" << "| " << left << setw(25) << ClientLoginRegister.DateTime;
        cout << setw(8) << left << "" << "| " << left << setw(10) << ClientLoginRegister.AccountNumber;
        cout << setw(8) << left << "" << "| " << left << setw(30) << ClientLoginRegister.ClientFullName;
        cout << "| " << left << setw(10) << ClientLoginRegister.Password;
        cout << "|    " << left << setw(9) << ClientLoginRegister.Permissions;
    
    }

public:
    static void ShowClientLogInRegisterScreen()
    {
       /* if (!CheckAccessRights(clsUser::enPermissions::pShowClientLogInRegister))
        {
            return;// this will exit the function and it will not continue
        }*/

        vector <clsBankClient::stClientLoginRegisterRecord> vClientLoginRegister = clsBankClient::ClientGetLoginRegisterList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vClientLoginRegister.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t___________________________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(25) << "Data/Time";
        cout << setw(8) << left << "" << "| " << left << setw(10) << "Acc.Number";
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Client Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";

        cout << setw(8) << left << "" << "\n\t___________________________________________________________________";
        cout << "______________________________________________\n" << endl;
     
        if (vClientLoginRegister.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient::stClientLoginRegisterRecord ClientLoginRegister : vClientLoginRegister)
            {

                _PrintClientLogInRegisterRecordLine(ClientLoginRegister);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t___________________________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

