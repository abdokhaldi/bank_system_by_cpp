#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
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

   public :

	   static void ShowFindClientScreen() {

		   if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
		   {
			   return;// this will exit the function and it will not continue
		   }


		   clsScreen::_DrawScreenHeader("\t Find Cient Screen ");

		   string AccountNumber = "";
		   cout << "enter accountNumber ";
			   AccountNumber = clsInputValidate::ReadString();
			   while (!clsBankClient::isClientExists(AccountNumber)) {
				   cout << "the Client was not found , please enter another one .";
				   AccountNumber = clsInputValidate::ReadString();
			   }

			   clsBankClient Client = clsBankClient::Find(AccountNumber);

			   if (!Client.isEmpty()) {
				   cout << "\n Client Found -)";
			   }
			   else {
				   cout << "\n Client was not found -(";
			   }

			   _PrintClient(Client);
	   }

};

