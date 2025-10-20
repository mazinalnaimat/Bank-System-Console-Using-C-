#pragma once
#include<iostream>
#include<vector>


using namespace std;

class clsString

{
private:
	string _Value;


public:

	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}


	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}

	short Length()
	{
		return Length(_Value);

	}

	static short CountWords(string S1)
	{


		string delim = " ";
		short pos = 0;
		string sWord;
		short Counter = 0;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != " ")
			{
				Counter++;
			}
			S1.erase(0, pos + delim.length());
		}


		if (S1 != " ")
		{
			Counter++;
		}
		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	};

	static void PrintFirstLetterOfEachWord(string s1)
	{
		cout << "The First Letter Each of this string:" << endl;
		cout << endl;

		bool isFirstLetter = true;
		for (int i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ' && isFirstLetter)
			{
				cout << s1[i] << endl;
			}
			isFirstLetter = (s1[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWord()
	{
		return PrintFirstLetterOfEachWord(_Value);
	};

	static string UpperFirstLetterOfEachWord(string s1)
	{



		bool IsFirstLetter = true;


		for (int i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ' && IsFirstLetter)
			{
				s1[i] = toupper(s1[i]);
			}
			IsFirstLetter = (s1[i] == ' ' ? true : false);

		}

		return  s1;
	}

	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	};

	static string LowerFirstLetterOfEachWord(string s1)
	{



		bool IsFirstLetter = true;


		for (int i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ' && IsFirstLetter)
			{
				s1[i] = tolower(s1[i]);
			}
			IsFirstLetter = (s1[i] == ' ' ? true : false);

		}

		return  s1;
	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string s1)

	{

		bool IsUpperLetter = true;

		for (int i = 0; i < s1.length(); i++)
		{
			IsUpperLetter = (char(s1[i]) > 64 && char(s1[i]) < 91 ? true : false);

			if (s1[i] != ' ' && !IsUpperLetter)
			{
				int NumLetter = char(s1[i]);
				s1[i] = char(NumLetter - 32);
			}


		}

		return  s1;
	}

	void UpperAllString()
	{
		_Value = UpperAllString(_Value);

	}

	static string LowerAllString(string s1)
	{
		bool IsUpperLetter = true;

		for (int i = 0; i < s1.length(); i++)
		{
			IsUpperLetter = (char(s1[i]) > 64 && char(s1[i]) < 91 ? true : false);

			if (s1[i] != ' ' && IsUpperLetter)
			{
				int NumLetter = char(s1[i]);
				s1[i] = char(NumLetter + 32);
			}
		}

		return  s1;
	}

	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertCharacter(char C1)
	{
		bool IsUpperLetter = true;
		bool IsLowerLetter = true;



		IsUpperLetter = (char(C1) > 64 && char(C1) < 91 ? true : false);
		IsLowerLetter = (char(C1) > 96 && char(C1) < 123 ? true : false);

		if (C1 != ' ' && IsUpperLetter)
		{
			int NumLetter = char(C1);
			C1 = char(NumLetter + 32);
		}

		else if (C1 != ' ' && IsLowerLetter)
		{
			int NumLetter = char(C1);
			C1 = char(NumLetter - 32);
		}


		return  C1;
	}

	static string InvertAllString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertCharacter(S1[i]);
		}
		return  S1;
	}

	void InvertAllString()
	{
		_Value = InvertAllString(_Value);

	}

	static short CountAllLetters(string S1)
	{
		return S1.length();
	};

	short CountAllLetters()
	{
		return CountAllLetters(_Value);

	};

	static short CountCapitalLetters(string S1)
	{

		short Count = 0;
		bool IsUpperLetter = true;


		for (int i = 0; i < S1.length(); i++)
		{
			IsUpperLetter = (char(S1[i]) > 64 && char(S1[i]) < 91 ? true : false);


			if (IsUpperLetter)
			{
				Count++;

			}


		}



		return Count;
	};

	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);

	};

	static short CountSmallLetters(string S1)
	{

		short Count = 0;

		bool IsLowerLetter = true;


		for (int i = 0; i < S1.length(); i++)
		{
			IsLowerLetter = (char(S1[i]) > 96 && char(S1[i]) < 123 ? true : false);


			if (IsLowerLetter)
			{
				Count++;

			}

		}


		return Count;
	};

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);

	};;

	static short CountlLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Count = 0;

		for (int i = 0; i < S1.length(); i++)
		{

			if (MatchCase && Letter == S1[i])
			{
				Count++;
			}
			else if (!MatchCase && (Letter == S1[i] || S1[i] == InvertCharacter(Letter)))
				Count++;
		}
		return Count;
	}

	short CountlLetter(char Letter, bool MatchCase = true)
	{
		return CountlLetter(_Value, Letter, MatchCase);

	}

	static bool IsVowel(char C1)
	{
		string VowelLetters = "aeuioAEIUO";

		for (int i = 0; i < VowelLetters.length(); i++)
		{

			if (C1 == VowelLetters[i])
			{
				return true;
			}
		}
		return 0;

	}

	static short CountVowels(string S1)
	{
		short Count = 0;
		string VowelLetters = "aeuioAEIUO";

		for (int i = 0; i < S1.length(); i++)
		{

			if (IsVowel(S1[i]))
			{
				Count++;
			}

		}
		return Count;

	}

	short CountVowels()
	{
		return CountVowels(_Value);

	}

	static	void PrintAllVowelInSring(string S1)
	{

		cout << "\nVowels in string are: ";
		for (int i = 0; i < S1.length(); i++)
		{

			if (IsVowel(S1[i]))
			{
				cout << S1[i] << "   ";

			}
		}
	}

	void PrintAllVowelInSring()
	{
		return PrintAllVowelInSring(_Value);

	}

	static void PrintEachWordInString(string S1)
	{
		string delim = " "; // delimiter
		cout << "\nYour string wrords are: \n\n";
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, pos + delim.length()); /* erase() until
		   positon and move to next word. */
		}
		if (S1 != "")
		{
			cout << S1 << endl; // it print last word of the string.
		}
	}

	void PrintEachWordInString()
	{
		return PrintEachWordInString(_Value);
	}

	static vector<string> Split(string S1, string Delim)
	{
		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word   
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;
	}

	vector<string> Split(string Delim)
	{
		return  Split(_Value, Delim);

	}

	static string TrimLeft(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}

	void TrimLeft()

	{
		_Value = TrimLeft(_Value);

	}

	static string TrimRight(string S1)
	{
		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimRight()
	{
		_Value = TrimRight(_Value);

	}

	static string Trim(string S1)
	{
		return (TrimLeft(TrimRight(S1)));
	}

	void Trim()
	{
		_Value = Trim(_Value);

	}

	static string JoinString(vector<string> vString, string Delim)
	{
		string S1 = "";
		for (string& s : vString)
		{
			S1 = S1 + s + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());

	}

	static string JoinString(string arrString[], short Length, string Delim)
	{
		string S1 = "";
		for (short i = 0; i < Length; i++)
		{
			S1 = S1 + arrString[i] + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}

	static string ReverseWordInString(string S1)
	{
		string S2 = "";

		vector <string> vString = Split(S1, " ");

		vector <string> ::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1);
		return S2;

	}

	void ReverseWordInString()
	{
		_Value = ReverseWordInString(_Value);

	}

	static string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}

	void ReplaceWordInStringUsingBuiltInFunction(string StringToReplace, string sRepalceTo)
	{
		_Value = ReplaceWordInStringUsingBuiltInFunction(_Value, StringToReplace, sRepalceTo);
	}

	static string ReplaceWordInStringUsingSplit(string S1, string OldWord, string NewWord, bool MatchCase = true)
	{


		vector <string> vString = Split(S1, " ");

		vector <string> ::iterator iter;


		for (iter = vString.begin(); iter != vString.end(); iter++)
		{
			if (MatchCase)
			{
				if (*iter == OldWord)
					*iter = NewWord;

			}
			else
			{
				if (UpperAllString(*iter) == UpperAllString(OldWord))
				{
					*iter = NewWord;
				}
			}


		}
		return JoinString(vString, " ");

	}

	void ReplaceWordInStringUsingSplit(string OldWord, string NewWord, bool MatchCase = true)
	{
		_Value = ReplaceWordInStringUsingSplit(_Value, OldWord, NewWord, MatchCase);

	}

	static string RemovePunctuation(string S1)
	{
		string S2 = "";

		for (short i = 0; i < S1.length(); i++)
		{

			if (!ispunct(S1[i]))
			{
				S2 += S1[i];

			}
		}
		S1 = S2;
		return S2;
	}

	void RemovePunctuation()
	{
		_Value = RemovePunctuation(_Value);

	}

	static string GetLine(int Length, char Char)
	{
		string Line = "";
		for (short i = 0; i < Length; i++)
			Line += Char;

		return Line;
	}
};

