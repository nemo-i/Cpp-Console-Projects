#pragma once
#include "Imports.h"
namespace DatabaseLib {
    void SaveRecordToFile(std::string record, std::string fileName = "Clients.txt")
    {
        std::fstream file;
        file.open(fileName, ios::out | ios::app);
        while (file.is_open())
        {
            file << record + "\n";
            file.close();
        }
    }
    bool IsClientExits(std::string accountNumber, std::vector<VarLib::sClient> clients, VarLib::sClient& client, bool markForDelete = false)
    {
        for (auto& i : clients)
        {
            if (accountNumber == i.accountNumber) {
                if (markForDelete) {
                    i.markForDelete = true;
                }
                client = i;
                return true;
            }

        }
        return false;
    }

    int IndexOfClientInDatabase(std::vector<VarLib::sClient>& clients, VarLib::sClient client)
    {
        for (size_t i = 0; i < clients.size(); i++)
        {
            if (clients[i].accountNumber == client.accountNumber) {
                return i;
            }
            else
            {
                return -1;
            }
        }
    }
    void AddClientAfterClearDatabase(std::vector<VarLib::sClient>& clients, std::string fileName = "Clients.txt")
    {
        std::string record;
        fstream file;
        file.open(fileName, ios::out);
        while (file.is_open())
        {



            for (auto& i : clients)
            {
                if (!i.markForDelete) {
                    record =  IOLib::ConvertClientToRecord(i);
                    file << record;
                }
            }
            file.close();
        }
    }

    void AddClientsToDatabase(std::vector<VarLib::sClient>& clients, std::string fileName = "Clients.txt")
    {
        std::string record;
        fstream file;
        file.open(fileName, ios::out || ios::app);
        while (file.is_open())
        {



            for (auto& i : clients)
            {
                if (!i.markForDelete) {
                    record = IOLib::ConvertClientToRecord(i);
                    file << record;
                }
            }
            file.close();
        }

    }
    void DeleteClientFromDatabase(std::vector<VarLib::sClient>& clients,VarLib:: sClient client)
    {
        AddClientAfterClearDatabase(clients);
    }
    void UpdateClientFromDatabase(std::vector<VarLib::sClient>& clients,VarLib:: sClient& client)
    {
        for (auto& i : clients)
        {
            if (client.accountNumber == i.accountNumber) {
                i = client;
                GraphicLib::DrawClientInfoCard(i);
            }
        }
        AddClientAfterClearDatabase(clients);
    }
}