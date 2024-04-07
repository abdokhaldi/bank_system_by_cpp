#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h";
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserSceen.h"
#include "clsLoginRegisterScreen.h"

//#include "GlobalVars.h"

using namespace std;

class clsMainMenuScreen : protected clsScreen 
{
private :
   
    enum enMainMenueOptions {
        eListClients=1, eAddNewClient=2,eDeleteClient=3,
        eUpdateClient=4,eFindClient=5,eShowTransactionsMenu=6,
        eManageUsers=7, eLoginRegister = 8, eExit=9
     };

    
    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "choose what do you want to do [1 to 9]? ";
        short Choice = (short)clsInputValidate::ReadShortNumberBetween(1,9, " Enter Number between 1 to 8? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }



    static void _ShowAllClientsScreen()
    {
       
        clsClientListScreen::ShowClientsList();
    }

static void _ShowAddNewClientsScreen()
{
    //cout << "\nAdd New Client Screen Will be here...\n";
    
    clsAddNewClientScreen::ShowAddNewClientScreen();
}
static void _ShowDeleteClientScreen()
{
    clsDeleteClientScreen::ShowDeleteClientScreen();

}
static void _ShowUpdateClientScreen()
{
    clsUpdateClientScreen::ShowUpdateClientScreen();

}

static void _ShowFindClientScreen()
{
    clsFindClientScreen::ShowFindClientScreen();

}

  static void _ShowTransactionsMenue()
{
    clsTransactionsScreen::ShowTransactionsMenue();

}

 static void _ShowManageUsersMenue()
{
     clsManageUserSceen::ShowManageUserScreenMenue();

}

 static void _ShowLoginRegisterScreen(){
     
     clsLoginRegisterScreen::ShowLoginRegisterScreen();
     
 }

static void _Logout()
{
    CurrentUser.Find("", "");
   
}





static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
    
    switch (MainMenueOption) {

    case enMainMenueOptions::eListClients:
    {
        system("cls");
        _ShowAllClientsScreen();
        _GoBackToMainMenue();
    }
    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");
        _ShowAddNewClientsScreen();
        _GoBackToMainMenue();
    }
    case enMainMenueOptions::eDeleteClient:
    {
        system("cls");
        _ShowDeleteClientScreen();
        _GoBackToMainMenue();
    }
    case enMainMenueOptions::eUpdateClient:
    {
        system("cls");
        _ShowUpdateClientScreen();
        _GoBackToMainMenue();
    }
    case enMainMenueOptions::eFindClient:
    {
        system("cls");
        _ShowFindClientScreen();
        _GoBackToMainMenue();
    }
    case enMainMenueOptions::eShowTransactionsMenu:
    {
        system("cls");
        _ShowTransactionsMenue();
        _GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eManageUsers:
    {
        system("cls");
        _ShowManageUsersMenue();
        _GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eLoginRegister :
    {
        system("cls");
        _ShowLoginRegisterScreen();
        _GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eExit:
    {
        system("cls");
        
         _Logout();
        break;

    }
    }

}


public : 

static void ShowMainMenue()
{


    system("cls");
    
    _DrawScreenHeader("\t\tMain Screen");

    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
    cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
    cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
    cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
    cout << setw(37) << left << "" << "\t[5] Find Client.\n";
    cout << setw(37) << left << "" << "\t[6] Transactions.\n";
    cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
    cout << setw(37) << left << "" << "\t[8] login register.\n";
    cout << setw(37) << left << "" << "\t[9] Logout.\n";
    cout << setw(37) << left << "" << "===========================================\n";

    _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
}

};
