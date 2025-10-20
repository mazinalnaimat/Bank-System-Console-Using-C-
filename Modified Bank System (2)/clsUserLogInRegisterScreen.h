#pragma once
#include <iostream>
#include "clsUserScreen.h"
#include "clsUser.h"

using namespace std;

class clsUserLogInRegisterScreen : protected clsUserScreen
{
private:

    static void _PrintUserLogInRegisterRecordLine(clsUser::stUserLoginRegisterRecord LoginRegister)
    {
        cout << setw(8) << left << "" << "| " << left << setw(25) << LoginRegister.DateTime;
        cout << setw(8) << left << "" << "| " << left << setw(12) << LoginRegister.UserName;
        cout << "| " << left << setw(10) << LoginRegister.Password;
        cout << "| " << left << setw(12) << LoginRegister.Permissions;


    }

public:
    static void ShowUserLogInRegisterScreen()
    {
       /* if (!CheckAccessRights(clsUser::enPermissions::pShowUserLogInRegister))
        {
            return;// this will exit the function and it will not continue
        }*/

        vector <clsUser::stUserLoginRegisterRecord> vLoginRegister = clsUser::GetUserLoginRegisterList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegister.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Data/Time";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vLoginRegister.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser::stUserLoginRegisterRecord LoginRegister : vLoginRegister)
            {

                _PrintUserLogInRegisterRecordLine(LoginRegister);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

