#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsUtil.h"

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;
    int _Permissions;
    string _SafeQuestion;
    string _AnswerOfSafeQuestion;
    short _FailedLoginCount = 0;


    struct stUserTransferLogRecord;

    static stUserTransferLogRecord _ConvertUserTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stUserTransferLogRecord UserTransferLogRecord;


        vector <string> TransferLogDataLine = clsString::Split(Line, Seperator);
        UserTransferLogRecord.DateTime = TransferLogDataLine[0];
        UserTransferLogRecord.SourceAccNum = TransferLogDataLine[1];
        UserTransferLogRecord.DestinationAccNum = TransferLogDataLine[2];
        UserTransferLogRecord.Amount = stoi(TransferLogDataLine[3]);
        UserTransferLogRecord.SourceAccBal = stoi(TransferLogDataLine[4]);
        UserTransferLogRecord.DestinationAccBal = stoi(TransferLogDataLine[5]);
        UserTransferLogRecord.UserName = TransferLogDataLine[6];

        return UserTransferLogRecord;

    }

    struct stClientTransferLogRecord;

    static stClientTransferLogRecord _ConvertClientTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stClientTransferLogRecord ClientTransferLogRecord;

        
        vector <string> TransferLogDataLine = clsString::Split(Line, Seperator);
        ClientTransferLogRecord.DateTime = TransferLogDataLine[0];
        ClientTransferLogRecord.SourceAccNum = TransferLogDataLine[1];
        ClientTransferLogRecord.DestinationAccNum = TransferLogDataLine[2];
        ClientTransferLogRecord.Amount = stoi(TransferLogDataLine[3]);
        ClientTransferLogRecord.SourceAccBal = stoi(TransferLogDataLine[4]);
        ClientTransferLogRecord.DestinationAccBal = stoi(TransferLogDataLine[5]);
        ClientTransferLogRecord.ClientFullName= TransferLogDataLine[6];

        return ClientTransferLogRecord;

    }

    struct stClientLoginRegisterRecord;

    static stClientLoginRegisterRecord _ConvertClientLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stClientLoginRegisterRecord ClientLoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        ClientLoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        ClientLoginRegisterRecord.AccountNumber = LoginRegisterDataLine[1];
        ClientLoginRegisterRecord.ClientFullName = LoginRegisterDataLine[2];
        ClientLoginRegisterRecord.Password = clsUtil::DecryptionText(LoginRegisterDataLine[3], 2);
        ClientLoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[4]);

        return ClientLoginRegisterRecord;

    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::DecryptionText( vClientData[5],2), stod(vClientData[6]), stoi(vClientData[7]), stoi(vClientData[8]), vClientData[9], vClientData[10]);
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += clsUtil::EncryptionText(Client.PinCode,2) + Seperator;
        stClientRecord += to_string(Client.AccountBalance) + Seperator;
        stClientRecord += to_string(Client.Permissions) + Seperator;
        stClientRecord += to_string(Client.FailedLoginCount) + Seperator;
        stClientRecord += (Client.SafeQuestion) + Seperator;
        stClientRecord += (Client.AnswerOfSafeQuestion) ;

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Files/Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Files/Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Files/Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0, 0, 0,"","");
    }

    string _PrepareUserTransferLogRecord(double Amount,  clsBankClient DestinationClient, string  UserName, string Seperator = "#//#")
    {
        string TransferRecord = "";
        TransferRecord += clsDate::DateToString(clsDate());
        TransferRecord += " - " + clsDate::GetTimeOfThisMomentString() + Seperator;
        TransferRecord += AccountNumber() + Seperator;
        TransferRecord += DestinationClient.AccountNumber() + Seperator;
        TransferRecord += to_string(Amount) + Seperator;
        TransferRecord += to_string(AccountBalance) + Seperator;
        TransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferRecord += UserName;
        return TransferRecord;

    }

    string _PrepareClientTransferLogRecord(double Amount, clsBankClient DestinationClient, string Seperator = "#//#")
    {
        string ClientTransferRecord = "";
        ClientTransferRecord += clsDate::DateToString(clsDate());
        ClientTransferRecord += " - " + clsDate::GetTimeOfThisMomentString() + Seperator;
        ClientTransferRecord += AccountNumber() + Seperator;
        ClientTransferRecord += DestinationClient.AccountNumber() + Seperator;
        ClientTransferRecord += to_string(Amount) + Seperator;
        ClientTransferRecord += to_string(AccountBalance) + Seperator;
        ClientTransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        ClientTransferRecord += FullName();
        return ClientTransferRecord;

    }

    void _RegisterUserTransferLog(float Amount, clsBankClient DestinationClinet, string UserName )
    {
        string stDataLine = _PrepareUserTransferLogRecord(Amount, DestinationClinet, UserName);

        fstream MyFile;
        MyFile.open("Files/UserTransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void _RegisterClientTransferLog(float Amount, clsBankClient DestinationClinet)
    {
        string stDataLine = _PrepareClientTransferLogRecord(Amount, DestinationClinet);

        fstream MyFile;
        MyFile.open("Files/ClientTransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    string _PrepareClientLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate());
        LoginRecord += " - " + clsDate::GetTimeOfThisMomentString() + Seperator;
        LoginRecord += _AccountNumber + Seperator;
        LoginRecord += FullName() + Seperator;
        LoginRecord += clsUtil::EncryptionText(_PinCode, 2) + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;

    }


public:
    enum enPermissions {pAll= -1,  pDeposit = 1, pWithdraw = 2, pShowBalance = 4, 
        pTransfer = 8, pClientInfo = 16};

    struct stClientLoginRegisterRecord
    {
        string DateTime;
        string AccountNumber;
        string ClientFullName;
        string Password;
        int Permissions;

    };
    
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance, int Permissions, short FailedLoginCount,string SafeQuestion, string AnswerOfSafeQuestion) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
        _Permissions = Permissions;
        _FailedLoginCount = FailedLoginCount;
        _SafeQuestion = SafeQuestion;
        _AnswerOfSafeQuestion = AnswerOfSafeQuestion;
    }

    struct stUserTransferLogRecord
    {
        string DateTime;
        string SourceAccNum;
        string DestinationAccNum;
        double Amount;
        double SourceAccBal;
        double DestinationAccBal;
        string UserName;
    };

    struct stClientTransferLogRecord
    {
        string DateTime;
        string SourceAccNum;
        string DestinationAccNum;
        double Amount;
        double SourceAccBal;
        double DestinationAccBal;
        string ClientFullName;
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    string GetSafeQuestion()
    {
        return _SafeQuestion;
    }

    void SetSafeQuestion(string SafeQuestion)
    {
        _SafeQuestion = SafeQuestion;
    }

    __declspec(property(get = GetSafeQuestion, put = SetSafeQuestion)) string SafeQuestion;


    string GetAnswerOfSafeQuestion()
    {
        return _AnswerOfSafeQuestion;
    }

    void SetAnswerOfSafeQuestion(string AnswerOfSafeQuestion)
    {
        _AnswerOfSafeQuestion = AnswerOfSafeQuestion;
    }

    __declspec(property(get = GetAnswerOfSafeQuestion, put = SetAnswerOfSafeQuestion)) string AnswerOfSafeQuestion;

    short GetFailedLoginCount()
    {
        return _FailedLoginCount;
    }

    void SetFailedLoginCount(short FailedLoginCount)
    {
        _FailedLoginCount = FailedLoginCount;
    }
    __declspec(property(get = GetFailedLoginCount, put = SetFailedLoginCount)) short FailedLoginCount;

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Files/Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Files/Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector<clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0, 0, 0,"","");
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    void Deposit(double Amount)
    {
        _AccountBalance = Amount + _AccountBalance;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {  
            _AccountBalance -= Amount;
            Save();
        }
    }

    static float GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient& Client : vClients)
        {
            TotalBalances +=Client.AccountBalance;
        }
        return TotalBalances;
    }

    bool TransferByUser(float Amount, clsBankClient & DestinationClient, string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterUserTransferLog(Amount, DestinationClient, UserName);
        return true;

    }

    bool TransferByClient(float Amount, clsBankClient& DestinationClient)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterClientTransferLog(Amount, DestinationClient);
        return true;

    }

    static  vector <stUserTransferLogRecord> GetUserTransfersLogList()
    {
        vector <stUserTransferLogRecord> vUserTransferLogRecord;

        fstream MyFile;
        MyFile.open("Files/UserTransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stUserTransferLogRecord UserTransferLogRecord;

            while (getline(MyFile, Line))
            {

                UserTransferLogRecord = _ConvertUserTransferLogLineToRecord(Line);

                vUserTransferLogRecord.push_back(UserTransferLogRecord);

            }

            MyFile.close();

        }

        return vUserTransferLogRecord;

    }

    static  vector <stClientTransferLogRecord> GetClientTransfersLogList()
    {
        vector <stClientTransferLogRecord> vClientTransferLogRecord;

        fstream MyFile;
        MyFile.open("Files/ClientTransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stClientTransferLogRecord ClientTransferLogRecord;

            while (getline(MyFile, Line))
            {

                ClientTransferLogRecord = _ConvertClientTransferLogLineToRecord(Line);

                vClientTransferLogRecord.push_back(ClientTransferLogRecord);

            }

            MyFile.close();

        }

        return vClientTransferLogRecord;

    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::pAll)
        {
            return true;
        }

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;
    }

    void ClientRegisterLogIn()
    {

        string stDataLine = _PrepareClientLogInRecord();

        fstream MyFile;
        MyFile.open("Files/ClientLoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static  vector <stClientLoginRegisterRecord> ClientGetLoginRegisterList()
    {
        vector <stClientLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("Files/ClientLoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stClientLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertClientLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);

            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }

    static vector<string> Questions()
    {
        vector<string> vQuestion;

        string Q1 = "What is your favorite Color ?";
        vQuestion.push_back(Q1);
        string Q2 = "What is your first School name?";
        vQuestion.push_back(Q2);
        string Q3 = "What is your favorite teacher name?";
        vQuestion.push_back(Q3);
        string Q4 = "What is your favorite country ?";
        vQuestion.push_back(Q4);
        string Q5 = "What was your first car ?";
        vQuestion.push_back(Q5);
        return vQuestion;

    }
};


