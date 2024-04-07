#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private:

    static void _PrintTransferRecord(clsBankClient::stTransferLogRecord TransferLogRecord) {

        cout << setw(4) << left << ""

            << "| " << setw(25) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(10) << left << TransferLogRecord.sAccNumber;
        cout << "| " << setw(10) << left << TransferLogRecord.dAccNumber;
        cout << "| " << setw(10) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.dBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.dBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.UserName;
    }

public:

    static void ShowTransferLogsScreen() {
        vector <clsBankClient::stTransferLogRecord>  vTransferLogRecords;
        vTransferLogRecords = clsBankClient::GetTransferLogsList();
        string Title = "\t Transfer Logs Screen ";
        string SubTitle = "\t (" + to_string(vTransferLogRecords.size()) + ") Record(s)";
        
        _DrawScreenHeader(Title, SubTitle);
        
        cout << setw(4) << left << "" << "\n _______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(4) << left << ""
            << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(4) << left << "" << "\n _______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecords.size() == 0) {
            cout << "\t\t\t\t No Records Available . \n";
        }
        else {
            for (clsBankClient::stTransferLogRecord T : vTransferLogRecords) {
                _PrintTransferRecord(T);
                cout << endl;
            }
        }
        cout << setw(4) << left << "" << "\n _______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

