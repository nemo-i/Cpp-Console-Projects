
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
void PrintMainMenu();
std::string AddSpace(short count) {
    std::string space;
    for (size_t i = 0; i < count; i++)
    {
        space += " ";
    }
    return space;
}
void PrintMainMenuHeader() {
    std::cout << "=================================" << std::endl;
    std::cout << AddSpace(9) << "Main Menu Screen" << AddSpace(9) << std::endl;
    std::cout << "=================================" << std::endl;
}

void PrintMainMenuOption(short index, std::string title)
{
    std::cout << AddSpace(5) << "[" << index + 1 << "] " << title << "." << std::endl;
}



short ReadOption() {
    std::cout << "Choose what do you want to do? [1 to 6]?";
    short option;
    std::cin >> option;
    return option;
}
void Clear() {
    system("cls");
}

enum  enOptions
{
    Show = 1,
    Add = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Exit = 6,
};


struct sClient
{
    std::string accountNumber;
    std::string pinCode;
    std::string name;
    std::string phone;
    double balance;
    bool markForDelete = false;
    bool markForUpdate = false;
};
std::string DrawLine(short count)
{
    std::string line;
    for (size_t i = 0; i < count; i++)
    {
        line += "-";
    }
    return line;
}

void DrawClientRow(sClient& client)
{
    std::cout << "|" << std::setw(15) << client.accountNumber << "|" << std::setw(15) << client.pinCode << "|" << std::setw(28) << client.name << "|" << std::setw(15) << client.phone << "|" << std::setw(15) << client.balance << "|" << std::endl;
}
std::string ConvertClientToRecord(sClient& client, std::string sepatrator = "#//#")
{
    return client.accountNumber + sepatrator + client.pinCode + sepatrator + client.name + sepatrator + client.phone + sepatrator + to_string(client.balance);
}

void SaveRecordToFile(std::string record, std::string fileName = "Clients.txt")
{
    std::fstream file;
    file.open(fileName, ios::out | ios::app);
    while (file.is_open())
    {
        file << record + "\n";
        file.close();
    }
}
void DrawClientListHeader(short clients)
{

    std::cout << DrawLine(100) << std::endl;
    std::cout << AddSpace(30) << "Client List (" << clients << ") Client(s)." << AddSpace(10) << std::endl;
    std::cout << DrawLine(100) << std::endl;
    std::cout << "|" << std::setw(15) << "Account Number" << "|" << std::setw(15) << "Pin Code" << "|" << std::setw(28) << "Client Name" << "|" << std::setw(15) << "Phone" << "|" << std::setw(15) << "Balance" << "|" << std::endl;
    std::cout << DrawLine(100) << std::endl;

}
std::vector<std::string> SplitRecord(std::string record, std::string separator)
{
    std::vector<std::string> values;
    bool showSeparator = false;
    std::string recordv;
    short pos;
    do
    {
        pos = record.find(separator);
        recordv = record.substr(0, pos);
        values.push_back(recordv);
        record.erase(0, pos + separator.length());
    } while (pos != -1);



    return values;
}

sClient ConvertRecordToClient(std::string record, std::string separator)
{
    sClient client;
    std::vector<std::string> values = SplitRecord(record, separator);
    client.accountNumber = values[0];
    client.pinCode = values[1];
    client.name = values[2];
    client.phone = values[3];
    client.balance = stod(values[4]);

    return client;
}

std::vector<sClient> ReadClientsFromFile(std::string fileName = "Clients.txt")
{
    std::fstream file;
    std::string record;
    std::vector<sClient> clients;
    sClient client;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        while (getline(file, record))
        {
            client = ConvertRecordToClient(record, "#//#");
            clients.push_back(client);
        }
        file.close();
    }
    return clients;
}

void ShowClientList(std::vector<sClient> clients) {

    Clear();
    DrawClientListHeader(clients.size());
    for (auto& i : clients)
    {
        DrawClientRow(i);
    }
    std::cout << DrawLine(100) << std::endl;
    std::cout << "Press any key to go to main menu..." << std::endl;
    system("pause");
    PrintMainMenu();
}

