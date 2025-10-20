#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"



class clsFindCurrencyScreen  : protected clsScreen
{
private:

	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << "\nCuurency Card:\n";
		cout << "______________________________\n";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n______________________________\n";

	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrencyInfo(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		short Answer;
		cout << "Find By: [1] Code or [2] Country? ";
		Answer = clsInputValidate::ReadShortNumberBetween(1,2);
		if (Answer == 1)
		{
			cout << "\nPlease Enter CurrenyCode: ";
			clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
			_ShowResult(Currency);

		}
		else
		{
			cout << "\nPlease Enter CurrenyCountry: ";
			clsCurrency Currency = clsCurrency::FindByCountry(clsInputValidate::ReadString());
			_ShowResult(Currency);
		}

	}
};

