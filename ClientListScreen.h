#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include "DatabaseLib.h"
#include "GraphicLib.h"
#include "IOLib.h"
#include "VarLib.h"
#include <vector>
#include "MainMenu.h"
#include "ClientListScreen.h"
#include "AddNewClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateScreen.h"
using namespace std;
namespace ClientListScreen {
    void DrawClientRow(VarLib::sClient& client) {
        std::cout << "|" << std::setw(15) << client.accountNumber << "|" << std::setw(15) << client.pinCode << "|" << std::setw(28) << client.name << "|" << std::setw(15) << client.phone << "|" << std::setw(15) << client.balance << "|" << std::endl;
    }
    void DrawClientListHeader(short clients)
    {

        GraphicLib::DrawLine(100);
        std::cout <<GraphicLib::  AddSpace(30) << "Client List (" << clients << ") Client(s)." <<GraphicLib:: AddSpace(10) << std::endl;
        GraphicLib::  DrawLine(100);
        std::cout << "|" << std::setw(15) << "Account Number" << "|" << std::setw(15) << "Pin Code" << "|" << std::setw(28) << "Client Name" << "|" << std::setw(15) << "Phone" << "|" << std::setw(15) << "Balance" << "|" << std::endl;
        GraphicLib:: DrawLine(100);

    }

    void ShowClientList(std::vector<VarLib::sClient> clients) {

        GraphicLib::Clear();
        DrawClientListHeader(clients.size());
        for (auto& i : clients)
        {
            DrawClientRow(i);
        }
        GraphicLib::DrawLine(100);
        std::cout << "Press any key to go to main menu..." << std::endl;
        system("pause");
        MainMenu::PrintMainMenu();
    }
}