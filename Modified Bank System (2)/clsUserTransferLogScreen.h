#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsUserTransferLogScreen : protected clsUserScreen
{
private:

	static void _PrintUserTranferLogRecord(clsBankClient::stUserTransferLogRecord Record)
	{
		cout << setw(12) << left << "" << "| " << setw(25) << left << Record.DateTime;
		cout << "| " << setw(8) << left << Record.SourceAccNum;
		cout << "| " << setw(8) << left << Record.DestinationAccNum;
		cout << "| " << setw(10) << left << Record.Amount;
		cout << "| " << setw(10) << left << Record.SourceAccBal;
		cout << "| " << setw(10) << left << Record.DestinationAccBal;
		cout << "| " << setw(8) << left << Record.UserName << "|\n";

	}



public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stUserTransferLogRecord> vRecord = clsBankClient::GetUserTransfersLogList();
		string Title = "  User Transfer  Log List Screen";
		string SubTitle = "\t   " + to_string(vRecord.size() )+ " Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n" << setw(12) << left << "" << "______________________________________________________________________________________________\n\n";
		cout << setw(12) << left << "" << "| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(8) << left << "s.Acct";
		cout << "| " << setw(8) << left << "d.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(8) << left << "User";
		cout << "|\n" << setw(12) << left << "" << "______________________________________________________________________________________________\n\n";


		for (clsBankClient::stUserTransferLogRecord Record : vRecord)
		{
			_PrintUserTranferLogRecord(Record);
		}
		cout << setw(12) << left << "" << "______________________________________________________________________________________________\n\n";

	}
};

