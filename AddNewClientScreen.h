#pragma once
#include <vector>
#include "VarLib.h"
#include "GraphicLib.h"
#include "IOLib.h"
#include "MainMenu.h"
namespace AddNewClientScreen {

    void DrawAddNewClientHeader() {
        GraphicLib::DrawLine(50);
        std::cout << GraphicLib::AddSpace(15) << "Add New Client Screen" << GraphicLib::AddSpace(15) << std::endl;
        GraphicLib::DrawLine(50);
    }
    void DrawAddNewClientScreen(std::vector<VarLib::sClient>& clients) {
        VarLib::sClient client;
        std::string record;
        std::string addMore;
        GraphicLib::Clear();
        DrawAddNewClientHeader();
        std::cout << "Adding New Client:" << std::endl;
        do
        {
            client = IOLib::ReadClientFromUser(clients);
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
}