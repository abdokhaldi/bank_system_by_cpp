#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : clsScreen
{
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
		string AccountNumber = " ";
		cout << "Please Enter Account Number \n ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public :

	static void ShoWithdrawScreen() {
		clsScreen::_DrawScreenHeader("\t Withdraw Screen \n");
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::isClientExists(AccountNumber)) {
			cout << "\n AccountNumber with [" << AccountNumber << "] desn't exist , try again\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\n Please Enter Withdraw Amount : \n ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\n Are you sure you want to perform this transaction :  y or n ?\n ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Withdraw(Amount))
			{
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.AccountBalance;

			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}

		}  
};

