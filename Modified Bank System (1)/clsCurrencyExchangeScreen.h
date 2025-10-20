#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculator.h"


using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

	enum enCurrencyExchangeOperations {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
		eCurrencyCalculator = 4, eMainMenue = 5
	};

	static short ReadCurrencyExcahngeMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static void _GoBackToCurrencyExchangeMenue()
	{
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowCurrencyExchangeMenue();
	}

    static void _ShowListCurrenciesScreen()
    {
        clsListCurrenciesScreen::ShowListCurrenciesScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeOperations CurrencyExchangeOperation)
    {

        switch (CurrencyExchangeOperation)
        {
        case enCurrencyExchangeOperations::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOperations::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOperations::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOperations::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOperations::eMainMenue:
        {
           
        }

        }

    }


public:

	static void ShowCurrencyExchangeMenue()
	{
        system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "==================================================\n";
		cout << setw(37) << left << "" << "\t\t    Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "==================================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "==================================================\n";

        _PerformCurrencyExchangeMenueOption(enCurrencyExchangeOperations(ReadCurrencyExcahngeMenueOption()));
	}
};

