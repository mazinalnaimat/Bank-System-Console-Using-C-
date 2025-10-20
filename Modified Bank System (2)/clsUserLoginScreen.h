#pragma once

#include <iostream>
//#include "clsUserScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsUserMainScreen.h"
#include "clsUserForgotPasswordScreen.h"

class clsUserLoginScreen  :protected clsUserScreen
{

private:


    static  bool _Login()
       {
    
        bool LoginFaild = false;
        bool LoginFaildWithCorrectUserName = false;

        short FaildLoginCount = 0;
        short LoginFaildWithCorrectUserNameCount = 0;
        short PrevoiusFailedLogin = 0;
        clsInputValidate::CheckLogin("Files/LastFailedUserLoginAttempt.txt", FaildLoginCount, false);

        string  UserName, Password;

        do
        {
            if (LoginFaild)
            {
                if (CurrentUser.FailedLoginCount < 3)
                {
                    printf("\n\x1B[31mError - Invalied (UserName / Password )...\033[0m\n");

                    cout << "Did You Forget Your Password ? (Y - N) : ";
                    char Answer = clsInputValidate::ReadCharAnswer("YN");

                    if (Answer == 'Y' || Answer == 'y')
                    {
                        clsUserForgotPasswordScreen::ShowUserForgotPasswordScreen(UserName);
                        CurrentUser = clsUser::Find("");
                        LoginFaild = false;
                        continue;
                    }
                   // cout << "\nYou Have " << 3 - FaildLoginCount << " Trials to login.\n";

                }
            }
            if (FaildLoginCount > 0  )
                cout << "\nYou Have " << 3 - FaildLoginCount << " Trials to login.\n";


            if (CurrentUser.FailedLoginCount == 3 && LoginFaildWithCorrectUserNameCount == 3 && PrevoiusFailedLogin == CurrentUser.FailedLoginCount - 1)
            {
                cout << "\n You are Locked after 3 failed trails\n";
                PrevoiusFailedLogin = 0;

            }

            if (FaildLoginCount == 3)
            {

                clsInputValidate::CheckLogin("Files/LastFailedUserLoginAttempt.txt", FaildLoginCount, true);
            }

            cout << "\n\nEnter User Name? ";
            cin >> UserName;

            cout << "Enter Password? ";
            cin >> Password;

            FaildLoginCount++;



            CurrentUser = clsUser::Find(UserName, Password);

            LoginFaild = CurrentUser.IsEmpty();

            if (LoginFaild == false && CurrentUser.FailedLoginCount < 3)
            {

                clsInputValidate::CheckLogin("Files/LastFailedUserLoginAttempt.txt", FaildLoginCount, false, true);  // To Change Login to (1)
                break;
            }

            CurrentUser = clsUser::Find(UserName);



            LoginFaildWithCorrectUserName = !CurrentUser.IsEmpty();

            if (LoginFaildWithCorrectUserName && CurrentUser.FailedLoginCount == 3)
            {
                cout << "\nYour Account Is Locked";
                cout << "\nPlease, Contact Your Admins\n";
                continue;
            }

            if (LoginFaildWithCorrectUserName && CurrentUser.FailedLoginCount < 3)
            {
                PrevoiusFailedLogin = CurrentUser.FailedLoginCount;
                CurrentUser.FailedLoginCount++;
                LoginFaildWithCorrectUserNameCount++;
                clsUser::enSaveResults SaveResult;
                SaveResult = CurrentUser.Save();
            }


        } while (FaildLoginCount < 4);


      
        CurrentUser.UserRegisterLogIn();
        clsUserMainScreen::ShowUserMainMenue();
        return true;
    }

    
public:


    static bool ShowUserLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t User Login Screen");
       return _Login();
        

    }

};

