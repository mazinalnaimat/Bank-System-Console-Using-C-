#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include "clsBankClient.h"
#include "clsUtil.h"


using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    short _VacationNumber = 0;
    bool _MarkedForDelete = false;
    string _SafeQuestion;
    string _AnswerOfSafeQuestion;
    short _FailedLoginCount = 0;


    struct stUserLoginRegisterRecord;

    static stUserLoginRegisterRecord _ConvertUserLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stUserLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptionText(LoginRegisterDataLine[2],3);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
      
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptionText(vUserData[5], 3),
            stoi(vUserData[6]), stoi(vUserData[7]), stoi(vUserData[8]), vUserData[9], vUserData[10]);

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptionText(User.Password,3) + Seperator;
        UserRecord += to_string(User._VacationNumber) + Seperator;
        UserRecord += to_string(User.Permissions) + Seperator;
        UserRecord += to_string(User.FailedLoginCount) + Seperator;
        UserRecord += (User.SafeQuestion) + Seperator;
        UserRecord += (User.AnswerOfSafeQuestion)  ;

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Files/Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Files/Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Files/Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0, 0, 0, "","");
    }

     string _PrepareUserLogInRecord(string Seperator ="#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate());
        LoginRecord += " - " + clsDate::GetTimeOfThisMomentString();
        LoginRecord += Seperator;
        LoginRecord += UserName;
        LoginRecord += Seperator;
        LoginRecord += clsUtil::EncryptionText(Password, 3);
        LoginRecord += Seperator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;

    }


public:

    enum enPermissions {
        pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
        pShowUserLogInRegister = 128, pShowClientLogInRegister = 256, pUnlockClientAccount = 512,
        pChangeCurrency = 1024
    };

    struct stUserLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;

    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password, 
        short VacationNumber, int Permissions, short FailedLoginCount,
        string SafeQuestion,  string AnswerOfSafeQuestion) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
         _SafeQuestion = SafeQuestion;
         _AnswerOfSafeQuestion = AnswerOfSafeQuestion;
         _FailedLoginCount = FailedLoginCount;
        _VacationNumber = VacationNumber;
    }

    
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

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


    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Files/Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Files/Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

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
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
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

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0, 0, 0, "", "");
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
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

    void UserRegisterLogIn()
    {

        string stDataLine = _PrepareUserLogInRecord();

        fstream MyFile;
        MyFile.open("Files/UserLoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

     static  vector <stUserLoginRegisterRecord> GetUserLoginRegisterList()
    {
        vector <stUserLoginRegisterRecord> vUserLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("Files/UserLoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stUserLoginRegisterRecord UserLoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                UserLoginRegisterRecord = _ConvertUserLoginRegisterLineToRecord(Line);

                vUserLoginRegisterRecord.push_back(UserLoginRegisterRecord);

            }

            MyFile.close();

        }

        return vUserLoginRegisterRecord;

    }

     static vector<string> Questions()
     {
         vector<string> vQuestion;

         string Q1 = "What is your favorite Color ?";
         vQuestion.push_back(Q1);
         string Q2 = "What is your first School name ?";
         vQuestion.push_back(Q2);
         string Q3 = "What is your favorite teacher name ?";
         vQuestion.push_back(Q3);
         string Q4 = "What is your favorite country ? ";
         vQuestion.push_back(Q4);
         string Q5 = "What was your first car ? ";
         vQuestion.push_back(Q5);
         return vQuestion;

     }
};

