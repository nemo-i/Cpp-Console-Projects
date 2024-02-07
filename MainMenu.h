#pragma once
#include "IOLib.h"
#include "Menus.h"
#include "GraphicLib.h"
#include "ClientListScreen.h"
#include "AddNewClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateScreen.h"
namespace MainMenu {
    void DrawMainMenuHeader() {
        std::cout << "=================================" << std::endl;
        std::cout <<GraphicLib::AddSpace(9) << "Main Menu Screen" << GraphicLib::AddSpace(9) << std::endl;
        std::cout << "=================================" << std::endl;
    }
    void DrawMainMenuOption(short index, std::string title)
    {
        std::cout << GraphicLib::AddSpace(5) << "[" << index + 1 << "] " << title << "." << std::endl;
    }
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
           DrawMainMenuOption(i, options[i]);
        }
    }
    void ShowMenus(VarLib::enOptions option)
    {
        std::vector<VarLib::sClient> clients = IOLib::ReadClientsFromFile("Clients.txt");
        switch (option)
        {
        case VarLib::Show:
            ClientListScreen::ShowClientList(clients);
            break;
        case VarLib::Add:
            AddNewClientScreen::DrawAddNewClientScreen(clients);
            break;
        case VarLib::Delete:
            DeleteClientScreen::DrawClientDeleteScreen(clients);
            break;
        case VarLib::Update:
            ClientUpdateScreen::DrawClientUpdateScreen(clients);
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
        DrawMainMenuHeader();
        DrawOptions();
        std::cout << "=================================" << std::endl;
        VarLib:: enOptions option = (VarLib::enOptions)IOLib::ReadOption();
        ShowMenus(option);
    }

}