#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsClientTransferLogScreen : protected clsUserScreen
{
private:

	static void _PrintClientTranferLogRecord(clsBankClient::stClientTransferLogRecord Record)
	{
		cout << setw(12) << left << "" << "| " << setw(25) << left << Record.DateTime;
		cout << "| " << setw(8) << left << Record.SourceAccNum;
		cout << "| " << setw(8) << left << Record.DestinationAccNum;
		cout << "| " << setw(10) << left << Record.Amount;
		cout << "| " << setw(10) << left << Record.SourceAccBal;
		cout << "| " << setw(10) << left << Record.DestinationAccBal;
		cout << "| " << setw(21) << left << Record.ClientFullName << "|\n";

	}



public:

	static void ShowClientTransferLogScreen()
	{
		vector <clsBankClient::stClientTransferLogRecord> vRecord = clsBankClient::GetClientTransfersLogList();
		string Title = "  Client Transfer  Log List Screen";
		string SubTitle = "\t   " + to_string(vRecord.size()) + " Record(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n" << setw(12) << left << "" << "___________________________________________________________________________________________________________\n\n";
		cout << setw(12) << left << "" << "| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(8) << left << "s.Acct";
		cout << "| " << setw(8) << left << "d.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(21) << left << "Full Name";
		cout << "|\n" << setw(12) << left << "" << "___________________________________________________________________________________________________________\n\n";


		for (clsBankClient::stClientTransferLogRecord Record : vRecord)
		{
			_PrintClientTranferLogRecord(Record);
		}
		cout << "\n" << setw(12) << left << "" << "___________________________________________________________________________________________________________\n\n";

	}
};

