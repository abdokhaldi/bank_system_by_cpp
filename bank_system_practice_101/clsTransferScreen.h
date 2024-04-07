#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "GlobalVars.h"
class clsTransferScreen : public clsScreen 
{
private :

	static void _PrintClientCard(clsBankClient Client) {
        cout << "\n\n Client Card : \n";
        cout << " ____________________________ \n";
		
		cout << "\nfull name       : " << Client.fullName();
		cout << "\naccount number  : " << Client.AccountNumber();
		cout << "\naccount balance : " << Client.AccountBalance;
        cout << "\n ____________________________ \n\n";
	 }

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::isClientExists(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient)
	{
		float Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}


public :

	static void ShowTransferScreen() {
		_DrawScreenHeader("\t Transfer Sceen ");
	clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
	_PrintClientCard(SourceClient);
	
	clsBankClient DistinationClient = clsBankClient::Find(_ReadAccountNumber());
	_PrintClientCard(DistinationClient);

	float Amount = ReadAmount(SourceClient);
	
	cout << "\n Are you sure you want to transfer ? y/n : ";
	char Answer = 'n';
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		if (SourceClient.Transfer(Amount, DistinationClient)) {
			cout << "\n Transfer Done Successfuly . \n";
		}
		else {
			cout << "\nTransfer Faild \n";
		}

	}
	else {
		cout << "\n Transfer operation was canceled . \n";
		return;
	}
	

	_PrintClientCard(SourceClient);
	_PrintClientCard(DistinationClient);
	}

};

