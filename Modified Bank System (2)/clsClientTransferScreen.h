
#pragma once
#include <iostream>
#include <iomanip>
#include "clsClientScreen.h"
#include "clsBankClient.h"


using namespace std;

class clsClientTransferScreen : protected clsClientScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n______________________\n";
		cout << "\nFull Name    :" << Client.FullName();
		cout << "\nAcc. Number  :" << Client.AccountNumber();
		cout << "\nBalance      :" << Client.AccountBalance;
		cout << "\n______________________\n";

	}

public:
	static void ShowClientTransferScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tATM");
		double Amount = 0;
		string  DestinationAccountNumber;
		//_DrawScreenHeader("\tTransfer Screen");



		_PrintClientCard(CurrentClient);

		cout << "\n\nPlease Enter Account Number to Transfer To: ";
		DestinationAccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(DestinationAccountNumber) || DestinationAccountNumber == CurrentClient.AccountNumber())
		{
			if(!clsBankClient::IsClientExist(DestinationAccountNumber))
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

		while (Amount > CurrentClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			Amount = clsInputValidate::ReadNumber<double>();

		}
		cout << "\nAre you sure you want to perform this transaction? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			CurrentClient.TransferByClient(Amount, DestinationClient);
			cout << "\nTransfer done Successfully.\n";
		}
		else
		{
			cout << "\nnTransfer Failed.\n";
		}
		_PrintClientCard(CurrentClient);
		_PrintClientCard(DestinationClient);
	}
};
