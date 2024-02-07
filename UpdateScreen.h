#pragma once
#include "GraphicLib.h"
#include "VarLib.h"
#include "DatabaseLib.h"
#include "MainMenu.h"
namespace ClientUpdateScreen {

    void DrawUpdateScreenClientHeader() {
      GraphicLib::  DrawLine(50);
        std::cout << GraphicLib::AddSpace(15) << "Update Client Info Screen" << GraphicLib::AddSpace(15) << std::endl;
        GraphicLib::DrawLine(50);
    }

    void DrawClientUpdateScreen(std::vector<VarLib::sClient>& clients) {
        GraphicLib::Clear();
        std::string accountNumber;
        VarLib::sClient client;
        char updateClient;
        DrawUpdateScreenClientHeader();
        std::cout << "Please enter Account Number? ";
        cin >> accountNumber;
        bool isClientExits = DatabaseLib::IsClientExits(accountNumber, clients, client, true);
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