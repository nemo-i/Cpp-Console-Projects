#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include <fstream>
#include <iomanip>
struct  sClient
{
	string name;
	string accountNumber;
	string pincode;
	double balance;
	bool isMarkForDelete = false;
	bool isMarkForUpdate = false;
};
enum enOptions {
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	Exit = 6,
};
void ShowClientList(vector<sClient> clients);
void DrawAddNewClientScreen(std::vector<sClient>& clients);
void DrawClientInfoCard(sClient& client);
void DrawClientDeleteScreen(std::vector<sClient>& clients);
void DrawMainMenu();
void DrawClientUpdateScreen(std::vector<sClient>& clients);
void DrawFindClientScreen(vector<sClient> clients);
string ConvertClientToRecord(sClient client,string sep = "#//#") {
	string record;
	record += client.name + sep;
	record += client.accountNumber + sep;
	record += client.pincode + sep;
	record += to_string(client.balance) + sep;
	return record;
}


vector<string> SplitRecord(string record,string sep = "#//#") {
	vector<string> clientData;
	
	while (record.length()>0)
	{
		short pos = record.find(sep);
		if (pos != -1) {
		clientData.push_back(record.substr(0,pos));
		}
		record.erase(0, pos + sep.length());
	}
	return clientData;
}

sClient ConvertClientDataToClient(vector<string>clientData){
	sClient client;
	client.name = clientData[0];
	client.accountNumber = clientData[1];
	client.pincode = clientData[2];
	client.balance = stod(clientData[3]);
	return client;
}


bool FindClientByAccountNumber(vector<sClient>& clients,string accountNumber ,sClient& client) {
	for (auto& i : clients)
	{
		if (i.accountNumber == accountNumber) {
			client = i;
			return true;
		}
	}
	return false;
}

sClient MarkClientForUpdate(vector<sClient> &clients,sClient &client) {
	for (auto& i : clients)
	{
		if (client.accountNumber == i.accountNumber) {
			i.isMarkForUpdate = true;
		}
	}
	return client;
}

sClient MarkClientForDelete(vector<sClient>& clients, sClient& client) {
	for (auto& i : clients)
	{
		if (client.accountNumber == i.accountNumber) {
			i.isMarkForDelete = true;
		}
	}
	return client;
}

vector<sClient> UpdateClientM(vector<sClient> &clients, sClient client) {
	for (auto& i : clients)
	{
		if (i.accountNumber == client.accountNumber) {
			i = client;
		}
	}
	return clients;
}

void SaveRecordToDatabase(string record, string fileName = "Clients.txt") {
	fstream file;
	file.open(fileName, ios::out | ios::app);
	while (file.is_open())
	{
		file << record<<endl;
		file.close();
	}
}

vector<sClient> DeleteClient(vector<sClient> &clients,string fileName = "Clients.txt") {
	fstream file;
	file.open(fileName, ios::out);
	while (file.is_open())
	{
		for (auto& i : clients)
		{
			if (!i.isMarkForDelete) {
				SaveRecordToDatabase(ConvertClientToRecord(i));
			}
		}
		file.close();
	}
	return clients;
}

vector<sClient> UpdateClient(vector<sClient> &clients,sClient newClient,string fileName ="Clients.txt") {
	fstream file;
	file.open(fileName, ios::out);
	while (file.is_open())
	{
		for (auto& i : clients)
		{
			if (!i.isMarkForUpdate) {
				SaveRecordToDatabase(ConvertClientToRecord(i));
			}
			else
			{
				SaveRecordToDatabase(ConvertClientToRecord(newClient));
			}
		}
		file.close();
	}
	return clients;
}

vector<sClient> ReadClientsFromDatabase(string fileName = "Clients.txt") {
	fstream file;
	file.open(fileName,ios::in);
	string record;
	vector<sClient> clients;
	while (file.is_open())
	{
		while (getline(file, record))
		{
			vector<string> clientData = SplitRecord(record);
			sClient client = ConvertClientDataToClient(clientData);
			clients.push_back(client);

		}
		file.close();
	}
	
	return clients;
}


void WriteClientsToDatabase(vector<sClient>& clients, string fileName = "Clients.txt")
{
	fstream file;
	file.open(fileName, ios::out);
	while (file.is_open())
	{
		for (auto& i : clients) {
			string record = ConvertClientToRecord(i);
			file << record<<endl;
		}
		file.close();
	}
}

void WriteClientToDatabase(sClient& client, string fileName = "Clients.txt") {
	fstream file;
	file.open(fileName, ios::out|ios::app);
	while (file.is_open())
	{
		
			string record = ConvertClientToRecord(client);
			file << record << endl;
		
		file.close();
	}
}

