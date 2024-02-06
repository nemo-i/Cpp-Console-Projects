
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
void PrintMainMenu();
std::string AddSpace(short count){
    std::string space;
    for (size_t i = 0; i < count; i++)
    {
        space += " ";
    }
    return space;
}
void PrintMainMenuHeader() {
    std::cout << "=================================" << std::endl;
    std::cout <<AddSpace(9) << "Main Menu Screen" << AddSpace(9)<< std::endl;
    std::cout << "=================================" << std::endl;
}

void PrintMainMenuOption(short index, std::string title)
{
    std::cout <<AddSpace(5)<< "[" << index + 1 << "] " << title << "." << std::endl;
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
    Add  = 2,
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

void DrawClientRow(sClient client)
{
    std::cout << "|"<<std::setw(15) << client.accountNumber << "|" << std::setw(15) << client.pinCode << "|" << std::setw(28) << client.name <<"|" << std::setw(15) << client.phone << "|" << std::setw(15) << client.balance <<"|"<< std::endl;
}
std::string ConvertClientToRecord(sClient& client, std:: string sepatrator = "#//#")
{
    return client.accountNumber + sepatrator + client.pinCode + sepatrator + client.name + sepatrator + client.phone + sepatrator + to_string(client.balance);
}

void SaveRecordToFile( std::string record, std::string fileName = "Clients.txt")
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
    std::cout << "|" << std::setw(15) << "Account Number" << "|" << std::setw(15) << "Pin Code" << "|" << std::setw(28) << "Client Name" << "|" << std::setw(15) << "Phone" << "|" << std::setw(15) << "Balance" <<"|" << std::endl;
   // std::cout << std::setw(15) << "|Account Number" << std::setw(15) << "| Pin Code" << std::setw(28) << "| Client Name" << std::setw(15) << "| Phone" << std::setw(15) << "| Balance" << std::endl;
    std::cout << DrawLine(100) << std::endl;
    
}
std::vector<std::string> SplitRecord(std::string record, std::string separator)
{
    std::vector<std::string> values;
    bool showSeparator = false;
    std::string recordv;
    short pos ;
    do
    {
        pos = record.find(separator);
        recordv = record.substr(0, pos);
        values.push_back(recordv);
        record.erase(0,pos+separator.length());
    } while (pos!=-1);
    
        

    return values;
}

//sClient ConvertRecordToClient(std::string record)
//{
//
//    return;
//}

//std::vector<sClient> ReadRecordFromFile(std::string fileName = "Clients.txt")
//{
//    std::fstream file;
//    std::string record;
//    file.open(fileName, ios::in);
//    if (file.is_open())
//    {
//        while (getline(file, record))
//        {
//
//        }
//        file.close();
//    }
//    return;
//}

void ShowClientList() {
    sClient client = {
    "A5100",
    "2356",
    "Hisham",
    "0106982",
    200.000
    };
    Clear();
    DrawClientListHeader(6);
    DrawClientRow(client);
    std::cout << DrawLine(100) << std::endl;
    std::cout << "Press any key to go to main menu..." << std::endl;
    system("pause");
    
    PrintMainMenu();
}
void ShowMenus(enOptions option)
{
    switch (option)
    {
    case Show:
        ShowClientList();
        break;
    case Add:
        break;
    case Delete:
        break;
    case Update:
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
        PrintMainMenuOption(i,options[i]);
    }
    std::cout << "=================================" << std::endl;
   enOptions option = (enOptions) ReadOption();
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
   std::vector<std::string> values = SplitRecord("Hisham#//#Ahmed#//#Ali#//#Mahar#//#","#//#");
   for (auto& i : values)
   {
       std::cout << i << endl;
   }
   // SaveRecordToFile(ConvertClientToRecord(client));
  //  PrintMainMenu();
}

