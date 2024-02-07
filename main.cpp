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

sClient MarkClientForUpdate(sClient client) {
	client.isMarkForUpdate = true;
	return client;
}

sClient MarkClientForDelete(sClient client) {
	client.isMarkForDelete = true;
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
	while (getline(file,record))
	{
		vector<string> clientData =SplitRecord(record);
		sClient client = ConvertClientDataToClient(clientData);
		clients.push_back(client);
	}
	return clients;
}


void WriteClientsToDatabase(vector<sClient>& clients, string fileName = "Clients.txt")
{
	fstream file;
	file.open(fileName, ios::out | ios::app);
	while (file.is_open())
	{
		for (auto& i : clients) {
			string record = ConvertClientToRecord(i);
			file << record<<endl;
		}
		file.close();
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

	DeleteClient(clients);
	return 0;
}