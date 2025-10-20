

#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>

class clsInputValidate
{
private:

    static void _AddDataLineToFile(string  stDataLine, string PathFile)
    {
        fstream MyFile;
        MyFile.open(PathFile, ios::out );

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static  vector <string> _LoadTheDateAndTimeFromFile(string PathFile)
    {

        vector <string> vDate;

        fstream MyFile;
        MyFile.open(PathFile, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {
                vDate = clsString::Split(Line,"#//#");

               // vDate.push_back(Date);
            }

            MyFile.close();

        }

        return vDate;

    }

    static void _CheckUnlockPeriod(vector <string> vFullDate, short &NumberOfIteration, short &CoefficientOfTime)
    {
        
            string StringDate = vFullDate[0];
            string UnlockTimeString = vFullDate[1];
            int Minutes = stoi(vFullDate[2]);
            NumberOfIteration = stoi(vFullDate[3]);
            CoefficientOfTime = stoi(vFullDate[4]);
           // int AddDays = Minutes / 1440;
            int RemainderMinutes = Minutes % 1440;
            int AddHours = RemainderMinutes / 60;
            int AddMinutes = RemainderMinutes % 60;
            string subTime = "";
            vector<short> UnlockTime;
       

            int  i = 0;
            for (i; i < 2; i++)
            {
              /*hour*/ subTime += UnlockTimeString[i];
            }
            UnlockTime.push_back(stoi(subTime));
            subTime = "";

            for (i++; i < 5; i++)
            {
                /*Minute*/  subTime += UnlockTimeString[i];

            }
            UnlockTime.push_back(stoi(subTime));
            subTime = "";

            for (i++; i < 8; i++)
            {
                /*Second*/ subTime += UnlockTimeString[i];
            }

            UnlockTime.push_back(stoi(subTime));


            clsDate Date = clsDate(StringDate);
            Date.IncreaseDateByXDays(Minutes / 1440);

            UnlockTime[1] += AddMinutes;
            if (UnlockTime[1] > 59)
            {
                UnlockTime[1] = UnlockTime[1] - 59;
                UnlockTime[0]++;
            }

            UnlockTime[0] += AddHours;
            if (UnlockTime[0] > 23)
            {
                UnlockTime[0] = UnlockTime[0] - 23;
                Date.IncreaseDateByOneDay();
            }

          //  Date.IncreaseDateByXDays(AddDays);

            int SecondsToUnlockTime = clsDate::NumberOfSecondsToDateAndTimeEqualTheMomentDateAndTime(Date, UnlockTime);

            
            int IsFirst = 0;

            while (SecondsToUnlockTime > 0)
            {
                int SecondsToUnlockTime = clsDate::NumberOfSecondsToDateAndTimeEqualTheMomentDateAndTime(Date, UnlockTime);

                if (IsFirst == 0)
                {
                    if (SecondsToUnlockTime == 0)
                        break;
                    else if (SecondsToUnlockTime <= 59)
                        cout << "\nPlease Try again After " << (SecondsToUnlockTime + 3) << " Second(s).     ";
                    else if ((SecondsToUnlockTime / 60) <= 59)
                        cout << "\nPlease Try again After " << (SecondsToUnlockTime+3) / 60  << " Minutes(s).     ";

                    else if (((SecondsToUnlockTime / 60) / 60) < 24)
                        cout << "\nPlease Try again After " << ((SecondsToUnlockTime +3)  / 60) / 60  << " Hour(s).     ";

                    else if ((((SecondsToUnlockTime / 60) / 60) / 24) < 7)
                        cout << "\nPlease Try again After " << (((SecondsToUnlockTime +3)/ 60) / 60) / 24   << " Day(s).     ";

                    else if (((((SecondsToUnlockTime / 60) / 60) / 24) / 7) < 4)
                        cout << "\nPlease Try again After " << ((((SecondsToUnlockTime + 3) / 60) / 60) / 24) / 7  << " Week(s).     ";
                    else if (((((SecondsToUnlockTime / 60) / 60) / 24) / 7) / 30 < 12)
                        cout << "\nPlease Try again After " << (((((SecondsToUnlockTime + 3) / 60) / 60) / 24)) / 30 << " Month(s).     ";
                    else
                        cout << "\nPlease Try again After " << ((((((SecondsToUnlockTime +3) / 60) / 60) / 24)) / 30 )/12 << " Year(s).     ";

                }
                else
                {
                    if (SecondsToUnlockTime == 0)
                        break;
                    else if (SecondsToUnlockTime <= 59)
                        cout << "Please Try again After " << SecondsToUnlockTime << " Second(s).     ";
                    else if ((SecondsToUnlockTime / 60) <= 59)
                        cout << "Please Try again After " << SecondsToUnlockTime / 60 << " Minutes(s).     ";

                    else if (((SecondsToUnlockTime / 60) / 60) < 24)
                        cout << "Please Try again After " << (SecondsToUnlockTime / 60) / 60 << " Hour(s).     ";

                    else if ((((SecondsToUnlockTime / 60) / 60) / 24) < 7)
                        cout << "Please Try again After " << ((SecondsToUnlockTime / 60) / 60) / 24 << " Day(s).     ";

                    else if (((((SecondsToUnlockTime / 60) / 60) / 24) / 7) < 4)
                        cout << "Please Try again After " << (((SecondsToUnlockTime / 60) / 60) / 24) / 7 << " Week(s).    ";
                    else if (((((SecondsToUnlockTime / 60) / 60) / 24) / 7) / 30 < 12)
                        cout << "\nPlease Try again After " << (((((SecondsToUnlockTime ) / 60) / 60) / 24)) / 30 << " Month(s).     ";
                    else
                        cout << "\nPlease Try again After " << ((((((SecondsToUnlockTime ) / 60) / 60) / 24)) / 30) / 12 << " Year(s).     ";
                }
                cout << "\r";       
                IsFirst++;
                system("pause>0");        
            }
            cout << "\n";
        
    }

    static void _PreperCoefficientOfTimeAndWaitingTime(short NumberOfIteration, short &CoefficientOfTime, int  &WaitingTime)
    {


        if (NumberOfIteration < 3)
        {
            CoefficientOfTime++;
            WaitingTime = 1;
        }

        else if (NumberOfIteration >= 3 && NumberOfIteration < 7)
        {
            WaitingTime = 5;

            if (NumberOfIteration == 3)
            {
                CoefficientOfTime = 1;
            }
            else
                CoefficientOfTime++;
        }

        else if (NumberOfIteration >= 7 && NumberOfIteration < 9)
        {
            WaitingTime = 15;
            if (NumberOfIteration == 7)
            {
                CoefficientOfTime = 2;
            }
            else
                CoefficientOfTime++;
        }

        else if (NumberOfIteration >= 9 && NumberOfIteration < 11)
        {
            WaitingTime = 1 * 60;
            if (NumberOfIteration == 9)
            {
                CoefficientOfTime = 1;
            }
            else
                CoefficientOfTime++;
        }

        else if (NumberOfIteration >= 11 && NumberOfIteration < 14)
        {
            WaitingTime = 3 * 60;
            if (NumberOfIteration == 11)
            {
                CoefficientOfTime = 1;
            }
            else
                CoefficientOfTime = CoefficientOfTime * 2;
        }

        else if (NumberOfIteration >= 14 && NumberOfIteration < 17)
        {
            WaitingTime = 1 * 60 * 24;

            if (NumberOfIteration == 14)
                CoefficientOfTime = 1;
            else
                CoefficientOfTime++;
        }

        else if (NumberOfIteration >= 17 && NumberOfIteration < 20)
        {
            WaitingTime = 1 * 60 * 24 * 7;

            if (NumberOfIteration == 17)
                CoefficientOfTime = 1;
            else
                CoefficientOfTime++;
        }

        else
        {
            WaitingTime = 1 * 60 * 24 * 30;

            if (NumberOfIteration == 20)
                CoefficientOfTime = 1;
            else
                CoefficientOfTime++;
        }
    }

    static bool _CheckSymbol(string Symbols, char  Answer)
    {
        Symbols = clsString::UpperAllString(Symbols);
        string  a (1,Answer) ;
       a = clsString::UpperAllString(a);
       Answer = a[0];

        for (int i = 0; i < Symbols.length(); i++)
        {
            if (Symbols[i] == Answer)
                return true;
        }
        return false;
    }

public:

    template   <typename T> static bool IsNumberBetween(T Number, T From, T To)
    {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        //Date>=From && Date<=To
        if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
            &&
            (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
            )
        {
            return true;
        }

        //Date>=To && Date<=From
        if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
            &&
            (clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
            )
        {
            return true;
        }

        return false;
    }

    template   <typename T> static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        T Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    template   <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        T Number = ReadNumber<T>();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadNumber<T>();
        }
        return Number;
    }

    static char ReadCharAnswer(string Symbols, string ErrorMessage = "Invalid Symbol, Enter again\n")
    {
        char Ansewr;
        bool CorrectSymbol = false;

     
            while (!(cin >> Ansewr)) 
            {
                CorrectSymbol = _CheckSymbol(Symbols, Ansewr);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
            }
            CorrectSymbol = _CheckSymbol(Symbols, Ansewr);
            while (!CorrectSymbol)
            {
                cin >> Ansewr;
                CorrectSymbol = _CheckSymbol(Symbols, Ansewr);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ErrorMessage;
            }

        return Ansewr;
    }

    static bool IsValideDate(clsDate Date)
    {
        return	clsDate::IsValidDate(Date);
    }

    static string ReadString(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        string S1;
        while (!(cin >> S1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return S1;
    }
    
    static void CheckLogin(string PathFile, short& FaildLoginCount, bool PeriodMode, bool Login = false)
    {
    

        static int  WaitingTime = 0; static short   NumberOfIteration = 0, CoefficientOfTime = 0;

        
        vector <string> vFullDate = _LoadTheDateAndTimeFromFile(PathFile);

        string DateAndTimeAtTheMomnet = "";

        if (Login == true && !vFullDate.empty())
        {
            DateAndTimeAtTheMomnet = vFullDate[0] + "#//#" + vFullDate[1] +
                "#//#" + vFullDate[2] + "#//#" + vFullDate[3] + "#//#" + vFullDate[4] + "#//#" + to_string(Login);

            _AddDataLineToFile(DateAndTimeAtTheMomnet, PathFile);
         }
        else if (FaildLoginCount == 0)
        {

            if (!vFullDate.empty())
                _CheckUnlockPeriod(vFullDate, NumberOfIteration, CoefficientOfTime);
        }
        else
        {
            if (vFullDate.empty() && !PeriodMode)
                return;
            bool _Login = 0;
            if (!vFullDate.empty())
            {
                _CheckUnlockPeriod(vFullDate, NumberOfIteration, CoefficientOfTime);
                 _Login = stoi(vFullDate[5]);
            }

         

            NumberOfIteration++;
            FaildLoginCount = 0;

            _PreperCoefficientOfTimeAndWaitingTime(NumberOfIteration, CoefficientOfTime, WaitingTime);

       
            if (_Login == 1)
            {
                WaitingTime = 1;
                NumberOfIteration = 1;
                CoefficientOfTime = 1;
            }
            WaitingTime = WaitingTime * CoefficientOfTime;

             DateAndTimeAtTheMomnet = clsDate::DateToString(clsDate()) + "#//#" + clsDate::GetTimeOfThisMomentString() +
                "#//#" + to_string(WaitingTime) + "#//#" + to_string(NumberOfIteration) + "#//#" + to_string(CoefficientOfTime) + "#//#" + to_string(Login);

            _AddDataLineToFile(DateAndTimeAtTheMomnet, PathFile);

           
                vFullDate = _LoadTheDateAndTimeFromFile(PathFile);
                _CheckUnlockPeriod(vFullDate, NumberOfIteration, CoefficientOfTime);
            

        }
   }
    
};

