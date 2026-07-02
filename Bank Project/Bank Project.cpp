// Bank Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
const string FileName = "Clients.txt";
enum enSystemOperations{show = 1 , add = 2 , Delete = 3 , update = 4 , find = 5 , Transactions = 6 , ExitSystem = 7};
enum enTransactionOPerations{Deposit = 1 , Withdraw = 2 , TotalBlalance = 3 , MainMenu = 4};
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

void PrintMainScreen() {
    cout << "======================================================\n";
    cout << "                   Main menu screen                   \n";
    cout << "======================================================\n";
    cout << "                  [1] show client list.               \n";
    cout << "                  [2] add new client.                 \n";
    cout << "                  [3] delete client.                  \n";
    cout << "                  [4] update client                   \n";
    cout << "                  [5] find client                     \n";
    cout << "                  [6] Transactions                            \n";
    cout << "                  [7] exit                            \n";
    cout << "======================================================\n";
}

string ConvertRecordToLine(sClient Client, string Delim = "#//#")

{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Delim;
    stClientRecord += Client.PinCode + Delim;
    stClientRecord += Client.Name + Delim;
    stClientRecord += Client.Phone + Delim;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<string> SplitString(string S1, string Delim = "#//#")
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}

sClient ConvertLineToRecord(string Line, string Delim = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Delim);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to  double

    return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

    cout << "\n_______________________________________________________";

    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";

    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";

    cout << "_________________________________________\n" << endl;
}

void ShowClientsListOperation() {
    vector<sClient> vClients = LoadClientsDataFromFile(FileName);
    PrintAllClientsData(vClients);
    cout << "press any key to go back to main menu....";
    system("pause");
}

string ReadClientAccountNumber()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    getline(cin , AccountNumber);
    return AccountNumber;
}

bool FindClientByAccountNumber(string AccountNumber, sClient& Client)
{
    vector <sClient> vClients = LoadClientsDataFromFile(FileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool Exist ;
    do {
        
        
        getline(cin, Client.AccountNumber);
        Exist = FindClientByAccountNumber(Client.AccountNumber, Client);
        if (Exist) {
            cout << "client with[" << Client.AccountNumber << "] is already exist, enter another one.";
        }
    } while (Exist);
   
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(FileName, ConvertRecordToLine(Client));
       
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {
        
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";

        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void PrintAddClientScreen() {
    cout << "\n-----------------------------\n";
    cout << "        Add new clients screen     ";
    cout << "\n-----------------------------\n";
}

void AddClientOperation() {
    PrintAddClientScreen();
    AddClients();
    cout << "press any key to go back to main menu....";
    system("pause");
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)

{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)

{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)

{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, Client))

    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
       cin>>Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

            SaveCleintsDataToFile(FileName, vClients);
            //Refresh Clients
            vClients = LoadClientsDataFromFile(FileName);
            cout << "\n\nClient Deleted Successfully.";
            
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
        return false;
    }
}

void DeleteClientScreen() {
    
    cout << "\n------------------------------------------\n";
    cout << "                delete client screen";
    cout << "\n------------------------------------------\n";
}

void DeleteOperation() {
    DeleteClientScreen();
    string accountNumber = ReadClientAccountNumber();
    vector<sClient>vClients = LoadClientsDataFromFile(FileName);
    DeleteClientByAccountNumber(accountNumber, vClients);
    cout << "press any key to go back to main menu....";
    system("pause");
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n? ";
            cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(FileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

void UpdateClientScreen() {
    cout << "\n------------------------------------------\n";
    cout << "                Update client screen";
    cout << "\n------------------------------------------\n";
}

void UpdateOperation() {
    UpdateClientScreen();
    vector<sClient>vClients = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
        cout << "press any key to go back to main menu....";
    system("pause");
}

void PrintFindClientScreen() {
    cout << "\n------------------------------------------\n";
    cout << "                find client screen";
    cout << "\n------------------------------------------\n";
}

void FindClientOperation() {

    PrintFindClientScreen();
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber , Client)) {
        PrintClientCard(Client);
        cout << "press any key to go back to main menu....";
        system("pause");
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        cout << "press any key to go back to main menu....";
        system("pause");
    }
}

void PrintTransactionMenuScreen() {
    cout << "======================================================\n";
    cout << "                   Main menu screen                   \n";
    cout << "======================================================\n";
    cout << "                  [1] Deposit.               \n";
    cout << "                  [2] Withdraw.                 \n";
    cout << "                  [3] TotalBalances.                  \n";
    cout << "                  [4] Main Menu                   \n";
    cout << "======================================================\n";
}

void PrintDepositScreen() {

    cout << "\n------------------------------------------\n";
    cout << "                Deposit screen";
    cout << "\n------------------------------------------\n";
}

bool DepositFromAccount(string AccountNumber , vector<sClient>& vClient) {
    char Answer = 'n';
   
    double DepositAmount = 0;
    cout << "\nplease enter deposit amount? ";
    cin >> DepositAmount;
    cout << "\n\nAre you sure you want to perform this operation? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for(sClient& C : vClient)
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance += DepositAmount;
                SaveCleintsDataToFile(FileName, vClient);
                cout << "\n\nDone Successfully. New balance is: "<< C.AccountBalance;
                return true;
        }
       
    }
    return false;
}
  