sClient ReadClientFromUserWithoutAccountNumber(sClient &client) {
	sClient iclient;
	cout << "Enter Client Name? ";
	getline(cin>>ws, client.name);
	cout << "Enter PinCode? ";
	cin >> client.pincode;
	cout << "Enter Client Balance? ";
	cin >> client.balance;
	return iclient;
}

void ReadClientFromUserWithAccountNumber(vector<sClient> &clients,sClient &client) {
	
	string accountNumber;
	cout << "Enter Client Account Number? ";
	getline(cin>>ws,accountNumber);
	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		cout << "Client With Account Number [" << client.accountNumber << "] Already Exits\n";
		
	}
	else
	{
		ReadClientFromUserWithoutAccountNumber(client);
		client.accountNumber = accountNumber;
		
	}
}



void ReadAndAddClientToClientListAndDatabase() {
	vector<sClient> clients = ReadClientsFromDatabase();
	char addMore;
	sClient client;

	do
	{
		ReadClientFromUserWithAccountNumber(clients,client);
		WriteClientToDatabase(client);
		cout << "Are you want to add more clients Y/N? ";
		cin >> addMore;
	} while (addMore =='Y' || addMore == 'y');
	
}


void UpdateClientAndSaveToDatabase(vector<sClient> clients) {
	string accountNumber;
	cout << "Enter Client Account Number? ";
	cin >> accountNumber;
	sClient client;
	char sure;
	bool found =FindClientByAccountNumber(clients, accountNumber, client);
	if (found) {
		DrawClientInfoCard(client);
		cout << "Are you sure want to update this client Y/N? ";
		cin >> sure;
		if (sure == 'Y' || sure == 'y') {
			MarkClientForUpdate(clients, client);
			ReadClientFromUserWithoutAccountNumber(client);
			UpdateClient(clients, client);
			cout << "Client Updated Successfully!\n";
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
			DrawMainMenu();
		}
		else
		{
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
			DrawMainMenu();
		}
	}
	else
	{
		cout << "Client not found\n";
		cout << "Press any key to go to main menu... ";
		system("pause>nul");
		DrawMainMenu();
	}
}

void DeleteClientAndSaveToDatabase(vector<sClient> clients) {
	string accountNumber;
	cout << "Enter Client Account Number? ";
	cin >> accountNumber;
	sClient client;
	char sure;
	bool found = FindClientByAccountNumber(clients, accountNumber, client);
	if (found) {
		DrawClientInfoCard(client);
		cout << "Are you sure want to delete this client Y/N? ";
		cin >> sure;
		if (sure == 'Y' || sure == 'y') {
			MarkClientForDelete(clients, client);
			DeleteClient(clients);
			cout << "Client Deleted Successfully!\n";
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
			DrawMainMenu();
		}
		else
		{
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
			DrawMainMenu();
		}
	}
	else
	{
		cout << "Client not found\n";
		cout << "Press any key to go to main menu... ";
		system("pause>nul");
		DrawMainMenu();
	}
}
std::string AddSpace(short count) {
	std::string space;
	for (size_t i = 0; i < count; i++)
	{
		space += " ";
	}
	return space;
}
void DrawMainMenuHeader() {
	cout << "=================================" << endl;
	cout << AddSpace(9) << "Main Menu Screen" << AddSpace(9) << endl;
	cout << "=================================" << endl;
}
void DrawMainMenuOption(short index, string title)
{
	cout << AddSpace(5) << "[" << index + 1 << "] " << title << "." << endl;
}
void DrawOptions() {
	string options[6] = {
	   "Show Client List",
	   "Add New Client",
	   "Delete Client",
	   "Update Client",
	   "Find Client",
	   "Exit",
	};

	for (size_t i = 0; i < 6; i++)
	{
		DrawMainMenuOption(i, options[i]);
	}
}

void ShowMenus(enOptions option)
{
	vector<sClient> clients = ReadClientsFromDatabase();
	switch (option)
	{
	case Show:
		ShowClientList(clients);
		break;
	case Add:
		DrawAddNewClientScreen(clients);
		break;
	case Delete:
		DrawClientDeleteScreen(clients);
		break;
	case Update:
		DrawClientUpdateScreen(clients);
		break;
	case Find:
		DrawFindClientScreen(clients);
		break;
	case Exit:
		return;
		break;
	default:
		return;
		break;
	}
}
void Clear() {
	system("cls");
}
short ReadOption() {
	std::cout << "Choose what do you want to do? [1 to 6]?";
	short option;
	std::cin >> option;
	return option;
}
void DrawMainMenu() {
	Clear();
	DrawMainMenuHeader();
	DrawOptions();
	cout << "=================================" << endl;
	enOptions option = (enOptions)ReadOption();
	ShowMenus(option);
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
	std::cout << GenerateLine(length) << std::endl;
};

