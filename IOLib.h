#pragma once
#include "Imports.h"
namespace IOLib {
    short ReadOption() {
        std::cout << "Choose what do you want to do? [1 to 6]?";
        short option;
        std::cin >> option;
        return option;
    }
    std::string ConvertClientToRecord(VarLib::sClient& client, std::string sepatrator = "#//#")
    {
        return client.accountNumber + sepatrator + client.pinCode + sepatrator + client.name + sepatrator + client.phone + sepatrator + to_string(client.balance);
    }
    std::vector<std::string> SplitRecord(std::string record, std::string separator)
    {
        std::vector<std::string> values;
        bool showSeparator = false;
        std::string recordv;
        short pos;
        do
        {
            pos = record.find(separator);
            recordv = record.substr(0, pos);
            values.push_back(recordv);
            record.erase(0, pos + separator.length());
        } while (pos != -1);



        return values;
    }
    VarLib::sClient ConvertRecordToClient(std::string record, std::string separator)
    {
        VarLib::sClient client;
        std::vector<std::string> values = SplitRecord(record, separator);
        client.accountNumber = values[0];
        client.pinCode = values[1];
        client.name = values[2];
        client.phone = values[3];
        client.balance = stod(values[4]);

        return client;
    }
    std::vector<VarLib::sClient> ReadClientsFromFile(std::string fileName = "Clients.txt")
    {
        std::fstream file;
        std::string record;
        std::vector<VarLib::sClient> clients;
        VarLib::sClient client;
        file.open(fileName, ios::in);
        if (file.is_open())
        {
            while (getline(file, record))
            {
                client = ConvertRecordToClient(record, "#//#");
                clients.push_back(client);
            }
            file.close();
        }
        return clients;
    }
}