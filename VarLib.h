#pragma once
#include <string>

namespace VarLib {
    enum enOptions {
        Show = 1,
        Add = 2,
        Delete = 3,
        Update = 4,
        Find = 5,
        Exit = 6,
    };
    struct sClient
    {
        std::string accountNumber;
        std::string pinCode;
        std::string name;
        std::string phone;
        double balance;
        bool markForDelete = false;
        bool markForUpdate = false;
    };
}