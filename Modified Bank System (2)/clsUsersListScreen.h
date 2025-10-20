#pragma once

#include <iostream>
#include "clsUserScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsUsersListScreen :protected clsUserScreen
{

private:
    static void _PrintUserRecordLine(clsUser User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

        if (User.FailedLoginCount == 3)
            cout << "|   " << setw(4) << left << "1";

        else
            cout << "|   " << setw(4) << left << "0";
        cout << "|     " << left << setw(10) << User.FailedLoginCount;
    }

public:

    static void ShowUsersList()
    {
        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________";
        cout << "__________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "| " << left << setw(6) << "Lock";
        cout << "| " << left << setw(12) << "Faild Login";
        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________";
        cout << "__________________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________";
        cout << "__________________________________________________\n" << endl;
    }

};

