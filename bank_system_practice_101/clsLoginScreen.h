#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainMenuScreen.h"
#include "GlobalVars.h"


class clsLoginScreen : protected clsScreen
{

private:

    


    static  bool _Login()
    {

        bool LoginFaild = false;
        short MaxTrails = 3;
        string Username, Password;
       
        do
        {
          if (LoginFaild)
            {
                MaxTrails--;
                cout << "\nInvlaid Username/Password!\n";
                cout << "\nYou have " << MaxTrails << "  trails to login \n\n";
            }
            
            if (MaxTrails == 0) {
                cout << "You are Locked after 3 trails ! ";
                return false;
            }
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();
           
            
         } while (LoginFaild );
         
         CurrentUser.RegisterLogIn();
        clsMainMenuScreen::ShowMainMenue();

        return true ;
       
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

