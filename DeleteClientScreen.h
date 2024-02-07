

namespace DeleteClientScreen {
    void DrawDeleteClientHeader() {
        GraphicLib::DrawLine(50);
        std::cout << GraphicLib::AddSpace(15) << "Delete Client Screen" << GraphicLib::AddSpace(15) << std::endl;
        GraphicLib::DrawLine(50);
    }

    void DrawClientDeleteScreen(std::vector<VarLib::sClient>& clients) {
        GraphicLib::Clear();
        std::string accountNumber;
        VarLib::sClient client;
        char deleteClient;
        DrawDeleteClientHeader();
        std::cout << "Please enter Account Number? ";
        std::cin >> accountNumber;
        bool isClientExits = DatabaseLib::IsClientExits(accountNumber, clients, client, true);
        if (!isClientExits) {
            std::cout << "Client with Account Number (" << accountNumber << ") is Not Found!" << std::endl;
            std::cout << "Press any key to go back to main Menue..";
        }
        else
        {
            GraphicLib::DrawClientInfoCard(client);
            std::cout << "\n\n\n";
            std::cout << "Are you sure you want delete this client? y/n ";
            std::cin >> deleteClient;
            if (deleteClient == 'y' || deleteClient == 'Y') {
                DatabaseLib::DeleteClientFromDatabase(clients, client);
                std::cout << "Client deleted successfully" << std::endl;
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