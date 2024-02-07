#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include <fstream>
struct  sClient
{
	string name;
	string accountNumber;
	string pincode;
	double balance;
	bool isMarkForDelete = false;
	bool isMarkForUpdate = false;
};

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
		return;
	}
	else
	{
		client = ReadClientFromUserWithoutAccountNumber(client);
		client.accountNumber = accountNumber;
		return;
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
		cout << "Are you sure want to update this client Y/N? ";
		cin >> sure;
		if (sure == 'Y' || sure == 'y') {
			MarkClientForUpdate(clients, client);
			ReadClientFromUserWithoutAccountNumber(client);
			UpdateClient(clients, client);
			cout << "Client Updated Successfully!\n";
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
		}
		else
		{
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
		}
	}
	else
	{
		cout << "Client not found\n";
		cout << "Press any key to go to main menu... ";
		system("pause>nul");
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
		cout << "Are you sure want to delete this client Y/N? ";
		cin >> sure;
		if (sure == 'Y' || sure == 'y') {
			MarkClientForDelete(clients, client);
			DeleteClient(clients);
			cout << "Client Deleted Successfully!\n";
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
		}
		else
		{
			cout << "Press any key to go to main menu... ";
			system("pause>nul");
		}
	}
	else
	{
		cout << "Client not found\n";
		cout << "Press any key to go to main menu... ";
		system("pause>nul");
	}
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
DeleteClientAndSaveToDatabase(clients);
	return 0;
}