#pragma once
#include "imports.h"
#include "Menus.h"
namespace MainMenu {

    std::string options[6] = {
       "Show Client List",
       "Add New Client",
       "Delete Client",
       "Update Client",
       "Find Client",
       "Exit",
    };

    void DrawOptions() {
        for (size_t i = 0; i < 6; i++)
        {
            GraphicLib::DrawMainMenuOption(i, options[i]);
        }
    }
    void ShowMenus(VarLib::enOptions option)
    {
        std::vector<VarLib::sClient> clients = IOLib::ReadClientsFromFile("Clients.txt");
        switch (option)
        {
        case VarLib::Show:
            Menus::ShowClientList(clients);
            break;
        case VarLib::Add:
            Menus::DrawAddNewClientScreen(clients);
            break;
        case VarLib::Delete:
            Menus::DrawClientDeleteScreen(clients);
            break;
        case VarLib::Update:
            Menus::DrawClientUpdateScreen(clients);
            break;
        case VarLib::Find:
            break;
        case VarLib::Exit:
            break;
        default:
            break;
        }
    }

    void PrintMainMenu() {
        GraphicLib::Clear();
        GraphicLib::DrawMainMenuHeader();
        DrawOptions();
        std::cout << "=================================" << std::endl;
        VarLib:: enOptions option = (VarLib::enOptions)IOLib::ReadOption();
        ShowMenus(option);
    }

}