void DrawClientRow(sClient& client) {
	std::cout << "|" << std::setw(15) << client.accountNumber << "|" << std::setw(15) << client.pincode << "|" << std::setw(28) << client.name  << "|" << std::setw(15) << client.balance << "|" << std::endl;
}
void DrawClientListHeader(short clients)
{

	DrawLine(100);
	std::cout << AddSpace(30) << "Client List (" << clients << ") Client(s)." << AddSpace(10) << std::endl;
	DrawLine(100);
	std::cout << "|" <<setw(15) << "Account Number" << "|" << std::setw(15) << "Pin Code" << "|" << std::setw(28) << "Client Name"  << "|" << std::setw(15) << "Balance" << "|" << std::endl;
	DrawLine(100);

}

void ShowClientList(vector<sClient> clients) {

	Clear();
	DrawClientListHeader(clients.size());
	for (auto& i : clients)
	{
		DrawClientRow(i);
	}
	DrawLine(100);
	std::cout << "Press any key to go to main menu..." << std::endl;
	system("pause>nul");
	DrawMainMenu();
}

void DrawAddNewClientHeader() {
	DrawLine(50);
	std::cout << AddSpace(15) << "Add New Client Screen" << AddSpace(15) << std::endl;
	DrawLine(50);
}
void DrawAddNewClientScreen(std::vector<sClient>& clients) {
	sClient client;
	std::string record;
	std::string addMore;
	Clear();
	DrawAddNewClientHeader();
	ReadAndAddClientToClientListAndDatabase();
	cout << "Press any key to go to main menu? ";
	system("pause>nul");
	DrawMainMenu();
}
void DrawDeleteClientHeader() {
	DrawLine(50);
	std::cout << AddSpace(15) << "Delete Client Screen" << AddSpace(15) << std::endl;
	DrawLine(50);
}
void DrawClientInfoCard(sClient& client) {
	std::cout << "The following are the client details:" << std::endl;
	DrawLine(35);
	std::cout << "Account Number:" << client.accountNumber << std::endl;
	std::cout << "Pin Code      :" << client.pincode << std::endl;
	std::cout << "Name          :" << client.name << std::endl;
	std::cout << "Balance       :" << client.balance << std::endl;
	DrawLine(35);
};
void DrawClientDeleteScreen(std::vector<sClient>& clients) {
	Clear();
	std::string accountNumber;
	sClient client;
	char deleteClient;
	DrawDeleteClientHeader();
	DeleteClientAndSaveToDatabase(clients);
}
void DrawUpdateScreenClientHeader() {
	DrawLine(50);
	std::cout << AddSpace(15) << "Update Client Info Screen" << AddSpace(15) << std::endl;
	DrawLine(50);
}

void DrawClientUpdateScreen(std::vector<sClient>& clients) {
	Clear();
	DrawUpdateScreenClientHeader();
	UpdateClientAndSaveToDatabase(clients);
}
void DrawFindClientScreenHeader() {
	DrawLine(50);
	std::cout << AddSpace(15) << "Find Client Screen" << AddSpace(15) << std::endl;
	DrawLine(50);
}

void FindClient(vector<sClient> clients) {
	sClient client;
	string accountNumber;
	cout << "Enter Client Account Number? ";
	cin >> accountNumber;
	char sure;
	bool found = FindClientByAccountNumber(clients, accountNumber, client);
	if (found) {
		DrawClientInfoCard(client);
		cout << "Press any key to go to main menu\n";
		system("pause>nul");
		DrawMainMenu();
	}
	else
	{
		cout << "Client With Account Number [" << accountNumber << "] Not Found\n";
		cout << "Press any key to go to main menu\n";
		system("pause>nul");
		DrawMainMenu();
	}
}
void DrawFindClientScreen(vector<sClient> clients) {
	Clear();
	DrawFindClientScreenHeader();
	FindClient(clients);
}

int main() {
	sClient client1{
		"Hisham",
		"A1501",
		"69000",
		9600.0,
	};
	sClient client2{
		"Hash",
		"A1500",
		"69000",
		9600.0,
		false,
		true,
	};
	sClient newClient{
		"Kimo",
		"A1500",
		"69000",
		9600.0,
		true,
		false,
	};

	vector<sClient> clients = {client1,newClient};
	//WriteClientsToDatabase(clients);
	//UpdateClient(clients,newClient);

	//DeleteClient(clients);
clients =ReadClientsFromDatabase();
//for (auto& i : clients)
//{
//	cout << i.name << endl;
//}
	//ReadAndAddClientToClientListAndDatabase();
	//UpdateClientAndSaveToDatabase(clients);
//DeleteClientAndSaveToDatabase(clients);
DrawMainMenu();
	return 0;
}