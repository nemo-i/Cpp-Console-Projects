
#include <iostream>
using namespace std;

std::string AddSpace(short count){
    std::string space;
    for (size_t i = 0; i < count; i++)
    {
        space += " ";
    }
    return space;
}
void PrintMainMenuHeader() {
    std::cout << "=================================" << std::endl;
    std::cout <<AddSpace(9) << "Main Menu Screen" << AddSpace(9)<< std::endl;
    std::cout << "=================================" << std::endl;
}

void PrintMainMenuOption(short index, std::string title)
{
    std::cout <<AddSpace(5)<< "[" << index + 1 << "] " << title << "." << std::endl;
}



short ReadOption() {
    std::cout << "Choose what do you want to do? [1 to 6]?";
    short option;
    std::cin >> option;
    return option;
}
void Clear() {
    system("cls");
}

enum  enOptions
{
    Show = 1,
    Add  = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Exit = 6,
};
void ShowMenus(enOptions option)
{
    switch (option)
    {
    case Show:
        break;
    case Add:
        break;
    case Delete:
        break;
    case Update:
        break;
    case Find:
        break;
    case Exit:
        break;
    default:
        break;
    }
    
}
void ShowClientList() {

}

void PrintMainMenu() {
    Clear();
    PrintMainMenuHeader();
    std::string options[6] = {
    "Show Client List",
    "Add New Client",
    "Delete Client",
    "Update Client",
    "Find Client",
    "Exit",
    };
    for (size_t i = 0; i < 6; i++)
    {
        PrintMainMenuOption(i,options[i]);
    }
    std::cout << "=================================" << std::endl;
   enOptions option = (enOptions) ReadOption();
   ShowMenus(option);
}
int main()
{
    PrintMainMenu();
}

