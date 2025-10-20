#pragma once
#include <iostream>
#include <iomanip>
#include "clsUserScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"


class clsCurrencyCalculator : protected clsUserScreen
{
private:

	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << "\n\nConvert From:";
		cout << "______________________________\n";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nName       :" << Currency.CurrencyName();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n______________________________\n";

	}


public:
	static void ShowCurrencyCalculatorScreen()
	{
		
		char Answer = 'y';
		while (Answer == 'y' || Answer == 'Y')
		{
		    system("cls");

			_DrawScreenHeader("\t  Currency Calculator Screen");

			cout << "\nPlease Enter Currency1 Code: ";
			clsCurrency CurrencyFrom = clsCurrency::FindByCode(clsInputValidate::ReadString());
			while (CurrencyFrom.IsEmpty())
			{
				cout << "\nPlease Enter The Correct Currency1 Code: ";
				CurrencyFrom = clsCurrency::FindByCode(clsInputValidate::ReadString());
			}

			cout << "\nPlease Enter Currency2 Code: ";
			clsCurrency CurrencyTo = clsCurrency::FindByCode(clsInputValidate::ReadString());
			while (CurrencyTo.IsEmpty())
			{
				cout << "\nPlease Enter The Correct Currency2 Code: ";
				CurrencyTo = clsCurrency::FindByCode(clsInputValidate::ReadString());
			}

			cout << "\nEnter Amount to Exchange: ";
			double Amount = clsInputValidate::ReadNumber<double>();

			_PrintCurrencyInfo(CurrencyFrom);

			double ConverteAmount = (1 / CurrencyFrom.Rate()) * Amount*CurrencyTo.Rate();
			
			//Teacher Solution			
			/*
		
			double ConverteAmount = Currency1.ConvertToOtherCurrency(Amount, Currency2);
			
			*/
			
			cout << "\n" << Amount << " " << CurrencyFrom.CurrencyCode()
				<< " = " << ConverteAmount << " " << CurrencyTo.CurrencyCode();

			cout << "\nDo you  want to perform Another Calculation? y/n? ";
			cin >> Answer;
			while (Answer != 'n' && Answer != 'N' && Answer != 'y' && Answer != 'Y')
			{
				cout << "\nThe value is unavailable";
				cout << "\nPlease, Enter The Correct Value.";
				cout << "\nDo you  want to perform Another Calculation? y/n? ";
				cin >> Answer;
			}

		}

	


	}
}
;