void DrawAddNewClientHeader() {
    std::cout << DrawLine(50) << std::endl;
    std::cout << AddSpace(15) << "Add New Client Screen" << AddSpace(15) << std::endl;
    std::cout << DrawLine(50) << std::endl;
}

sClient ReadClientFromUser(std::vector<sClient> clients) {
    sClient client;
    bool addMore;
    std::cout << "Enter Account Number? ";
    getline(cin >> ws, client.accountNumber);
    for (sClient& i : clients)
    {
        if (i.accountNumber == client.accountNumber) {
            std::cout << "Client with [" << i.accountNumber << "] " << "already exits, ";
            std::cout << "Enter Another Account Number? ";
            getline(cin >> ws, client.accountNumber);
            break;
        }
    }
    std::cout << "Enter PinCode? ";
    getline(cin, client.pinCode);
    std::cout << "Enter Client Name? ";
    getline(cin, client.name);
    std::cout << "Enter Client Phone? ";
    getline(cin, client.phone);
    std::cout << "Enter Client Balance?";
    cin >> client.balance;
    return client;
}
void DrawAddNewClientScreen(std::vector<sClient>& clients) {
    sClient client;
    std::string record;
    std::string addMore;
    Clear();
    DrawAddNewClientHeader();
    std::cout << "Adding New Client:" << std::endl;
    do
    {
        client = ReadClientFromUser(clients);
        record = ConvertClientToRecord(client);
        SaveRecordToFile(record);
        clients.push_back(client);
        std::cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
        cin >> addMore;
    } while (addMore == "y");
    std::cout << "Press any key to go to main menu..." << std::endl;
    system("pause>nul");
    PrintMainMenu();

}

void DrawDeleteClientHeader() {
    std::cout << DrawLine(50) << std::endl;
    std::cout << AddSpace(15) << "Delete Client Screen" << AddSpace(15) << std::endl;
    std::cout << DrawLine(50) << std::endl;
}

bool IsClientExits(std::string accountNumber, std::vector<sClient> clients, sClient& client, bool markForDelete = false,bool markForUpdate)
{
    for (auto& i : clients)
    {
        if (accountNumber == i.accountNumber) {
            if (markForDelete) {
                i.markForDelete = true;
                
            }
            if (markForUpdate) {
                i.markForUpdate = true;
            }
           
            client = i;
            return true;
        }

    }
    return false;
}
void DrawClientInfoCard(sClient& client) {
    std::cout << "The following are the client details:" << std::endl;
    std::cout << DrawLine(35) << std::endl;
    std::cout << "Account Number:" << client.accountNumber << std::endl;
    std::cout << "Pin Code      :" << client.pinCode << std::endl;
    std::cout << "Name          :" << client.name << std::endl;
    std::cout << "Phone         :" << client.phone << std::endl;
    std::cout << "Balance       :" << client.balance << std::endl;
    std::cout << DrawLine(35) << std::endl;
};

int IndexOfClientInDatabase(std::vector<sClient>& clients, sClient client)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i].accountNumber == client.accountNumber) {
            return i;
        }
        else
        {
            return -1;
        }
    }
}
void AddClientAfterClearDatabase(std::vector<sClient>& clients, std::string fileName = "Clients.txt")
{
    std::string record;
    fstream file;
    file.open(fileName, ios::out);
    while (file.is_open())
    {



        for (auto& i : clients)
        {
            if (!i.markForDelete) {
                record = ConvertClientToRecord(i);
                file << record;
            }
        }
        file.close();
    }
}

void AddClientsToDatabase(std::vector<sClient>& clients, std::string fileName = "Clients.txt")
{
    std::string record;
    fstream file;
    file.open(fileName, ios::out || ios::app);
    while (file.is_open())
    {



        for (auto& i : clients)
        {
            if (!i.markForDelete) {
                record = ConvertClientToRecord(i);
                file << record;
            }
        }
        file.close();
    }

}
void DeleteClientFromDatabase(std::vector<sClient>& clients, sClient client)
{

    AddClientAfterClearDatabase(clients);
}


