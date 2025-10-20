
#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsDate.h"

using namespace std;

clsBankClient CurrentClient = clsBankClient::Find("", "");


    class clsClientScreen
    {
    protected:

        static void _DrawScreenHeader(string Title, string SubTitle = "")
        {

            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  " << Title;
            if (SubTitle != "")
            {
                cout << "\n\t\t\t\t\t  " << SubTitle;
            }
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            cout << "\t\t\t\t\tClient: " << CurrentClient.FullName() << "\n";
            cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";

        }

        static bool CheckClientAccessRights(clsBankClient::enPermissions Permission)
        {

            if (!CurrentClient.CheckAccessPermission(Permission))
            {
                /*
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                */
                return false;
            }
            else
            {
                return true;
            }

        }


    };

