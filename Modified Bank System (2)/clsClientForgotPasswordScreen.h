
#pragma once

#include <iostream>
#include "clsString.h"
#include "clsClientScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"


class clsClientForgotPasswordScreen : protected clsClientScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
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
		cout << "\n___________________\n";

	}


public :
	static void ShowClientForgotPasswordScreen(string AccountNumber)
	{
		system("cls");
		_DrawScreenHeader("\t Client Forget Passord Screen");
		CurrentClient= clsBankClient:: Find(AccountNumber);
		if (CurrentClient.IsEmpty())
		{
			printf("\n\x1B[31mError - Invalied (AccountNumber  )...\033[0m\n");
		}
		else
		{
			string Email;
			cout << "Enter Your (Email) : ";
			Email = clsInputValidate::ReadString();
			if (CurrentClient.Email == Email)
			{
				cout <<  "\n" << CurrentClient.SafeQuestion << "\n";
				string Answer = clsInputValidate::ReadString();
				if (clsString::UpperAllString(Answer) == clsString::UpperAllString(CurrentClient.AnswerOfSafeQuestion))
				{
					cout << "Enter The New Password: ";
					string Password = clsInputValidate::ReadString();
					CurrentClient.PinCode = (Password);

					clsBankClient::enSaveResults SaveResult;

					SaveResult = CurrentClient.Save();

					switch (SaveResult)
					{
						case  clsBankClient::enSaveResults::svSucceeded:
						{
							cout << "\nPassword Updated Successfully :-)\n";

							_PrintClient(CurrentClient);
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
		_DrawScreenHeader("\t  Client Login Screen");
	}
};

