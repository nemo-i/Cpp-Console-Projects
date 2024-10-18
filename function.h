#pragma once
#include <vector>
#include <string>
struct  sClient
{
	std::string name;
	std::string accountNumber;
	std::string pincode;
	double balance;
	bool isMarkForDelete = false;
	bool isMarkForUpdate = false;
};
struct sUser
{
	std::string username = "";
	std::string password = "";
	short previlage = 0;
	bool isMarkForDelete = false;
	bool isMarkForUpdate = false;
	bool isMarkForChangePrevilage = false;
};
enum enOptions {
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Transction = 6,
	Manage = 7,
	Exit = 8,
};
enum enManagerOptions {
	ListUsers = 1,
	AddUser = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	FindUser = 5,
	MainMenu = 6,
};
enum TranscationOptions
{
	deposite = 1,
	withdraw = 2,
	totalbalance = 3,
	quit = 4,
};
void Clear();
void DrawLoginScreen(std::vector<sUser>& users);
void ShowClientList(std::vector<sClient> clients, bool showTotalBalance);
void DrawAddNewClientScreen(std::vector<sClient>& clients);
void DrawClientInfoCard(sClient& client);
void DrawClientDeleteScreen(std::vector<sClient>& clients);
void DrawMainMenu();
void DrawClientUpdateScreen(std::vector<sClient>& clients);
void DrawFindClientScreen(std::vector<sClient> clients);
void DrawLine(short length);
void WithdrawScreen(std::vector<sClient>& clients);
std::string AddSpace(short count);
void DepositScreen(std::vector <sClient>& clients);
void DrawTranscationMenu(std::vector<sClient>& clients);
void DrawManageUsersScreenHeader();
enManagerOptions DrawMangeUserScreen(std::vector<sUser> &users);
void DrawUserListScreenHeader(std::vector<sUser> &users);
void DrawUserListScreen(std::vector<sUser>& users);