#pragma once
#include <iostream>
#include "GlobalVars.h"
#include <ctime>
#include <sstream>
#include "clsDate.h"
#include <string>
#include "clsUser.h"

using namespace std;

class clsScreen
{
    
    protected:

      
        static void _DrawScreenHeader(string Title, string SubTitle = "") {

            cout << "\t\t\t\t\t ______________________________________";
            cout << "\n\n \t\t\t\t\t " << Title;
            if (SubTitle != "")
            {
                cout << "\n\n\t\t\t\t\t " << SubTitle;
            }
            cout << "\n\t\t\t\t\t ______________________________________\n\n";


            cout << "\n\t\t\t\t\t  User : " << CurrentUser.UserName << "\n";
            cout << "\t\t\t\t\t  Date : " << clsDate::DateToString(clsDate()) << "\n\n";
        }


       static bool _CheckAccessRights(clsUser::enPermissions Permision) {
        
            if (!CurrentUser.CheckAccessPermission(Permision)) {
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                return false;
            }
            else {
                return true;
            }
        }

};

