#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTranferLogRecord(clsBankClient::stTransferLogRecord Record)
	{
		cout << setw(12) << left << "" << "| " << setw(25) << left << Record.DateTime;
		cout << "| " << setw(8) << left << Record.SourceAccNum;
		cout << "| " << setw(8) << left << Record.DestinationAccNum;
		cout << "| " << setw(10) << left << Record.Amount;
		cout << "| " << setw(10) << left << Record.SourceAccBal;
		cout << "| " << setw(10) << left << Record.DestinationAccBal;
		cout << "| " << setw(8) << left << Record.UserName << "\n";

	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vRecord = clsBankClient::GetTransfersLogList();
		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t   " + to_string(vRecord.size() )+ " Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n" << setw(12) << left << "" << "_________________________________________________________________________________________________\n\n";
		cout << setw(12) << left << "" << "| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(8) << left << "s.Acct";
		cout << "| " << setw(8) << left << "d.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(8) << left << "User";
		cout << "\n" << setw(12) << left << "" << "_________________________________________________________________________________________________\n\n";


		for (clsBankClient::stTransferLogRecord Record : vRecord)
		{
			_PrintTranferLogRecord(Record);
		}
		cout << setw(12) << left << "" << "_________________________________________________________________________________________________\n\n";

	}
};

