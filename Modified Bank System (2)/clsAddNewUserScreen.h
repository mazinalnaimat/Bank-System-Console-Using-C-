#pragma once

#include <iostream>
#include "clsUserScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsUserScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();


        cout << "\nEnter The List of  Safe Question [1 - 5]: \n";

        vector <string> vQuestion = User.Questions();

        int CountQuestion = 0;

        for (string& Question : vQuestion)
        {
            CountQuestion++;
            cout << "\n[" << CountQuestion << "] " << Question;
        }

        cout << "\n\nEnter The Number of Safe Question [1 - 5]: ";
        short Answer = clsInputValidate::ReadNumberBetween<short>(1, 5);
        User.SafeQuestion = vQuestion[Answer - 1];

        cout << "\nEnter the answer of Safe Question : ";

        User.AnswerOfSafeQuestion = clsInputValidate::ReadString();
        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

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

        cout << "\nShow Client List? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
          /*[1]*/    Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
           /*[2]*/   Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[3]*/    Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[4]*/   Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[5]*/   Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[6]*/   Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[7]*/   Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow User Login Register? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[8]*/   Permissions += clsUser::enPermissions::pShowUserLogInRegister;
        }

        cout << "\nShow Client Login Register? y/n? ";
         Answer = clsInputValidate::ReadCharAnswer(Symbols);
        if (Answer == 'y' || Answer == 'Y')
        {
            /*[9]*/   Permissions += clsUser::enPermissions::pShowUserLogInRegister;
        }



        return Permissions;

    }

public:

    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }



};

