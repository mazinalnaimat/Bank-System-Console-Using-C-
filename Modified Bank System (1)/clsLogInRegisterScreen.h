#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsLogInRegisterScreen : protected clsScreen
{
private:

    static void _PrintLogInRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegister)
    {
        cout << setw(8) << left << "" << "| " << left << setw(25) << LoginRegister.DateTime;
        cout << setw(8) << left << "" << "| " << left << setw(12) << LoginRegister.UserName;
        cout << "| " << left << setw(10) << LoginRegister.Password;
        cout << "| " << left << setw(12) << LoginRegister.Permissions;
     //   cout << setw(8) << left << "" << "\n\t_______________________________________________________";
       // cout << "______________________________________________\n" << endl;

    }

public:
    static void ShowLogInRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pShowLogInRegister))
        {
            return;// this will exit the function and it will not continue
        }

        vector <clsUser::stLoginRegisterRecord> vLoginRegister = clsUser::GetLoginRegisterList();

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

            for (clsUser::stLoginRegisterRecord LoginRegister : vLoginRegister)
            {

                _PrintLogInRegisterRecordLine(LoginRegister);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

