#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"


class clsDiposetScreen : protected clsScreen
{

private:
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

	static string _ReadAccountNumber() {
		cout << "\n please enter accountNuber \n";
		return clsInputValidate::ReadString();
	}

public :

	static void ShowDipositScreen() {

		clsScreen::_DrawScreenHeader("\t Diposit Screen \n");

		string AccountNumber = "";
		
		AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::isClientExists(AccountNumber)) {
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

       double Amount = 0;
	   cout << "\nPlease enter deposit amount? ";
	   Amount = clsInputValidate::ReadDblNumber();

	   cout << "\nAre you sure you want to perform this transaction? ";
		
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Client.Diposet(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}
		
	}

};

