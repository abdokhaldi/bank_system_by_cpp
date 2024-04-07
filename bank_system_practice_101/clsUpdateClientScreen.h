#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen : protected clsScreen
{
private :

    static void _PrintClient(clsBankClient Client) {
        cout << "\n Client Card : ";
        cout << "\n First Name      : " << Client.FirstName;
        cout << "\n Last Name       : " << Client.LastName;
        cout << "\n Full Name       : " << Client.FullName();
        cout << "\n Email           : " << Client.Email;
        cout << "\n Phone Number    : " << Client.PhoneNumber;
        cout << "\n Account Nnumber : " << Client.AccountNumber();
        cout << "\n Pin Code        : " << Client.PinCode;
        cout << "\n Account Balance : " << Client.AccountBalance;

    }

   static void _ReadClientInfo(clsBankClient& Client) {
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


public :

   static void ShowUpdateClientScreen() {

       if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClients))
       {
           return;// this will exit the function and it will not continue
       }
       clsScreen::_DrawScreenHeader("\t Update screen \n");

        string AccountNumber = " ";
        cout << " \nEnter AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExists(AccountNumber)) {
            cout << " \n Enter AccountNumber Again : \n ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();

        cout << "\n Update client info : \n";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = Client.Save();

        switch (SaveResult) {
        case clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\n Account Updated Succesfuly -) \n";
            Client.Print();
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\n Error account was not Saved becoaus it is Empty -( \n";
        }
        }

    }


};

