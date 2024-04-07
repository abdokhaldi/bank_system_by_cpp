#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsAddNewClientScreen : protected clsScreen
{
private :

   static  void _ReadClientInfo(clsBankClient& Client) {
        cout << "\n Enter FirstName : ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\n Enter LastName : ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\n Enter Email : ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\n Enter PhoneNumber : ";
        Client.PhoneNumber = clsInputValidate::ReadString();
        cout << "\n Enter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\n Enter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.PhoneNumber;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public : 


    static void ShowAddNewClientScreen()
    {

        if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }


        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::isClientExists(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


         _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
         }
        case clsBankClient::enSaveResult::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }

};

