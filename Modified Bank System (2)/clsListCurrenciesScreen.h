#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsCurrency.h"


class clsListCurrenciesScreen : protected clsUserScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << Currency.Country();
		cout << setw(8) << left << "" << "| " << setw(8) << Currency.CurrencyCode();
		cout << setw(8) << left << "" << "| " << setw(40) << Currency.CurrencyName();
		cout << setw(8) << left << "" << "| " << setw(8) << Currency.Rate() << "\n";
	}

public:
	static void ShowListCurrenciesScreen()
	{
		vector <clsCurrency> vCurrency;
		vCurrency = clsCurrency::GetCurrenciesList();
		string Title = "\tCurrencies List Screen";
		string SubTitle = "\t  (" + to_string(vCurrency.size()) + ") Currency.";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n" << setw(8) << left << "" << "____________________________________________________________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(30) << "Country";
		cout << setw(8) << left << "" << "| " << setw(8) << "Code";
		cout << setw(8) << left << "" << "| " << setw(40) << "Name";
		cout << setw(8) << left << "" << "| " << setw(8) << "Rate/(1$)";
		cout <<"\n" << setw(8) << left << "" << "____________________________________________________________________________________________________________________________________\n\n";

		if (vCurrency.size() == 0)
			cout << "\t\t\t\tNo Currecies Available In the System!\n";
		else
		for (clsCurrency& Currency : vCurrency)
		{
			_PrintCurrencyInfo(Currency);
		}
		cout << "\n" << setw(8) << left << "" << "____________________________________________________________________________________________________________________________________\n\n";

	}
};

