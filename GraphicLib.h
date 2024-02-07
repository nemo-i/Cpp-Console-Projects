#pragma once
#include<iostream>
#include<string>

namespace GraphicLib {
 
    void Clear() {
        system("cls");
    }

    std::string GenerateLine(short count)
    {
        std::string line;
        for (size_t i = 0; i < count; i++)
        {
            line += "-";
        }
        return line;
    }

	void DrawLine(short length) {
        std::cout << GenerateLine(length)<<std::endl;
	};

    std::string AddSpace(short count) {
        std::string space;
        for (size_t i = 0; i < count; i++)
        {
            space += " ";
        }
        return space;
    }


    void DrawMainMenuHeader() {
        std::cout << "=================================" << std::endl;
        std::cout << AddSpace(9) << "Main Menu Screen" << AddSpace(9) << std::endl;
        std::cout << "=================================" << std::endl;
    }

    void DrawMainMenuOption(short index, std::string title)
    {
        std::cout << AddSpace(5) << "[" << index + 1 << "] " << title << "." << std::endl;
    }

   
    void DrawClientListHeader(short clients)
    {

        DrawLine(100);
        std::cout << AddSpace(30) << "Client List (" << clients << ") Client(s)." << AddSpace(10) << std::endl;
        DrawLine(100);
        std::cout << "|" << std::setw(15) << "Account Number" << "|" << std::setw(15) << "Pin Code" << "|" << std::setw(28) << "Client Name" << "|" << std::setw(15) << "Phone" << "|" << std::setw(15) << "Balance" << "|" << std::endl;
        DrawLine(100);

    }
    void DrawAddNewClientHeader() {
        DrawLine(50);
        std::cout << AddSpace(15) << "Add New Client Screen" << AddSpace(15) << std::endl;
        DrawLine(50);
    }
    void DrawDeleteClientHeader() {
        DrawLine(50);
        std::cout << AddSpace(15) << "Delete Client Screen" << AddSpace(15) << std::endl;
        DrawLine(50);
    }
    
    void DrawUpdateScreenClientHeader() {
        DrawLine(50);
        std::cout << AddSpace(15) << "Update Client Info Screen" << AddSpace(15) << std::endl;
        DrawLine(50);
    }
    void DrawClientInfoCard(VarLib::sClient& client) {
        std::cout << "The following are the client details:" << std::endl;
        DrawLine(35);
        std::cout << "Account Number:" << client.accountNumber << std::endl;
        std::cout << "Pin Code      :" << client.pinCode << std::endl;
        std::cout << "Name          :" << client.name << std::endl;
        std::cout << "Phone         :" << client.phone << std::endl;
        std::cout << "Balance       :" << client.balance << std::endl;
        DrawLine(35);
    };
    void DrawClientRow(VarLib::sClient& client){
        std::cout << "|" << std::setw(15) << client.accountNumber << "|" << std::setw(15) << client.pinCode << "|" << std::setw(28) << client.name << "|" << std::setw(15) << client.phone << "|" << std::setw(15) << client.balance << "|" << std::endl;
    }

}