void DepositOperation()
{
    PrintDepositScreen();
    sClient Client;
   
        string AccountNumber = ReadClientAccountNumber();
        vector<sClient> vClient = LoadClientsDataFromFile(FileName);
        while (!FindClientByAccountNumber(AccountNumber, Client)) {
            cout << "client with [" << AccountNumber << " ] does not exist.\n";
            AccountNumber = ReadClientAccountNumber();
        }
        PrintClientCard(Client);
        DepositFromAccount( AccountNumber , vClient);
        
    
}

void WithDrawScreen() {

    cout << "\n------------------------------------------\n";
    cout << "                Withdraw screen";
    cout << "\n------------------------------------------\n";
}

bool WithdarwFromAccount(string AccountNumber, vector<sClient>& vClient) {
    char Answer = 'n';

    double WithdrawAmount = 0;
    cout << "\nplease enter withdraw amount? ";
    cin >> WithdrawAmount;
   
    
    {
        for (sClient& C : vClient)
            if (C.AccountNumber == AccountNumber) {
                while (WithdrawAmount > C.AccountBalance) {
                    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
                        cout << "Please enter another amount? ";
                    cin >> WithdrawAmount;
                }
                cout << "\n\nAre you sure you want to perform this operation? y/n? ";
                cin >> Answer;
                if (Answer == 'y' || Answer == 'Y') {
                    C.AccountBalance += (-1*WithdrawAmount);
                    SaveCleintsDataToFile(FileName, vClient);
                    cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                    return true;
                }
               
            }

    }
    return false;
}

void WithdrawOperation()
{
    WithDrawScreen();
    sClient Client;

    string AccountNumber = ReadClientAccountNumber();
    vector<sClient> vClient = LoadClientsDataFromFile(FileName);
    while (!FindClientByAccountNumber(AccountNumber, Client)) {
        cout << "client with [" << AccountNumber << " ] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    WithdarwFromAccount(AccountNumber, vClient);


}

void PrintClientRecordBalanceLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
    vector <sClient> vClients = LoadClientsDataFromFile(FileName);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (sClient Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void TotalBalancesOperation() {
    ShowTotalBalances();
    cout << "\npress any key to go back to main menu....";
    system("pause");
}

void PrintExitScreen() {
    cout << "\n------------------------------------------\n";
    cout << "                Program Ends :-)";
    cout << "\n------------------------------------------\n";
}

short ChooseOperation() {
    int Operation;
    do {
        cout << "Choose what do you want to do? [ 1 - 7 ]";
        cin >> Operation;
    } while (Operation > 7 || Operation <= 0);

    return Operation;
}

short ChooseTransactionOperation() {
    int Operation;
    do {
        cout << "Choose what do you want to do? [ 1 - 4 ]";
        cin >> Operation;
    } while (Operation > 4 || Operation <= 0);

    return Operation;
}

void StartTransactionOperation(enTransactionOPerations TransactionOperation) {

    switch (TransactionOperation) {
    case enTransactionOPerations::Deposit:
        system("cls");
        DepositOperation();
        system("cls");
        PrintTransactionMenuScreen();
        StartTransactionOperation((enTransactionOPerations)ChooseTransactionOperation());
        break;
    case enTransactionOPerations::Withdraw:
        system("cls");
        WithdrawOperation();
        system("cls");
        PrintTransactionMenuScreen();
        StartTransactionOperation((enTransactionOPerations)ChooseTransactionOperation());
        break;
    case enTransactionOPerations::TotalBlalance:
        system("cls");
        TotalBalancesOperation();
        system("cls");
        PrintTransactionMenuScreen();
        StartTransactionOperation((enTransactionOPerations)ChooseTransactionOperation());
        break;
    case enTransactionOPerations::MainMenu:
        system("cls");
        
        
    }
}

void StartOperation(enSystemOperations OperationChosin) {
    
    switch (OperationChosin) {
    case enSystemOperations::show:
        system("cls");
        ShowClientsListOperation();
        break;
    case enSystemOperations::add:
        system("cls");
        AddClientOperation();
        break;
    case enSystemOperations::Delete:
        system("cls");
        DeleteOperation();
        break;
    case enSystemOperations::update:
        system("cls");
        UpdateOperation();
        break;
    case enSystemOperations::find:
        system("cls");
        FindClientOperation();
        break;
    case enSystemOperations::Transactions:
        system("cls");
        PrintTransactionMenuScreen();
        StartTransactionOperation((enTransactionOPerations)ChooseTransactionOperation());
        break;

    case enSystemOperations::ExitSystem:
        system("cls");
        PrintExitScreen();
        break;
       
    }
}

void Start() {
    enSystemOperations Operation;
    do {
        PrintMainScreen();
         Operation = (enSystemOperations)ChooseOperation();
        StartOperation(Operation);
        if (Operation != enSystemOperations::ExitSystem) {
            system("cls");
        }
       
    } while (Operation!=enSystemOperations::ExitSystem);
    

}

int main()
{
    Start();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
