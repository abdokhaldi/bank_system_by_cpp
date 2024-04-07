
#pragma once

 #include <iostream>
 #include "clsPerson.h"
 #include <string>
 #include "clsString.h"
 #include <vector>
 #include <fstream>


using namespace std;



class clsBankClient : public clsPerson
    
{
private:

    struct stTransferLogRecord;

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNew=2 };

    enMode _Mode;
    string _accountNumber;
    string _pinCode;
    double _accountBalance;
    bool   _MarkForDelete = false;

    
     static stTransferLogRecord _ConvertTransferedLineToRecord(string Line , string sep="#//#") {
        vector <string> vTransferLogs;
        vTransferLogs = clsString::Split(Line, sep);
        stTransferLogRecord TransferLogData;
        TransferLogData.DateTime = vTransferLogs[0];
        TransferLogData.sAccNumber = vTransferLogs[1];
        TransferLogData.dAccNumber = vTransferLogs[2];
        TransferLogData.Amount = stof(vTransferLogs[3]);
        TransferLogData.sBbalance = stof(vTransferLogs[4]);
        TransferLogData.dBalance = stof(vTransferLogs[5]);
        TransferLogData.UserName = vTransferLogs[6];

        return TransferLogData;
    }

    

    string _PrepareTransfersRecord(clsBankClient distinationClient,
        double Amount, string UserName,string Seperator = "#//#"
        )
    {
        
        string TransferRecord = "";
        TransferRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferRecord += AccountNumber() + Seperator;
        TransferRecord += distinationClient._accountNumber + Seperator;
        TransferRecord += to_string(Amount) + Seperator;
        TransferRecord += to_string(AccountBalance) + Seperator;
        TransferRecord += to_string(distinationClient.AccountBalance) + Seperator;
        TransferRecord += UserName ;
        return TransferRecord;
    }


    static clsBankClient _convertLineToRecord(string Line, string sep = "#//#") {
        vector <string>  vClientData;
        vClientData = clsString::Split(Line, sep);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _convertRecordToLine(clsBankClient Client, string sep = "#//#") {
        string Line = "";
        Line += Client.FirstName + sep;
        Line += Client.LastName + sep;
        Line += Client.Email + sep;
        Line += Client.PhoneNumber + sep;
        Line += Client._accountNumber + sep;
        Line += Client.PinCode + sep;
        Line += to_string(Client.AccountBalance);

        return Line;
    }

    

    static clsBankClient _getEmptyClientObj() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _SaveClientsData(vector <clsBankClient> vClients) {
        fstream MyFile;
        MyFile.open("clients.txt", ios::out);

        if (MyFile.is_open()) {
            for (clsBankClient C : vClients) {

                if(C._MarkForDelete == false ){

                string DataLine = _convertRecordToLine(C);
                MyFile << DataLine << endl;
                
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        vector<clsBankClient> vClients;
        vClients = _LoadDataFromFile();

        for (clsBankClient& C : vClients) {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
            }
        }
        _SaveClientsData(vClients);
    };

    static vector <clsBankClient> _LoadDataFromFile() {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("clients.txt", ios::in);// read mode

        if (MyFile.is_open()) {

            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = clsBankClient::_convertLineToRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

  bool _isEmpty() {
        return  (_Mode == enMode::EmptyMode);
    }

  void _AddNew()
  {

      _AddDataLineToFile(_convertRecordToLine(*this));
  }

  void _AddDataLineToFile(string  stDataLine)
  {
      fstream MyFile;
      MyFile.open("Clients.txt", ios::out | ios::app);

      if (MyFile.is_open())
      {

          MyFile << stDataLine << endl;

          MyFile.close();
      }

  }

public:

   
    struct stTransferLogRecord {
        string DateTime;
        string sAccNumber;
        string dAccNumber;
        float  Amount;
        float  sBbalance;
        float  dBalance;
        string UserName;
    };
  

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber,
        string AccountNumber, string PinCode, double AccountBalance) :
        clsPerson(FirstName, LastName, Email, PhoneNumber) {
        _Mode = Mode;
        _accountNumber = AccountNumber;
        _pinCode = PinCode;
        _accountBalance = AccountBalance;
    }


    string AccountNumber()
    {
        return _accountNumber;
    }
    

    void setPinCode(string pinCode) {
        _pinCode = pinCode;
    }
    string getPinCode() {
        return _pinCode;
    }
    __declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

    void setAccountBalance(double accountBalance)
    {
        _accountBalance = accountBalance;
    }
    double getAccountBalance() {
        return _accountBalance;
    }
    __declspec(property(get = getAccountBalance, put = setAccountBalance)) double AccountBalance;

    string FullName() {
        return FirstName + " " + LastName;
    }

    void Print() {
        cout << "\n First name     : " << FirstName;
        cout << "\n Last Name      : " << LastName;
        cout << "\n fullName       : " << FullName();
        cout << "\n Email          : " << Email;
        cout << "\n Phone Number   : " << PhoneNumber;
        cout << "\n Account Number : " << AccountNumber();
        cout << "\n Pin Code       : " << PinCode;
        cout << "\n Account Balance: " << AccountBalance;
        
    }

    

     static clsBankClient Find(string AccountNumber) {

        fstream MyFile;
        MyFile.open("clients.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = clsBankClient::_convertLineToRecord(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _getEmptyClientObj();
    }

     void  Diposet(double Amount) {
         _accountBalance += Amount;
         Save();
   }

     bool Withdraw(double Amount) {
         if (Amount > _accountBalance) {
             return false;
         }
         else {
             _accountBalance -= Amount;
             Save();
             return true;
            
         }
         
     }

     enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists=2 };

     enSaveResult Save() {
         switch (_Mode) {
         case enMode::EmptyMode:
         {
             if(_isEmpty()){
             return enSaveResult::svFaildEmptyObject;
            }
         }
         case enSaveResult::svSucceeded:
         {
             _Update();
             return enSaveResult::svSucceeded;
             break;
         }
         case enMode::AddNew :
         {
             //This will add new record to file or database
             if (clsBankClient::isClientExists(_accountNumber)) {
                 return enSaveResult::svFaildAccountNumberExists;
             }
             else {
                 _AddNew();
                 //We need to set the mode to update after add new
                 _Mode = enMode::UpdateMode;
                 enSaveResult::svSucceeded;
                 break;
             }
         }
   
      }
   }


     static clsBankClient GetAddNewClientObject(string AccountNumber)
     {
         return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
     }


     static bool isClientExists(string AccountNumber) {
         clsBankClient Client = clsBankClient::Find(AccountNumber);
         return (!Client._isEmpty());
     }

     bool Delete () {
         vector <clsBankClient> vClients;
         vClients = _LoadDataFromFile();

         for (clsBankClient& C : vClients) {
             if (AccountNumber() == _accountNumber) {
                 C._MarkForDelete = true;
                 break;
             }
         }

         _SaveClientsData(vClients);
         *this = _getEmptyClientObj();

         return true;
     }

     static vector<clsBankClient> GetClientsList() {
         return _LoadDataFromFile();
         
     }
     
     

     static float GetTotalBalances()
     {
         vector <clsBankClient> vClients = clsBankClient::GetClientsList();

         double TotalBalances = 0;

         for (clsBankClient Client : vClients)
         {

             TotalBalances += Client.AccountBalance;
         }

         return TotalBalances;

     }

     bool isEmpty() {
         return _isEmpty();
     }

     bool Transfer(double Amount, clsBankClient& DistinationClient) {

         if (Amount > AccountBalance) {
             return false;
         }

         Withdraw(Amount);
         DistinationClient.Diposet(Amount);
         RegisterTransfers(DistinationClient, Amount, CurrentUser.UserName);
         
         return true;
     }

     void RegisterTransfers (clsBankClient distinationClient, double Amount, string UserName
         ) {
         fstream MyFile;
         string DataLine = _PrepareTransfersRecord(distinationClient,
             Amount, UserName);
         MyFile.open("Transfers.txt", ios::out | ios::app);
         if(MyFile.is_open()){
             MyFile << DataLine << endl;
             MyFile.close();
         }
     }

     
   static  vector<stTransferLogRecord> GetTransferLogsList() {
      
           vector <stTransferLogRecord> vLogsDataTransferd;
           fstream MyFile;
           MyFile.open("Transfers.txt", ios::in);
           if (MyFile.is_open()) {
               string Line;
               while (getline(MyFile, Line)) {
                   stTransferLogRecord TransferLogs = _ConvertTransferedLineToRecord(Line);
                   vLogsDataTransferd.push_back(TransferLogs);
               }
               MyFile.close();
           }
           return vLogsDataTransferd;
       
     }



};