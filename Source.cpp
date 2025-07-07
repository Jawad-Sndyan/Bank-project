#include<iostream>
#include<cctype>
#include<string>
#include<windows.h>
#include<vector>
#include<iomanip>
#include<fstream>
#include"\Users\j7664\Source\Repos\Main Library\Main Library/Sounds.h"
#include"\Users\j7664\Source\Repos\Main Library\Main Library/ScreenDesigner.h"
#include"\Users\j7664\Source\Repos\Main Library\Main Library/Numbers.h"
#include"\Users\j7664\Source\Repos\Main Library\Main Library/Text.h"
using namespace std;
string ClientsFile = "Clients.txt";
string UsersFile = "Users.txt";
enum enTransactions { Deposite = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4 };
enum enBank { List = 1, New = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6,ManageUsers=7, Exit = 8 };
enum enUsers { uList = 1, uNew = 2, uDelete = 3, uUpdate = 4, uFind = 5, uMainMenue = 6 };
enum enUserPermissions {
	pAll = -1, pListClients = 1, pNewClients = 2, pDeleteClients = 4, pUpdateClients = 8, pFindClients = 16,
	pTransactions = 32, pManageUsers = 64
};
void PerformMainMenueOperatoins(enBank bank);
void BankProgram();
void GoBackToMainMenue();
void PerformTransactionsMenueOperatoins(enTransactions Transactions);
enTransactions ReadTransactionsMenueOperatoins(string message);
void GoBackToTransactionMenue();
void TransactionProgram();
void GoBackToManageUsersMenue();
void BankAplication();
struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};
struct stUser
{
	string Name = "";
	string Password = "";
	int Permissions = 0;
	bool MarkForDelete = false;
};
stUser CurrentUser;
void MainMenueScreen()
{
	cout << ScreenDesigner::Line(50, '=') << endl;
	cout << "\t\tMain Menue Screen" << endl;
	cout << ScreenDesigner::Line(50, '=') << endl;
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Manage Users\n";
	cout << "\t[8] Exit\n";
	cout << ScreenDesigner::Line(50, '=') << endl;
}
void AddNewClientsScreen()
{
	cout << "\n" << ScreenDesigner::Line(60, '-') << endl;
	cout << "\t\tAdd New Clients Screen" << endl;
	cout << ScreenDesigner::Line(60, '-') << endl;
}
void DeleteClientsScreen()
{
	cout << "\n" << ScreenDesigner::Line(52, '-') << endl;
	cout << "\t\tDelete Clients Screen" << endl;
	cout << ScreenDesigner::Line(52, '-') << endl;
}
void UpdateClientsInfoScreen()
{
	cout << "\n" << ScreenDesigner::Line(60, '-') << endl;
	cout << "\t\tUpdate Clients Info Screen" << endl;
	cout << ScreenDesigner::Line(60, '-') << endl;
}
void FindClientsScreen()
{
	cout << "\n" << ScreenDesigner::Line(50, '-') << endl;
	cout << "\t\tFind Clients Screen" << endl;
	cout << ScreenDesigner::Line(50, '-') << endl;
}
void TransactionsMenueScreen()
{
	cout << ScreenDesigner::Line(55, '=') << endl;
	cout << "\t\tTransactions Menue Screen" << endl;
	cout << ScreenDesigner::Line(55, '=') << endl;
	cout << "\t[1] Deposite\n";
	cout << "\t[2] WithDraw\n";
	cout << "\t[3] TotalBalances\n";
	cout << "\t[4] Main Menue\n";
	cout << ScreenDesigner::Line(55, '=') << endl;
}
void DepositeScreen()
{
	cout << "\n" << ScreenDesigner::Line(50, '-') << endl;
	cout << "\t\tDeposit Screen" << endl;
	cout << ScreenDesigner::Line(50, '-') << endl;
}
void WithdrawScreen()
{
	cout << "\n" << ScreenDesigner::Line(50, '-') << endl;
	cout << "\t\tWithdraw Screen" << endl;
	cout << ScreenDesigner::Line(50, '-') << endl;
}
void ExitScreen()
{
	cout << "\n" << ScreenDesigner::Line(50, '-') << endl;
	cout << "\t\tProgram Ends :-)" << endl;
	cout << ScreenDesigner::Line(50, '-') << endl;
}
void ManageUsersMenueScreen()
{
	cout << ScreenDesigner::Line(50, '=') << endl;
	cout << "\t   Manage Users Menue Screen" << endl;
	cout << ScreenDesigner::Line(50, '=') << endl;
	cout << "\t[1] Show Users List\n";
	cout << "\t[2] Add New User\n";
	cout << "\t[3] Delete User\n";
	cout << "\t[4] Update User Info\n";
	cout << "\t[5] Find User\n";
	cout << "\t[6] Main Menue\n";
	cout << ScreenDesigner::Line(50, '=') << endl;
}
void AddNewUsersScreen()
{
	cout << "\n" << ScreenDesigner::Line(60, '-') << endl;
	cout << "\t\tAdd New Users Screen" << endl;
	cout << ScreenDesigner::Line(60, '-') << endl;
}
void DeleteUsersScreen()
{
	cout << "\n" << ScreenDesigner::Line(52, '-') << endl;
	cout << "\t\tDelete Users Screen" << endl;
	cout << ScreenDesigner::Line(52, '-') << endl;
}
void UpdateUsersInfoScreen()
{
	cout << "\n" << ScreenDesigner::Line(60, '-') << endl;
	cout << "\t\tUpdate Users Info Screen" << endl;
	cout << ScreenDesigner::Line(60, '-') << endl;
}
void FindUsersScreen()
{
	cout << "\n" << ScreenDesigner::Line(50, '-') << endl;
	cout << "\t\tFind Users Screen" << endl;
	cout << ScreenDesigner::Line(50, '-') << endl;
}
void LoginScreen()
{
	cout << "\n" << ScreenDesigner::Line(60, '-') << endl;
	cout << "\t\t\tLogin Screen" << endl;
	cout << ScreenDesigner::Line(60, '-') << endl;
}
void AccessDeniedMessage()
{
	cout << "\n" << ScreenDesigner::Line(40, '-') << endl;
	cout << "Access Denied,\n";
	cout << "You Dont Have Permmision To Do This,\n";
	cout << "Please Conact Your Admin.\n";
	cout << ScreenDesigner::Line(40, '-') << endl;
}
string ConvertClientsRecordToLine(stClient Client, string delimiter = "#//#")
{
	string S = "";
	S += Client.AccountNumber + delimiter;
	S += Client.PinCode + delimiter;
	S += Client.Name + delimiter;
	S += Client.Phone + delimiter;
	S += to_string(Client.AccountBalance);
	return S;
}
stClient ConvertLineToClientsRecord(string Line, string delimiter = "#//#")
{
	vector<string> VClient = Text::SplitString(Line, delimiter);
	stClient Client;
	Client.AccountNumber = VClient[0];
	Client.PinCode = VClient[1];
	Client.Name = VClient[2];
	Client.Phone = VClient[3];
	Client.AccountBalance = stod(VClient[4]);
	return Client;
}
void AddRecordToFile(string FileName, string Line)
{
	fstream File;
	File.open(FileName, ios::out | ios::app);
	if (File.is_open())
	{
		File << Line << endl;
		File.close();
	}
}
vector<stClient> LoadCleintsDataFromFile(string FileName)
{
	vector<stClient> VClientsData;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line = "";
		while (getline(File, Line))
		{
			VClientsData.push_back(ConvertLineToClientsRecord(Line));
		}
		File.close();
	}
	return VClientsData;
}
stClient ReadNewClientData()
{
	stClient Client;
	Client.AccountNumber = Text::ReadText("Enter Account Number?");
	Client.PinCode = Text::ReadText("Enter PinCode?");
	Client.Name = Text::ReadText("Enter Client Name?");
	Client.Phone = Text::ReadText("Enter Phone Number?");
	Client.AccountBalance = Numbers::ReadPositiveNumber<double>("Enter AccountBalance?");

	return Client;
}
void DisplayClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << string(40, '-') << endl;
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "PinCode: " << Client.PinCode << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Phone: " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << string(40, '-') << endl;
}
string ConvertUsersRecordToLine(stUser User, string delimiter = "#//#")
{
	string S = "";
	S += User.Name + delimiter;
	S += User.Password + delimiter;
	S += to_string(User.Permissions);
	return S;
}
stUser ConvertLineToUsersRecord(string Line, string delimiter = "#//#")
{
	vector<string> VUsers = Text::SplitString(Line, delimiter);
	stUser User;
	User.Name = VUsers[0];
	User.Password = VUsers[1];
	User.Permissions = stoi(VUsers[2]);
	return User;
}
vector<stUser> LoadUsersDataFromFile(string FileName)
{
	vector<stUser> VUsersData;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line = "";
		while (getline(File, Line))
		{
			VUsersData.push_back(ConvertLineToUsersRecord(Line));
		}
		File.close();
	}
	return VUsersData;
}
void DisplayUserCard(stUser User)
{
	cout << "\nThe following are the user details:\n";
	cout << string(40, '-') << endl;
	cout << "Username    : " << User.Name << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissions << endl;
	cout << string(40, '-') << endl;
}
stUser ReadUserInfo()
{
	stUser User;
	User.Name = Text::ReadText("Enter Username? ");
	User.Password = Text::ReadText("Enter Password? ");

	return User;
}
bool UserExistByUserNameAndPassword(string FileName, string Username, string Password, stUser& User)
{
	vector<stUser>VUsers = LoadUsersDataFromFile(FileName);
	for (stUser& U : VUsers)
	{
		if (U.Name == Username && U.Password == Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}
//-1-1-1-1-1-1-1-1-1-1-1-1-1-1-1
bool CheckPemissions(enUserPermissions Permission)
{
	if (Permission == enUserPermissions::pAll)
		return true;
	if ((Permission & CurrentUser.Permissions) == Permission)
	{
		return true;
	}
	else
		return false;
}
//000000000000000000000000000000000
void PrintClientRecord(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.Phone;
	cout << "| " << setw(10) << left << Client.AccountBalance << endl;
}
void PrintAllClientsData()
{
	if (!CheckPemissions(enUserPermissions::pListClients))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}
	system("cls");
	vector<stClient> VClientsData = LoadCleintsDataFromFile(ClientsFile);
	cout << "\n\t\t\t\t\tClient List (" << VClientsData.size() << ") Client(s)." << endl;
	cout << string(120, '-') << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(14) << "Phone";
	cout << "| " << left << setw(10) << "Balance" << endl;
	cout << string(120, '-') << endl;
	for (stClient Client : VClientsData)
	{
		PrintClientRecord(Client);
	}
	cout << string(120, '-') << endl << endl;
	Sounds::OperationCompleteSound();
}
void ShowAllClients()
{
	system("cls");
	PrintAllClientsData();
	GoBackToMainMenue();
}
void PrintUsersData(stUser User)
{
	cout << "| " << setw(51) << left << User.Name;
	cout << "| " << setw(20) << left << User.Password;
	cout << "| " << setw(18) << left << User.Permissions << endl;
}
void PrintAllUsersInfo()
{
	vector<stUser> VUsersData = LoadUsersDataFromFile(UsersFile);
	if (VUsersData.size() == 0)
	{
		cout << "There is no users\n";
	}
	else
	{
		cout << "\n\t\t\t\t\tUser List (" << VUsersData.size() << ") User(s)." << endl;
		cout << string(120, '-') << endl;
		cout << "| " << left << setw(51) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(18) << "Permissions" << endl;
		cout << string(120, '-') << endl;
		for (stUser User : VUsersData)
		{
			PrintUsersData(User);
		}
		cout << string(120, '-') << endl << endl;
	}
}
void PrintAllUsers()
{
	system("cls");
	PrintAllUsersInfo();
	GoBackToManageUsersMenue();
}
//111111111111111111111111111111111
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	stClient Client;
	vector<stClient>VClient;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			Client = ConvertLineToClientsRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				File.close();
				return true;
			}
			VClient.push_back(Client);
		}
		File.close();
	}
	return false;
}
stClient ReadNewClientInfo(string AccountNumber)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;
	Client.PinCode = Text::ReadText("Enter PinCode?");
	Client.Name = Text::ReadText("Enter Client Name?");
	Client.Phone = Text::ReadText("Enter Phone Number?");
	Client.AccountBalance = Numbers::ReadPositiveNumber<double>("Enter AccountBalance?");
	cout << endl;
	return Client;
}
stClient ReadNewClient()
{
	stClient Client;
	Client.AccountNumber = Text::ReadText("Enter Account Number?");
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFile))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with [" << Client.AccountNumber << "] already exsist, ";
		Client.AccountNumber = Text::ReadText("Enter another Account Number?");
	}
	Client = ReadNewClientInfo(Client.AccountNumber);

	return Client;
}
void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddRecordToFile(ClientsFile, ConvertClientsRecordToLine(Client));
}
void AddNewClients()
{
	if (!CheckPemissions(enUserPermissions::pNewClients))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		return;
	}
	char Answer = 'y';
	while (tolower(Answer) == 'y')
	{
		system("cls");
		AddNewClientsScreen();
		cout << "Adding New Client\n\n";
		AddNewClient();
		Sounds::OperationCompleteSound();
		cout << "Client Added successfully, do want to add more clients Y/N ? ";
		cin >> Answer;
		Sounds::KeypressConfirmation();
	}

}
void NewClients()
{
	system("cls");
	AddNewClients();
	GoBackToMainMenue();
}
int PermissionsToSet()
{
	int Permissions = 0;
	char Ans = 'Y';
	cout << "Do you want to give full access ";
	cin >> Ans;
	Sounds::KeypressConfirmation();
	if (toupper(Ans) == 'Y')
		return -1;
	else
	{
		cout << "\n\nDo you want to give access to : \n";
		cout << "\nShow Clients List? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pListClients;
		cout << "\nAdd New Clients? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pNewClients;
		cout << "\nDelete Client? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pDeleteClients;
		cout << "\nUpdate Client? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pUpdateClients;
		cout << "\nFind Client? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pFindClients;
		cout << "\nTransactions? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pTransactions;
		cout << "\nManage Users? (y/n) ";
		cin >> Ans;
		Sounds::KeypressConfirmation();
		if (toupper(Ans) == 'Y')
			Permissions += enUserPermissions::pManageUsers;
	}
	return Permissions;
}
bool UserExistsByUserName(string UserName, string FileName)
{
	stUser User;
	vector<stUser>VUser;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			if (Line != "")
			{
				User = ConvertLineToUsersRecord(Line);
				if (User.Name == UserName)
				{
					File.close();
					return true;
				}
				VUser.push_back(User);
			}
		}
		File.close();
	}
	return false;
}
stUser ReadNewUserInfo(string UserName)
{
	stUser User;
	User.Name = UserName;
	User.Password = Text::ReadText("Enter Password?");
	User.Permissions = PermissionsToSet();
	cout << endl;
	return User;
}
stUser ReadNewUser()
{
	stUser User;
	User.Name = Text::ReadText("Enter Username?");
	while (UserExistsByUserName(User.Name, UsersFile))
	{
		Sounds::OperationDeclinedSound();
		cout << "User with [" << User.Name << "] already exsist, ";
		User.Name = Text::ReadText("Enter another Username?");
	}
	User = ReadNewUserInfo(User.Name);

	return User;
}
void AddNewUser()
{
	stUser User;
	User = ReadNewUser();
	AddRecordToFile(UsersFile, ConvertUsersRecordToLine(User));
}
void AddNewUsers()
{
	char Answer = 'y';
	while (tolower(Answer) == 'y')
	{
		system("cls");
		AddNewUsersScreen();
		cout << "Adding New User\n\n";
		AddNewUser();
		Sounds::OperationCompleteSound();
		cout << "User Added successfully, do want to add more Users Y/N ? ";
		cin >> Answer;
		Sounds::KeypressConfirmation();
	}
}
void AddNewUsersProgram()
{
	system("cls");
	AddNewUsers();
	GoBackToManageUsersMenue();
}
//22222222222222222222222222222
bool FindClientByAccountNumber(string FileName, string AccountNumber, stClient& Client)
{
	vector<stClient> VClientsData = LoadCleintsDataFromFile(FileName);
	for (stClient& C : VClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
bool MarkClientForDelete(string AccountNumber, vector<stClient>& VClientsData)
{
	for (stClient& C : VClientsData)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void DeleteClientRecordFromFile(string FileName, vector<stClient> VClientsData)
{
	fstream File;
	string ClientData = "";
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (stClient& C : VClientsData)
		{
			if (C.MarkForDelete == false)
			{
				ClientData = ConvertClientsRecordToLine(C);
				File << ClientData << endl;
			}
		}
		File.close();
	}
}
bool DeleteClientByAccountNumber(string FileName, string AccountNumber, vector<stClient>& VClientsData)
{
	char Answer = 'n';
	stClient Client;
	if (!FindClientByAccountNumber(ClientsFile, AccountNumber, Client))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with Account Number [" << AccountNumber << "] is not found " << endl;
		return false;
	}
	else
	{
		DisplayClientCard(Client);
		cout << "\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		Sounds::KeypressConfirmation();
		if (toupper(Answer) == 'Y')
		{
			MarkClientForDelete(AccountNumber, VClientsData);
			DeleteClientRecordFromFile(FileName, VClientsData);
			VClientsData = LoadCleintsDataFromFile(FileName);
			cout << "\nClient Deleted Successfully.\n";
			Sounds::OperationCompleteSound();
			return true;
		}
	}

}
void DeleteClientScreen()
{
	if (!CheckPemissions(enUserPermissions::pDeleteClients))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}
	vector<stClient> VClientsData = LoadCleintsDataFromFile(ClientsFile);
	DeleteClientsScreen();
	string AccountNumber = Text::ReadText("Enter Client Account Number");
	DeleteClientByAccountNumber(ClientsFile, AccountNumber, VClientsData);
}
void DeleteClient()
{
	system("cls");
	DeleteClientScreen();
	GoBackToMainMenue();
}
bool FindUserByUsername(string FileName, string Username, stUser& User)
{
	vector<stUser> VUsersData = LoadUsersDataFromFile(FileName);
	for (stUser& U : VUsersData)
	{
		if (U.Name == Username)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool MarkUserForDelete(string Username, vector<stUser>& VUsersData)
{
	for (stUser& U : VUsersData)
	{
		if (U.Name == Username)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void DeleteUserRecordFromFile(string FileName, vector<stUser> VUsersData)
{
	fstream File;
	string UserData = "";
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (stUser& U : VUsersData)
		{
			if (U.MarkForDelete == false)
			{
				UserData = ConvertUsersRecordToLine(U);
				File << UserData << endl;
			}
		}
		File.close();
	}
}
bool DeleteUserByUsername(string FileName, string Username, vector<stUser>& VUsersData)
{
	char Answer = 'n';
	stUser User;
	if (Username == "Admin")
	{
		cout << "\nYou Cannot Delete This User\n";
		return false;
	}
	if (!FindUserByUsername(UsersFile, Username, User))
	{
		Sounds::OperationDeclinedSound();
		cout << "User with username [" << Username << "] is not found " << endl;
		return false;
	}
	else
	{
		DisplayUserCard(User);
		cout << "\nAre you sure you want delete this User? y/n ? ";
		cin >> Answer;
		Sounds::KeypressConfirmation();
		if (toupper(Answer) == 'Y')
		{
			MarkUserForDelete(Username, VUsersData);
			DeleteUserRecordFromFile(FileName, VUsersData);
			VUsersData = LoadUsersDataFromFile(FileName);
			cout << "\nUser Deleted Successfully.\n";
			Sounds::OperationCompleteSound();
			return true;
		}
	}

}
bool DeleteUserScreen()
{
	vector<stUser> VUsersData = LoadUsersDataFromFile(UsersFile);
	DeleteUsersScreen();
	string Username = Text::ReadText("Enter Username");
	DeleteUserByUsername(UsersFile, Username, VUsersData);
	return true;
}
void DeleteUser()
{
	system("cls");
	DeleteUserScreen();
	GoBackToManageUsersMenue();
}
//333333333333333333333333333333
void SaveClientRecordToFile(string FileName, vector<stClient> VClientsData)
{
	fstream File;
	string ClientData = "";
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (stClient& C : VClientsData)
		{
			if (C.MarkForDelete == false)
			{
				ClientData = ConvertClientsRecordToLine(C);
				File << ClientData << endl;
			}
		}
		File.close();
	}
}

stClient ReadUpdatedClientInfo(string AccountNumber)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;
	Client.PinCode = Text::ReadText("Enter PinCode?");
	Client.Name = Text::ReadText("Enter Client Name?");
	Client.Phone = Text::ReadText("Enter Phone Number?");
	Client.AccountBalance = Numbers::ReadPositiveNumber<double>("Enter AccountBalance?");
	cout << endl;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& VClientsData)
{
	char Answer = 'n';
	stClient Client;

	if (!FindClientByAccountNumber(ClientsFile, AccountNumber, Client))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with Account Number [" << AccountNumber << "] is not found " << endl;
		return false;
	}
	else
	{
		DisplayClientCard(Client);
		cout << "\nAre you sure you want to update this client info? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : VClientsData)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadUpdatedClientInfo(AccountNumber);
					break;
				}
			}
			SaveClientRecordToFile(ClientsFile, VClientsData);
			cout << "\nClient Updated Successfully.\n";
			Sounds::OperationCompleteSound();
			return true;
		}
	}
}
void UpdateClientScreen()
{
	if (!CheckPemissions(enUserPermissions::pUpdateClients))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}
	vector<stClient> VClientsData = LoadCleintsDataFromFile(ClientsFile);
	UpdateClientsInfoScreen();
	string AccountNumber = Text::ReadText("Enter Client Account Number");
	UpdateClientByAccountNumber(AccountNumber, VClientsData);
}
void UpdateClient()
{
	system("cls");
	UpdateClientScreen();
	GoBackToMainMenue();
}
void SaveUsersRecordToFile(string FileName, vector<stUser> VUsersData)
{
	fstream File;
	string UserData = "";
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (stUser& C : VUsersData)
		{
			if (C.MarkForDelete == false)
			{
				UserData = ConvertUsersRecordToLine(C);
				File << UserData << endl;
			}
		}
		File.close();
	}
}
stUser ReadUpdatedUserInfo(string Username)
{
	stUser User;
	User.Name = Username;
	User.Password = Text::ReadText("Enter Password?");
	User.Permissions = PermissionsToSet();
	cout << endl;
	return User;
}
bool UpdateUserByUsername(string Username, vector<stUser>& VUsersData)
{
	char Answer = 'n';
	stUser User;
	if (Username == "Admin")
	{
		cout << "\nYou Cannot Update This User\n";
		return false;
	}
	if (!FindUserByUsername(UsersFile, Username, User))
	{
		Sounds::OperationDeclinedSound();
		cout << "User with Account Number [" << Username << "] is not found " << endl;
		return false;
	}
	else
	{
		DisplayUserCard(User);
		cout << "\nAre you sure you want to update this User info? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (stUser& U : VUsersData)
			{
				if (U.Name == Username)
				{
					U = ReadUpdatedUserInfo(Username);
					break;
				}
			}
			SaveUsersRecordToFile(UsersFile, VUsersData);
			cout << "\nUser Updated Successfully.\n";
			Sounds::OperationCompleteSound();
			return true;
		}
	}
}
bool UpdateUserScreen()
{
	vector<stUser> VUsersData = LoadUsersDataFromFile(UsersFile);
	UpdateUsersInfoScreen();
	string Username = Text::ReadText("Enter a Username");
	UpdateUserByUsername(Username, VUsersData);
	return true;
}
void UpdateUser()
{
	system("cls");
	UpdateUserScreen();
	GoBackToManageUsersMenue();
}
//44444444444444444
void FindClientScreen()
{
	if (!CheckPemissions(enUserPermissions::pFindClients))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}
	FindClientsScreen();
	string AccountNumber = Text::ReadText("Enter Client Account Number");
	stClient Client;
	if (!FindClientByAccountNumber(ClientsFile, AccountNumber, Client))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with Account Number [" << AccountNumber << "] is not found " << endl;
	}
	else
	{
		DisplayClientCard(Client);
		Sounds::OperationCompleteSound();
	}
}
void FindClient()
{
	system("cls");
	FindClientScreen();
	GoBackToMainMenue();
}
bool FindUserScreen()
{
	FindUsersScreen();
	string Username = Text::ReadText("Enter Username");
	stUser User;
	if (!FindUserByUsername(UsersFile, Username, User))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with username [" << Username << "] is not found " << endl;
		return false;
	}
	else
	{
		DisplayUserCard(User);
		Sounds::OperationCompleteSound();
		return true;
	}
}
void FindUser()
{
	system("cls");
	FindUserScreen();
	GoBackToManageUsersMenue();
}
//5555555555555555
void GoBackToTransactionMenue()
{
	cout << "Press any key to go back to Transaction Menu...";
	system("pause>0");
	Sounds::KeypressConfirmation();
	TransactionProgram();
}
void PrintClientAccountBalance(stClient Client)
{
	cout << "| " << setw(21) << left << Client.AccountNumber;
	cout << "| " << setw(50) << left << Client.Name;
	cout << "| " << setw(18) << left << Client.AccountBalance << endl;
}
void PrintAllClientsAccountBalances()
{
	vector<stClient> VClientsData = LoadCleintsDataFromFile(ClientsFile);
	cout << "\n\t\t\t\t\tClient List (" << VClientsData.size() << ") Client(s)." << endl;
	cout << string(120, '-') << endl;
	cout << "| " << left << setw(21) << "Accout Number";
	cout << "| " << left << setw(50) << "Client Name";
	cout << "| " << left << setw(18) << "Balance" << endl;
	cout << string(120, '-') << endl;
	for (stClient Client : VClientsData)
	{
		PrintClientRecord(Client);
	}
	cout << string(120, '-') << endl << endl;
}
double CalculateToTalBalances()
{
	vector<stClient> VClientsData = LoadCleintsDataFromFile(ClientsFile);
	double Sum = 0;
	for (stClient Client : VClientsData)
	{
		Sum += Client.AccountBalance;
	}

	return Sum;
}
void ToTalBalancesScreen()
{
	PrintAllClientsAccountBalances();
	cout << "\t\t\t\t\t Total Balances = " << CalculateToTalBalances() << endl;
	Sounds::OperationCompleteSound();
}
void ToTalBalances()
{
	system("cls");
	ToTalBalancesScreen();
	GoBackToTransactionMenue();
}
//666666666666666666666666666
bool DepositeBalancetoClient(string AccountNumber, double Ammount, vector<stClient>VClientsData)
{
	char Answer = 'n';
	cout << "Are you sure you want perform this transaction [y/n] ";
	cin >> Answer;
	Sounds::KeypressConfirmation();
	if (toupper(Answer) == 'Y')
	{
		for (stClient& C : VClientsData)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Ammount;
				SaveClientRecordToFile(ClientsFile, VClientsData);
				cout << "Done seccessfully new Balance is: " << C.AccountBalance;
				Sounds::OperationCompleteSound();
				return true;
			}
		}
	}
	return false;
}
void DepositeMonyScreen()
{
	stClient Client;
	vector<stClient> VClient = LoadCleintsDataFromFile(ClientsFile);
	DepositeScreen();
	string AccountNumber = Text::ReadText("Plese enter Account Number");
	while (!FindClientByAccountNumber(ClientsFile, AccountNumber, Client))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with Account [" << AccountNumber << "] does not exist\n";
		AccountNumber = Text::ReadText("Plese enter Account Number");
	}
	DisplayClientCard(Client);
	double Ammount = Numbers::ReadPositiveNumber<double>("Pleas enter deposite ammount? ");
	DepositeBalancetoClient(AccountNumber, Ammount, VClient);
};
void DepositeMony()
{
	system("cls");
	DepositeMonyScreen();
	TransactionProgram();
}
//7777777777777777777777777777777
void WithdrawMonyScreen()
{
	stClient Client;
	vector<stClient> VClient = LoadCleintsDataFromFile(ClientsFile);
	DepositeScreen();
	string AccountNumber = Text::ReadText("Plese enter Account Number");
	while (!FindClientByAccountNumber(ClientsFile, AccountNumber, Client))
	{
		Sounds::OperationDeclinedSound();
		cout << "Client with Account [" << AccountNumber << "] does not exist\n";
		AccountNumber = Text::ReadText("Plese enter Account Number");
	}
	DisplayClientCard(Client);
	double Ammount = Numbers::ReadPositiveNumber<double>("Pleas enter Withdraw ammount? ");
	while (Ammount > Client.AccountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
		Ammount = Numbers::ReadPositiveNumber<double>("Pleas enter Withdraw ammount? ");
	}
	DepositeBalancetoClient(AccountNumber, Ammount * (-1), VClient);
};
void WithdrawMony()
{
	system("cls");
	WithdrawMonyScreen();
	TransactionProgram();
}
//88888888888888888888888
void TransactionProgram()
{
	if (!CheckPemissions(enUserPermissions::pTransactions))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}
	system("cls");
	TransactionsMenueScreen();
	PerformTransactionsMenueOperatoins(ReadTransactionsMenueOperatoins("Choose what do you want to do? [1 to 4]"));
}
void Transaction()
{
	system("cls");
	TransactionProgram();
}
enTransactions ReadTransactionsMenueOperatoins(string message)
{
	int num;
	do
	{
		cout << message << endl;
		cin >> num;
		if (cin.fail() || (num > 4 || num < 1))
		{
			Sounds::WarningSound();
			cin.clear();
			cin.ignore(1000000000, '\n');
		}
		else
			Sounds::KeypressConfirmation();
	} while (num <= 0);
	return (enTransactions)num;
}
void PerformTransactionsMenueOperatoins(enTransactions Transactions)
{
	switch (Transactions)
	{
	case::Deposite:
		DepositeMony();
		break;
	case::Withdraw:
		WithdrawMony();
		break;
	case::TotalBalances:
		ToTalBalances();
		break;
	case::MainMenue:
		BankProgram();
		break;
	default:
		cout << "Invalid Choice \n\n";
	}
}
void PerfromManageUsersMenueOption(enUsers ManageUsersMenueOption)
{
	switch (ManageUsersMenueOption) 
	{
	case enUsers::uList:  
	{  
		PrintAllUsers();
		break;
	} 
	case enUsers::uNew : 
	{   

		AddNewUsersProgram();
		break; 
	} case enUsers::uDelete : 
	{    
		DeleteUser();
		break; 
	} case enUsers::uUpdate : {
		UpdateUser();
		break;
	} case enUsers::uFind:
	{   
		FindUser();
		break;
	}
		case enUsers::uMainMenue : 
	{ 
			BankProgram();
			break;
	}
	}
}
enUsers ReadManageUsersMenueOption(string message)
{ 
	int num;
	do
	{
		cout << message << endl;
		cin >> num;
		if (cin.fail() || (num > 6 || num < 1))
		{
			Sounds::WarningSound();
			cin.clear();
			cin.ignore(1000000000, '\n');
		}
		else
			Sounds::KeypressConfirmation();
	} while (num <= 0);
	return (enUsers)num;
} void ManageUsersProgram() 
{

	system("cls"); 
	if (!CheckPemissions(enUserPermissions::pManageUsers))
	{
		AccessDeniedMessage();
		Sounds::OperationDeclinedSound();
		GoBackToMainMenue();
		return;
	}     
	ManageUsersMenueScreen();
	PerfromManageUsersMenueOption(ReadManageUsersMenueOption("Choose what do you want to do? [1 to 6]"));
} 
void GoBackToManageUsersMenue() 
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ManageUsersProgram(); 
}
void GoBackToMainMenue()
{
	cout << "Press any key to go back to Main Menu...";
	system("pause>0");
	Sounds::KeypressConfirmation();
	BankProgram();
}
enBank ReadMainMenueOperatoins(string message)
{
	int num;
	do
	{
		cout << message << endl;
		cin >> num;
		if (cin.fail() || (num > 8 || num < 1))
		{
			Sounds::WarningSound();
			cin.clear();
			cin.ignore(1000000000, '\n');
		}
		else
			Sounds::KeypressConfirmation();
	} while (num <= 0);
	return (enBank)num;
}
void PerformMainMenueOperatoins(enBank bank)
{
	switch (bank)
	{
	case::List:
		ShowAllClients();
		break;
	case::New:
		NewClients();
		break;
	case::Delete:
		DeleteClient();
		break;
	case::Update:
		UpdateClient();
		break;
	case::Find:
		FindClient();
		break;
	case::Transactions:
		Transaction();
		break;
	case::ManageUsers:
		ManageUsersProgram();
		break;
	case::Exit:
		system("cls");
		BankAplication();
		break;
	default:
		cout << "Invalid Choice \n\n";
	}
}
void BankProgram()
{
	system("cls");
	MainMenueScreen();
	PerformMainMenueOperatoins(ReadMainMenueOperatoins("Choose what do you want to do? [1 to 8]"));
}
bool  LoadUserInfo(string Username, string Password)
{
 if (UserExistByUserNameAndPassword(UsersFile,Username, Password, CurrentUser))
	 return true;
 else 
	 return false; 
}
void BankAplication()
{
	bool LoginFaild = false;
	stUser User;
	do
	{
		system("cls");
		LoginScreen();
		if (LoginFaild)
		{
			cout << "Invalid Username/Password!\n";
		}
		User = ReadUserInfo();

		LoginFaild = !LoadUserInfo(User.Name, User.Password);
	} while (LoginFaild);
	BankProgram();
}
int main()
{
	BankAplication();
	return 0;
}