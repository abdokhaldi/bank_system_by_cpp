#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUserSceen : protected clsScreen
{
private :
	enum enManageUserOptions {
        eListUsers=1,eAddNewUser=2,eDeleteUuser=3,
        eUpdateUser=4, eFindUser=5,eMainMenue=6
	};
    
    static void  _GoBackToManageUserMenue() {
        
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowManageUserScreenMenue();
   }

    static short _ReadManageMenueOptions() {
        cout << setw(37) << left << "" << "choose what do you want to do [1 to 6]? ";
        short Choice = (short)clsInputValidate::ReadShortNumberBetween(1, 6, " Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowUsersListScreen() {
        clsListUsersScreen::ShowUsersList();
    }
    static void _ShowAddNewUserScreen() {
       // cout << " Add New User screen will be here \n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteUsersScreen() {
       // cout << "Delete User screen will be here \n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen() {
        // cout << "Update User screen will be here \n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {
      //  cout << "Find User screen will be here \n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUserMenue(enManageUserOptions manageUserOption) {
        switch (manageUserOption) {
        case enManageUserOptions::eListUsers :
        {
             system("cls");
             _ShowUsersListScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUserOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUserOptions::eDeleteUuser:
        {
            system("cls");
            _ShowDeleteUsersScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUserOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUserOptions::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUserOptions::eMainMenue:
        {
            // will back to main menue  
        }
        }
    }

public:

	static void ShowManageUserScreenMenue() {

        if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }


        system("cls");

		_DrawScreenHeader("\tManage User Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage User Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List User .\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";       
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUserMenue((enManageUserOptions)_ReadManageMenueOptions());
	}
};

