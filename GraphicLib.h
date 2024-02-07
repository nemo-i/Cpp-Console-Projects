#pragma once
#include "Imports.h"
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
   
  
    
   

}

