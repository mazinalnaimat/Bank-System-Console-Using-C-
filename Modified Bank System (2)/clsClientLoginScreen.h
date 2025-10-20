#pragma once

#include <iostream>
#include "clsClientScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsATM_MainScreen.h"
#include "clsClientForgotPasswordScreen.h"

class clsClientLoginScreen :protected clsClientScreen
{

private:



    static  bool _Login()
    {

        bool LoginFaild = false;
        bool LoginFaildWithCorrectUserName = false;

        short FaildLoginCount = 0;
        short LoginFaildWithCorrectUserNameCount = 0;
        short PrevoiusFailedLogin = 0;
        clsInputValidate::CheckLogin("Files/LastFailedClientLoginAttempt.txt", FaildLoginCount, false);

        string  AccountNumber, Password;
    
        do
        {
            if (LoginFaild)
            {
                if (CurrentClient.FailedLoginCount < 3)
                {
                    printf("\n\x1B[31mError - Invalied (AccountNumber / Password )...\033[0m\n");

                    cout << "Did You Forget Your Password ? (Y - N) : ";
                    char Answer = clsInputValidate::ReadCharAnswer("YN");

                    if (Answer == 'Y' || Answer == 'y')
                    {
                        clsClientForgotPasswordScreen::ShowClientForgotPasswordScreen(AccountNumber);
                        CurrentClient = clsBankClient::Find("");
                        LoginFaild = false;
                        continue;
                    }
                 //   cout << "\nYou Have " << 3 - FaildLoginCount << " Trials to login.\n";

                }
            }
            if(FaildLoginCount>0 )
                     cout << "\nYou Have " << 3 - FaildLoginCount << " Trials to login.\n";

                if (CurrentClient.FailedLoginCount == 3 && LoginFaildWithCorrectUserNameCount == 3 && PrevoiusFailedLogin == CurrentClient.FailedLoginCount-1)
                {
                    cout << "\nYou are Locked after 3 failed trails\n"; 
                    PrevoiusFailedLogin = 0;
                }

                if (FaildLoginCount == 3)
                {

                    clsInputValidate::CheckLogin("Files/LastFailedClientLoginAttempt.txt", FaildLoginCount, true);
                }

                cout << "\n\nEnter Account Number? ";
                cin >> AccountNumber;

                cout << "Enter Password? ";
                cin >> Password;

                FaildLoginCount++;

     

                CurrentClient = clsBankClient::Find(AccountNumber, Password);

                LoginFaild = CurrentClient.IsEmpty();

                if (LoginFaild == false && CurrentClient.FailedLoginCount<3)
                {
                                       
                    clsInputValidate::CheckLogin("Files/LastFailedClientLoginAttempt.txt", FaildLoginCount, false,true);  // To Change Login to (1)

                    break;
                }

                CurrentClient = clsBankClient::Find(AccountNumber);



                LoginFaildWithCorrectUserName = !CurrentClient.IsEmpty();

                if (LoginFaildWithCorrectUserName && CurrentClient.FailedLoginCount == 3)
                {
                    cout << "\nYour Account Is Locked";
                    cout << "\nPlease,Contact the technical support Bank In headquarters\n";
                    continue;
                }

                if (LoginFaildWithCorrectUserName && CurrentClient.FailedLoginCount < 3)
                {
                    PrevoiusFailedLogin = CurrentClient.FailedLoginCount;
                    CurrentClient.FailedLoginCount++;
                    LoginFaildWithCorrectUserNameCount++;
                    clsBankClient::enSaveResults SaveResult;
                    SaveResult = CurrentClient.Save();
                }


            } while (FaildLoginCount < 4 );

       
        CurrentClient.ClientRegisterLogIn();
        clsATM_MainScreen::ShowATM_MainMenue();
        return true;
    }

public:


    static bool ShowCleintLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Client Login Screen");
        return _Login();


    }
};

