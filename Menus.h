#pragma once
#include "Imports.h"
#include "MainMenu.h"
namespace Menus {
    void ShowClientList(std::vector<VarLib::sClient> clients) {

        GraphicLib::Clear();
        GraphicLib::DrawClientListHeader(clients.size());
        for (auto& i : clients)
        {
           GraphicLib::DrawClientRow(i);
        }
        GraphicLib::DrawLine(100) ;
        std::cout << "Press any key to go to main menu..." << std::endl;
        system("pause");
        MainMenu::PrintMainMenu();
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
    void DrawAddNewClientScreen(std::vector<VarLib::sClient>& clients) {
        VarLib::sClient client;
        std::string record;
        std::string addMore;
        GraphicLib::Clear();
        GraphicLib::DrawAddNewClientHeader();
        std::cout << "Adding New Client:" << std::endl;
        do
        {
            client = ReadClientFromUser(clients);
            record = IOLib::ConvertClientToRecord(client);
            DatabaseLib::SaveRecordToFile(record);
            clients.push_back(client);
            std::cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
            cin >> addMore;
        } while (addMore == "y");
        std::cout << "Press any key to go to main menu..." << std::endl;
        system("pause>nul");
        MainMenu::PrintMainMenu();

    }






    void DrawClientDeleteScreen(std::vector<VarLib::sClient>& clients) {
        GraphicLib::Clear();
        std::string accountNumber;
        VarLib::sClient client;
        char deleteClient;
        GraphicLib::DrawDeleteClientHeader();
        std::cout << "Please enter Account Number? ";
        cin >> accountNumber;
        bool isClientExits = IsClientExits(accountNumber, clients, client, true);
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
                std::cout << "Client deleted successfully" << std::endl;
                std::cout << "Press any key to go back to main Menue..";
                system("pause>nul");
                PrintMainMenu();
            }
        }
        std::cout << "Press any key to go back to main Menue..";
        system("pause>nul");
        PrintMainMenu();
    }


    void DrawClientUpdateScreen(std::vector<VarLib::sClient>& clients) {
        GraphicLib::Clear();
        std::string accountNumber;
        VarLib::sClient client;
        char updateClient;
        GraphicLib::DrawUpdateScreenClientHeader();
        std::cout << "Please enter Account Number? ";
        cin >> accountNumber;
        bool isClientExits = IsClientExits(accountNumber, clients, client, true);
        if (!isClientExits) {
            std::cout << "Client with Account Number (" << accountNumber << ") is Not Found!" << std::endl;
            std::cout << "Press any key to go back to main Menue..";
        }
        else
        {
            GraphicLib::DrawClientInfoCard(client);
            std::cout << "\n\n\n";
            std::cout << "Are you sure you want update this client? y/n ";
            std::cin >> updateClient;
            if (updateClient == 'y' || updateClient == 'Y') {

                std::cout << "Enter PinCode? ";
                getline(cin >> ws, client.pinCode);
                std::cout << "Enter Client Name? ";
                getline(cin, client.name);
                std::cout << "Enter Client Phone? ";
                getline(cin, client.phone);
                std::cout << "Enter Client Balance?";
                cin >> client.balance;
                DatabaseLib::UpdateClientFromDatabase(clients, client);
                std::cout << "Client updated successfully" << std::endl;
                std::cout << "Press any key to go back to main Menue..";
                system("pause>nul");
                MainMenu::PrintMainMenu();
            }
        }
        std::cout << "Press any key to go back to main Menue..";
        system("pause>nul");
        MainMenu::PrintMainMenu();
    }
}