void DrawClientDeleteScreen(std::vector<sClient>& clients) {
    Clear();
    std::string accountNumber;
    sClient client;
    char deleteClient;
    DrawDeleteClientHeader();
    std::cout << "Please enter Account Number? ";
    cin >> accountNumber;
    bool isClientExits = IsClientExits(accountNumber, clients, client, true,false);
    if (!isClientExits) {
        std::cout << "Client with Account Number (" << accountNumber << ") is Not Found!" << std::endl;
        std::cout << "Press any key to go back to main Menue..";
    }
    else
    {
        DrawClientInfoCard(client);
        std::cout << "\n\n\n";
        std::cout << "Are you sure you want delete this client? y/n ";
        std::cin >> deleteClient;
        if (deleteClient == 'y' || deleteClient == 'Y') {
            DeleteClientFromDatabase(clients, client);
            std::cout << "Client deleted successfully";
            system("pause>nul");
            PrintMainMenu();
        }
    }
    system("pause>nul");
    PrintMainMenu();
}

void UpdateClientsToDatabase(std::vector<sClient>& clients,sClient client,std::string fileName = "Clients.txt") {
    std::string record;
    fstream file;
    file.open(fileName, ios::out);
    while (file.is_open())
    {



        for (auto& i : clients)
        {
            if (!i.markForUpdate) {
                record = ConvertClientToRecord(i);
                file << record;
            }
            else
            {
                record = ConvertClientToRecord(client);
                file << record;
            }
        }
        file.close();
    }
}


void UpadateClientScreen(std::vector<sClient>& clients) {
    Clear();
    std::string accountNumber;
    sClient client;
    char updateClient;
    std::cout << DrawLine(50) << std::endl;
    std::cout << AddSpace(15) << "Update Client Screen" << AddSpace(15) << std::endl;
    std::cout << DrawLine(50) << std::endl;
    std::cout << "Please enter Account Number? ";
    cin >> accountNumber;
    bool isClientExits = IsClientExits(accountNumber, clients, client, false,true);
    if (!isClientExits) {
        std::cout << "Client with Account Number (" << accountNumber << ") is Not Found!" << std::endl;
        std::cout << "Press any key to go back to main Menue..";
    }
    else
    {
        DrawClientInfoCard(client);
        std::cout << "\n\n\n";
        std::cout << "Are you sure you want update this client? y/n ";
        std::cin >> updateClient;
        if (updateClient == 'y' || updateClient == 'Y') {
            UpdateClientsToDatabase(clients, client);
            std::cout << "Client updated successfully";
            std::cout << "Press any key to go back to main Menue..";
            system("pause>nul");
            PrintMainMenu();
        }
    }
    std::cout << "Press any key to go back to main Menue..";
    system("pause>nul");
    PrintMainMenu();
}
void ShowMenus(enOptions option)
{
    std::vector<sClient> clients = ReadClientsFromFile("Clients.txt");
    switch (option)
    {
    case Show:
        ShowClientList(clients);
        break;
    case Add:
        DrawAddNewClientScreen(clients);
        break;
    case Delete:
        DrawClientDeleteScreen(clients);
        break;
    case Update:
        UpadateClientScreen(clients);
        break;
    case Find:
        break;
    case Exit:
        break;
    default:
        break;
    }

}

void PrintMainMenu() {
    Clear();
    PrintMainMenuHeader();
    std::string options[6] = {
    "Show Client List",
    "Add New Client",
    "Delete Client",
    "Update Client",
    "Find Client",
    "Exit",
    };
    for (size_t i = 0; i < 6; i++)
    {
        PrintMainMenuOption(i, options[i]);
    }
    std::cout << "=================================" << std::endl;
    enOptions option = (enOptions)ReadOption();
    ShowMenus(option);
}
int main()
{
    sClient client = {
    "N5100",
    "2635",
    "Nemo",
    "010892",
     80.000
    };
    /* std::vector<std::string> values = SplitRecord("Hisham#//#Ahmed#//#Ali#//#Mahar#//#","#//#");
     for (auto& i : values)
     {
         std::cout << i << endl;
     }*/


     // SaveRecordToFile(ConvertClientToRecord(client));
    PrintMainMenu();
}