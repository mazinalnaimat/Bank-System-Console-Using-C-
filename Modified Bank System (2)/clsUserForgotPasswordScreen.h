
#pragma once

#include <iostream>
#include "clsString.h"
#include "clsUserScreen.h"
#include "clsUser.h"
#include "clsUtil.h"


class clsUserForgotPasswordScreen : protected clsUserScreen
{


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
	static void ShowUserForgotPasswordScreen(string UserName)
	{
		system("cls");
		_DrawScreenHeader("\t Client Forget Passord Screen");
		CurrentUser = clsUser::Find(UserName);
		if (CurrentUser.IsEmpty())
		{
			printf("\n\x1B[31mError - Invalied (UserName)...\033[0m\n");
		}
		else
		{
			string Email;
			cout << "Enter Your (Email) : ";
			Email = clsInputValidate::ReadString();
			if (CurrentUser.Email == Email)
			{
				cout << "\n" << CurrentUser.SafeQuestion << "\n";
				string Answer = clsInputValidate::ReadString();
				if (clsString::UpperAllString(Answer) == clsString::UpperAllString(CurrentUser.AnswerOfSafeQuestion))
				{
					cout << "Enter The New Password: ";
					string Password = clsInputValidate::ReadString();
					CurrentUser.Password = (Password);

					clsUser::enSaveResults SaveResult;

					SaveResult = CurrentUser.Save();

					switch (SaveResult)
					{
					case  clsBankClient::enSaveResults::svSucceeded:
					{
						cout << "\nPassword Updated Successfully :-)\n";

						_PrintUser(CurrentUser);
						break;
					}
					case clsBankClient::enSaveResults::svFaildEmptyObject:
					{
						cout << "\nError account was not saved because it's Empty";
						break;

					}
					}
				}
				else
				{
					printf("\n\x1B[31mError - Invalied (Answer)...\033[0m\n");
				}
			}
			else
			{
				printf("\n\x1B[31mError - Invalied (Email)...\033[0m\n");

			}
		}
		system("pause>0");
		system("cls");
		_DrawScreenHeader("\t  User Login Screen");
	}

};

