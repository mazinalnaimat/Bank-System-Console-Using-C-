#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"


class clsUpdateCurrencyRateScreen : protected clsScreen
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


public:
	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\t  Update Rate Screen");

		
			cout << "\nPlease Enter Curreny Code: ";
			clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
			while (Currency.IsEmpty())
			{
				cout << "\nPlease Enter The Correct Curreny Code: ";
				 Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
			}			
			_PrintCurrencyInfo(Currency);
			
			cout << "\n\nAre you syre you want to update the rate of this Currency? y/n? ";
			char Answer = 'n';
			cin >> Answer;
			while (Answer != 'n' && Answer!='N' && Answer != 'y' && Answer != 'Y')
			{
				cout << "\nThe value is unavailable";
				cout << "\nPlease, Enter The Correct Value.";
				cout << "\nAre you syre you want to update the rate of this Currency? y/n? ";
				cin >> Answer;
			}
			if (Answer == 'y' || Answer == 'Y')
			{
				cout << "\n\nUpdate Currency Rate:";
				cout << "\n____________________________";
				cout << "\nEnter New Rate: ";
				Currency.UpdateRate(clsInputValidate::ReadFloatNumber());

				cout << "\n\nCurrency Rate Updated Successfully :-)";
				_PrintCurrencyInfo(Currency);

			}
			
		

	}
};

