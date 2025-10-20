#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsBankClient.h"


using namespace std;

class clsTransferScreen : protected clsUserScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n_______________________________\n" ;
		cout << "\nFull Name    :" << Client.FullName();
		cout << "\nAcc. Number  :" << Client.AccountNumber();
		cout << "\nBalance      :" << Client.AccountBalance;
		cout << "\n_______________________________\n";

	}

public:
	static void ShowTransferScreen()
	{
		double Amount = 0;
		string SourceAccountNumber, DestinationAccountNumber;
		_DrawScreenHeader("\tTransfer Screen");

		cout << "\n\nPlease Enter Account Number to Transfer From: ";
		SourceAccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(SourceAccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			SourceAccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient SourceClient = clsBankClient::Find(SourceAccountNumber);
		_PrintClientCard(SourceClient);

		cout << "\n\nPlease Enter Account Number to Transfer To: ";
		DestinationAccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(DestinationAccountNumber) || DestinationAccountNumber == SourceAccountNumber)
		{
			if (!clsBankClient::IsClientExist(DestinationAccountNumber))
				cout << "\nAccount number is not found";
			else
				cout << "\nYou can not transfer to yourself";
			cout << ", choose another one: ";
			DestinationAccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient DestinationClient = clsBankClient::Find(DestinationAccountNumber);
		_PrintClientCard(DestinationClient);

		cout << "\nEnter Transfer Amount? ";
		
		 Amount = clsInputValidate::ReadNumber<double>();

		 while (Amount >SourceClient.AccountBalance)
		 {
			 cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			 Amount = clsInputValidate::ReadNumber<double>();

		 }
		 cout << "\nAre you sure you want to perform this transaction? y/n? ";
		 char Answer = 'n';
		 cin >> Answer;

		 if (Answer == 'Y' || Answer == 'y')
		 {
			 SourceClient.TransferByUser(Amount, DestinationClient, CurrentUser.UserName);
				 cout << "\nTransfer done Successfully.\n";
		 }
		 else
		 {
			 cout << "\nnTransfer Failed.\n";
		 }
		 _PrintClientCard(SourceClient);
		 _PrintClientCard(DestinationClient);
	}
};

