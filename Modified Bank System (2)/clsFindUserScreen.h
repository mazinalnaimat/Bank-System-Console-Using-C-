#pragma once
#include <iostream>
#include "clsUserScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsUserScreen
{

private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n____________________________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;

        if (User.FailedLoginCount == 3)
            cout << "\nLock        :  1";
        else
            cout << "\nLock        : 0";

        cout << "\nFailed Login: " << User.FailedLoginCount;

        cout << "\n____________________________________\n";

    }
public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};

