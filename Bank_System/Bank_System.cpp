#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>


// constants

const std::string SEPARATOR = " /##/ ";

const int CLIENT_NOT_FOUND = -1;
const int USER_NOT_FOUND = -99;


namespace file {

    const std::string CLIENTS_FILE = "CLIENTS.txt";
    const std::string USERS_FILE = "USERS.txt";
}

namespace menu {

    const std::string MAIN = "Main Menu";
    const std::string TRANSACTIONS = "Transactions Menu";
    const std::string MANAGE_USERS = "Manage Users Menu";
}


// types (enums & structs)

enum eMainMenu {

    ADD_CLIENT = 1,
    SHOW_ALL_CLIENTS = 2,
    UPDATE_CLIENT = 3,
    REMOVE_CLIENT = 4,
    FIND_CLIENT = 5,
    TRANSACTIONS = 6,
    MANAGE_USERS = 7,
    LOGOUT = 8,
};

enum eTransactionsMenu {

    DEPOSIT = 1,
    WITHDRAW = 2,
    SHOW_ALL_BALANCES = 3,
    RETURN_TO_MAIN_MENU = 4,
};

enum eManageUsersMenu {

    ADD_NEW_USER = 1,
    LIST_USERS = 2,
    UPDATE_USER = 3,
    REMOVE_USER = 4,
    FIND_USER = 5,
    uRETURN_TO_MAIN_MENU = 6,
};

enum ePermissions {

    FULL_ACCESS = -1,
    ALLOW_ADD_CLIENT = 1,
    ALLOW_SHOW_ALL_CLIENTS = 2,
    ALLOW_UPDATE_CLIENT = 4,
    ALLOW_REMOVE_CLIENT = 8,
    ALLOW_FIND_CLIENT = 16,
    ALLOW_TRANSACTIONS = 32,
    ALLOW_MANAGE_USERS = 64,
};


struct sClient {

    std::string accountNum = "";
    int pincode = 0;
    std::string name = "";
    std::string phoneNum = "";
    float balance = 0;
    bool isDeleted = false;
};

struct sUser {

    std::string name = "";
    int password = 0;
    int permissions = 0;
    bool isDeleted = false;
};


// utility functions (declaration)

float readNum(const std::string& msg, const std::string& sep = " ");

float readNumInRange(const std::string& msg, float min, float max, const std::string& sep = " ");

float readPositiveNum(const std::string& msg, const std::string& sep = " ");

std::string readText(const std::string& msg, const std::string& sep = " ");

char readChar(const std::string& msg, const std::string& sep = " ");

std::vector <std::string> splitText(const std::string& text, const std::string& sep);

void clearScreen();

bool addLineToFile(const std::string& line, const std::string& fileName);


// input functions (declaration)

int readMenuChoice(int firstChoice, int lastChoice, const std::string& msg = "Enter your choice:");

std::string readAccountNum(const std::string& msg = "Enter account number:");

sClient readClientData(const std::vector <sClient>& vClients);

sUser readUserData(const std::vector <sUser>& vUsers);

void readUpdatedClientData(sClient& client);

std::string readUsername(const std::string& msg = "Enter username:");

int readPermissionsToSet();


// helper functions (declaration)

void addClient(const std::vector <sClient>& vClients);

int getClientIndex(const std::string& accountNum, const std::vector <sClient>& vClients);

sClient clientLineToRecord(const std::string& line);

sUser userLineToRecord(const std::string& line);

std::string clientRecordToLine(const sClient& client);

void returnToMenu(const std::string& menu = menu::MAIN);

void processUpdating(const std::string& accountNum, std::vector <sClient>& vClients);

void processRemoving(const std::string& accountNum, std::vector <sClient>& vClients);

void processRemoving(int index, std::vector <sUser>& vUsers);

void processUpdating(int index, std::vector <sUser> vUsers);

bool confirmTransaction(int depositAmount, float& balance, bool isDeposit = true);

bool isClientExistsByIndex(int index);

bool isUserExistsByIndex(int index);

std::string userRecordToLine(const sUser& user);

int getUserIndexByName(const std::string& username, const std::vector <sUser>& vUsers);

int getUserIndexByNameAndPassword(const std::string& username, int password, const std::vector <sUser>& vUsers);

void processDeposit(int index, std::vector <sClient>& vClients);

void processWithdraw(int index, std::vector <sClient>& vClients);

bool isAllowedPermission(int permissions, ePermissions permissionToCheck);


// output functions (declaration)

void printMainMenu();

void printClientsListHeader(int numOfClients);

void printClientRecord(const sClient& client);

void printClientCard(const sClient& client);

void printClientNotFound(const std::string& accountNum);

void printTransactionsMenu();

void printBalancesListHeader(int numOfClients);

void printManageUsersMenu();

void printUsersListHeader(int numOfUsers);

void printUserCard(const sUser& user);

void printUserNotFound(const std::string& username);

void printAccessDenied();


// data functions (declaration)

std::vector <sClient> loadClientsFromFile();

std::vector <sUser> loadUsersFromFile();

void saveClientsToFile(const std::vector <sClient> vClients);

void saveUsersToFile(const std::vector <sUser> vUsers);


// core functions (declaration)

void addClients(sUser& user);

void showAllClients(const sUser& user);

void updateClient(const sUser& user);

void removeClient(const sUser& user);

void findClient(const sUser& user);

void Deposit();

void Withdraw();

void showAllBalances();

void applyTransaction(eTransactionsMenu choice);

void Transactions(const sUser& user);

void addUser(const std::vector <sUser>& vUsers);

void addUsers();

void showAllUsers();

void updateUser();

void removeUser();

void findUser();

void applyMainMenuChoice(eMainMenu choice, sUser& user);

void applyManageUsersMenuChoice(eManageUsersMenu choice);

void manageUsers(const sUser& user);

void startProgram(sUser& user);

void Login();



// utility functions (definition)

float readNum(const std::string& msg, const std::string& sep) {

    float num;

    std::cout << msg << sep;
    std::cin >> num;

    while (std::cin.fail()) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid Number! Enter a valid number:" << sep;
        std::cin >> num;
    }

    return num;
}

float readNumInRange(const std::string& msg, float min, float max, const std::string& sep) {

    float num;

    do {

        num = readNum(msg, sep);

    } while (num < min || num > max);

    return num;
}

float readPositiveNum(const std::string& msg, const std::string& sep) {

    float num;

    do {

        num = readNum(msg, sep);

    } while (num < 1);

    return num;
}

std::string readText(const std::string& msg, const std::string& sep) {

    std::string text;

    std::cout << msg << sep;
    std::getline(std::cin >> std::ws, text);

    return text;
}

char readChar(const std::string& msg, const std::string& sep) {

    char character;

    std::cout << msg << sep;
    std::cin >> character;

    return character;
}

std::vector <std::string> splitText(const std::string& text, const std::string& sep) {

    int wordPos = 0;
    int sepPos;

    std::string word;
    std::vector <std::string> vWords;

    while ((sepPos = text.find(sep, wordPos)) != std::string::npos) {

        word = text.substr(wordPos, sepPos - wordPos);

        if (!word.empty())
            vWords.push_back(word);

        wordPos = sepPos + sep.length();
    }

    if (wordPos < text.length())
        vWords.push_back(text.substr(wordPos));

    return vWords;
}

void clearScreen() {

    system("cls");
}

bool addLineToFile(const std::string& line, const std::string& fileName) {

    std::fstream file;

    file.open(fileName, std::ios::app);

    if (file.is_open()) {

        file << line << '\n';

        file.close();

        return true;
    }

    else
        return false;
}


// input functions (definition)

int readMenuChoice(int firstChoice, int lastChoice, const std::string& msg) {

    return readNumInRange(msg, firstChoice, lastChoice);
}

std::string readAccountNum(const std::string& msg) {

    return readText(msg);
}

sClient readClientData(const std::vector <sClient>& vClients) {

    sClient client;

    client.accountNum = readAccountNum();
    int index = getClientIndex(client.accountNum, vClients);

    while (!isClientExistsByIndex(index)) {

        std::cout << "\nClient with account number [" << client.accountNum << "] is already added, ";
        client.accountNum = readAccountNum();
    }

    client.pincode = readPositiveNum("Enter pincode:");
    client.name = readText("Enter client name:");
    client.phoneNum = readText("Enter phone number:");
    client.balance = readPositiveNum("Enter balance:", " $");

    return client;
}

void readUpdatedClientData(sClient& client) {

    client.pincode = readPositiveNum("Enter new pincode:");
    client.name = readText("Enter new client name:");
    client.phoneNum = readText("Enter new phone number:");
    client.balance = readPositiveNum("Enter new balance: ", "$");
}

std::string readUsername(const std::string& msg) {

    return readText(msg);
}

void readCheckAddPermission(const std::string& permissionToCheck, int& permissions, ePermissions allowedPermission) {

    char permission = readChar(permissionToCheck + " (Y/N): ");

    if (toupper(permission) == 'Y')
        permissions |= allowedPermission;
}

int readPermissionsToSet() {

    char fullAccess = readChar("\nDo you want to give him full access (Y/N):");

    if (toupper(fullAccess) != 'Y') {

        int permissions = 0;
        

        readCheckAddPermission("\nAdd New Client", permissions, ePermissions::ALLOW_ADD_CLIENT);

        readCheckAddPermission("Show All Clients", permissions, ePermissions::ALLOW_SHOW_ALL_CLIENTS);

        readCheckAddPermission("Update Client", permissions, ePermissions::ALLOW_UPDATE_CLIENT);

        readCheckAddPermission("Remove Client", permissions, ePermissions::ALLOW_REMOVE_CLIENT);

        readCheckAddPermission("Find Client", permissions, ePermissions::ALLOW_FIND_CLIENT);

        readCheckAddPermission("Transactions", permissions, ePermissions::ALLOW_TRANSACTIONS);

        readCheckAddPermission("Manage Users", permissions, ePermissions::ALLOW_MANAGE_USERS);


        return permissions;
    }

    return ePermissions::FULL_ACCESS;
}

sUser readUserData(const std::vector <sUser>& vUsers) {

    sUser user;

    user.name = readUsername();
    int index = getUserIndexByName(user.name, vUsers);

    while ((isUserExistsByIndex(index))) {

        std::cout << "\nUser is already added, ";
        user.name = readUsername("Enter a valid username:");
    }

    user.password = readPositiveNum("Enter password:");
    user.permissions = readPermissionsToSet();

    return user;
}


// helper functions (definition)

void addClient(const std::vector <sClient>& vClients) {

    sClient client = readClientData(vClients);
    addLineToFile(clientRecordToLine(client), file::CLIENTS_FILE);
}

int getClientIndex(const std::string& accountNum, const std::vector <sClient>& vClients) {

    int index = 0;

    for (const sClient& client : vClients) {

        if (client.accountNum != accountNum)
            index++;

        else
            return index;
    }

    return CLIENT_NOT_FOUND;
}

sClient clientLineToRecord(const std::string& line) {

    std::vector <std::string> vRecord = splitText(line, SEPARATOR);

    sClient client;

    client.accountNum = vRecord[0];
    client.pincode = std::stoi(vRecord[1]);
    client.name = vRecord[2];
    client.phoneNum = vRecord[3];
    client.balance = std::stod(vRecord[4]);

    return client;
}

sUser userLineToRecord(const std::string& line) {

    std::vector <std::string> vUser = splitText(line, SEPARATOR);

    sUser user;

    user.name = vUser[0];
    user.password = std::stoi(vUser[1]);
    user.permissions = std::stoi(vUser[2]);

    return user;
}

std::string clientRecordToLine(const sClient& client) {

    std::string line = "";

    line += client.accountNum + SEPARATOR;
    line += std::to_string(client.pincode) + SEPARATOR;
    line += client.name + SEPARATOR;
    line += client.phoneNum + SEPARATOR;
    line += std::to_string(client.balance);

    return line;
}

std::string userRecordToLine(const sUser& user) {

    std::string line = "";

    line += user.name + SEPARATOR;
    line += std::to_string(user.password) + SEPARATOR;
    line += std::to_string(user.permissions);

    return line;
}

void returnToMenu(const std::string& menu) {

    std::cout << "\nPress any key to return to " << menu << "...";
    system("pause>0");

    clearScreen();
}

void processUpdating(const std::string& accountNum, std::vector <sClient>& vClients) {

    int index = getClientIndex(accountNum, vClients);

    if (isClientExistsByIndex(index)) {

        printClientCard(vClients[index]);

        char sureToUpdate = readChar("\nAre you sure you want to update client data (Y/N):");

        if (toupper(sureToUpdate) == 'Y') {

            std::cout << '\n';

            readUpdatedClientData(vClients[index]);
            saveClientsToFile(vClients);
        }
    }

    else
        printClientNotFound(accountNum);
}

void processRemoving(const std::string& accountNum, std::vector <sClient>& vClients) {

    int index = getClientIndex(accountNum, vClients);

    if (isClientExistsByIndex(index)) {

        printClientCard(vClients[index]);

        char sureToUpdate = readChar("\nAre you sure you want to remove client (Y/N):");

        if (toupper(sureToUpdate) == 'Y') {

            vClients[index].isDeleted = true;
            saveClientsToFile(vClients);
            vClients = loadClientsFromFile();
        }
    }

    else
        printClientNotFound(accountNum);
}

bool confirmTransaction(int amount, float& balance, bool isDeposit) {

    char confirm = readChar("Are you sure you want to do this transaction (Y/N):");

    if (toupper(confirm) == 'Y') {
        
        if (!isDeposit)
            amount *= -1;

        balance += amount;


        std::cout << "\nNew Account Balance: $" << balance << '\n';

        return true;
    }

    return false;
}

bool isClientExistsByIndex(int index) {

    return (index != CLIENT_NOT_FOUND);
}

bool isUserExistsByIndex(int index) {

    return (index != USER_NOT_FOUND);
}

int getUserIndexByName(const std::string& username, const std::vector <sUser>& vUsers) {

    int index = 0;

    for (const sUser& user : vUsers) {

        if (user.name != username)
            index++;

        else
            return index;
    }

    return USER_NOT_FOUND;
}

void processRemoving(int index, std::vector <sUser>& vUsers) {

    if (isUserExistsByIndex(index)) {

        if (vUsers[index].permissions == ePermissions::FULL_ACCESS)
            std::cout << "\nYou can't delete this user\n";

        else {

            printUserCard(vUsers[index]);

            char sureToDelete = readChar("\nAre you sure you want to delete this user (Y/N):");

            if (toupper(sureToDelete) == 'Y') {

                vUsers[index].isDeleted = true;
                saveUsersToFile(vUsers);
                vUsers = loadUsersFromFile();

                std::cout << "\nUser Deleted Successfully!\n";
            }

            else
                printUserNotFound(vUsers[index].name);
        }

    }
}

void processUpdating(int index, std::vector <sUser> vUsers) {

    if (isUserExistsByIndex(index)) {

        if (vUsers[index].permissions == ePermissions::FULL_ACCESS)
            std::cout << "\nYou can't update info of this user !\n";

        else {

            printUserCard(vUsers[index]);

            char sureToUpdate = readChar("\nAre you sure you want to update this user info (Y/N):");

            vUsers[index].password = readPositiveNum("\nEnter new password:");
            vUsers[index].permissions = readPermissionsToSet();

            saveUsersToFile(vUsers);

            std::cout << "\nUser Updated Successfully\n";
        }
    }

    else
        printUserNotFound(vUsers[index].name);
}

void processDeposit(int index, std::vector <sClient>& vClients) {

    if (isClientExistsByIndex(index)) {

        printClientCard(vClients[index]);

        int depositAmount = readPositiveNum("\nEnter deposit amount:", " $");

        if (confirmTransaction(depositAmount, vClients[index].balance)) {

            saveClientsToFile(vClients);
        }
    }

    else
        printClientNotFound(vClients[index].accountNum);
}

void processWithdraw(int index, std::vector <sClient>& vClients) {

    if (isClientExistsByIndex(index)) {

        printClientCard(vClients[index]);

        int withdrawAmount = readPositiveNum("\nEnter withdraw amount:", " $");

        while (withdrawAmount > vClients[index].balance) {

            std::cout << "\nWithdraw is bigger than account balance\n";
            std::cout << "Your Current Balance: " << vClients[index].balance << '\n';
        }

        if (confirmTransaction(withdrawAmount, vClients[index].balance, false)) {

            saveClientsToFile(vClients);
        }
    }

    else
        printClientNotFound(vClients[index].accountNum);
}

bool isAllowedPermission(int permissions, ePermissions permissionToCheck) {

    return ((permissions & permissionToCheck) == permissionToCheck);
}

int getUserIndexByNameAndPassword(const std::string& username, int password, const std::vector <sUser>& vUsers) {

    int index = 0;

    for (const sUser& user : vUsers) {

        if (user.name != username || user.password != password)
            index++;

        else
            return index;
    }

    return USER_NOT_FOUND;
}


// output functions (definition)

void printMainMenu() {

    std::cout << "=============================\n";
    std::cout << "\tMain Menu\n";
    std::cout << "=============================\n";
    std::cout << "[1] Add New Client\n";
    std::cout << "[2] Show All Clients\n";
    std::cout << "[3] Update Client\n";
    std::cout << "[4] Remove Client\n";
    std::cout << "[5] Find Client\n";
    std::cout << "[6] Transactions\n";
    std::cout << "[7] Manage Users\n";
    std::cout << "[8] Logout\n";
    std::cout << "=============================\n";
}

void printClientsListHeader(int numOfClients) {

    std::cout << '\n' << "\t\t\tClients List [" << numOfClients << "] Client(s)\n";

    std::cout << std::left;
    std::cout << "\n--------------------------------------------------------------------------------------------\n\n";
    std::cout << "| " << std::setw(17) << "Account Number";
    std::cout << "| " << std::setw(10) << "Pincode";
    std::cout << "| " << std::setw(30) << "Client Name";
    std::cout << "| " << std::setw(17) << "Phone Number";
    std::cout << "| " << std::setw(10) << "Balance";
    std::cout << "\n\n--------------------------------------------------------------------------------------------\n";
}

void printClientRecord(const sClient& client) {

    std::cout << "| " << std::setw(17) << client.accountNum;
    std::cout << "| " << std::setw(10) << client.pincode;
    std::cout << "| " << std::setw(30) << client.name;
    std::cout << "| " << std::setw(17) << client.phoneNum;
    std::cout << "| $" << std::setw(10) << client.balance << '\n';
}

void printClientCard(const sClient& client) {

    std::cout << "\nAccount Number: " << client.accountNum;
    std::cout << "\nPincode: " << client.pincode;
    std::cout << "\nClient Name: " << client.name;
    std::cout << "\nPhone Number: " << client.phoneNum;
    std::cout << "\nBalance: $" << client.balance << '\n';
}

void printClientNotFound(const std::string& accountNum) {

    std::cout << "\nClient with account number [" << accountNum << "] isn't founded\n";
}

void printTransactionsMenu() {

    std::cout << "=============================\n";
    std::cout << "\tTransactions Menu\n";
    std::cout << "=============================\n";
    std::cout << "[1] Deposit\n";
    std::cout << "[2] Withdraw\n";
    std::cout << "[3] Show All Balances\n";
    std::cout << "[4] Return To Main Menu\n";
    std::cout << "=============================\n";
}

void printBalancesListHeader(int numOfClients) {

    std::cout << '\n' << "\t\t\tClients List [" << numOfClients << "] Client(s)\n";

    std::cout << std::left;
    std::cout << "\n--------------------------------------------------------------------------------------------\n\n";
    std::cout << "| " << std::setw(17) << "Account Number";
    std::cout << "| " << std::setw(30) << "Client Name";
    std::cout << "| " << std::setw(10) << "Balance";
    std::cout << "\n\n--------------------------------------------------------------------------------------------\n";
}

void printManageUsersMenu() {

    std::cout << "=============================\n";
    std::cout << "\tManage Users Menu\n";
    std::cout << "=============================\n";
    std::cout << "[1] Add New User\n";
    std::cout << "[2] List Users\n";
    std::cout << "[3] Update User\n";
    std::cout << "[4] Remove User\n";
    std::cout << "[5] Find User\n";
    std::cout << "[6] Return to Main Menu\n";
    std::cout << "=============================\n";
}

void printUsersListHeader(int numOfUsers) {

    std::cout << '\n' << "\t\t\tUsers List [" << numOfUsers << "] User(s)\n";

    std::cout << std::left;
    std::cout << "\n--------------------------------------------------------------------------------------------\n\n";
    std::cout << "| " << std::setw(17) << "Username";
    std::cout << "| " << std::setw(20) << "Password";
    std::cout << "| " << std::setw(20) << "Permissions";
    std::cout << "\n\n--------------------------------------------------------------------------------------------\n";
}

void printUserCard(const sUser& user) {

    std::cout << "\nUsername: " << user.name;
    std::cout << "\nPassword: " << user.password;
    std::cout << "\nPermissions: " << user.permissions << '\n';
}

void printUserNotFound(const std::string& username) {

    std::cout << "\nUser with username [" << username << "] is not found!\n";
}

void printAccessDenied() {

    std::cout << "\t\t\t\t\t! Access Denied !\n";
    std::cout << "\t\t\t\t-- Please contact your admin --\n\n";
}


// data functions (definition)

std::vector <sClient> loadClientsFromFile() {

    std::fstream file;

    file.open(file::CLIENTS_FILE, std::ios::in);

    std::vector <sClient> vClients;

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            sClient client = clientLineToRecord(line);
            vClients.push_back(client);
        }

        file.close();
    }

    return vClients;
}

void saveClientsToFile(const std::vector <sClient> vClients) {

    std::fstream file;

    file.open(file::CLIENTS_FILE, std::ios::out);

    if (file.is_open()) {

        for (const sClient& client : vClients) {

            if (client.isDeleted == false) {

                file << clientRecordToLine(client) << '\n';
            }
        }

        file.close();
    }
}

void saveUsersToFile(const std::vector <sUser> vUsers) {

    std::fstream file;

    file.open(file::USERS_FILE, std::ios::out);

    if (file.is_open()) {

        for (const sUser& user : vUsers) {

            if (user.isDeleted == false) {

                file << userRecordToLine(user) << '\n';
            }
        }

        file.close();
    }
}

std::vector <sUser> loadUsersFromFile() {

    std::fstream file;

    file.open(file::USERS_FILE, std::ios::in);

    std::vector <sUser> vUsers;

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            sUser user = userLineToRecord(line);
            vUsers.push_back(user);
        }

        file.close();
    }

    return vUsers;
}


// core functions (definition)

void addClients(sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_ADD_CLIENT)) {

        printAccessDenied();
    }

    else {

        std::cout << "\t\t----------------------------\n";
        std::cout << "\t\t\tAdd New Client\n";
        std::cout << "\t\t----------------------------\n\n";

        std::vector <sClient> vClients = loadClientsFromFile();

        char addOtherClient;

        do {

            std::cout << "\nAdding New Client:\n\n";

            addClient(vClients);

            addOtherClient = readChar("\nDo you want to add another client (Y/N):");

        } while (toupper(addOtherClient) == 'Y');
    }
    

    returnToMenu();
}

void showAllClients(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_SHOW_ALL_CLIENTS)) {

        printAccessDenied();
    }

    else {

        std::cout << "\t\t----------------------------\n";
        std::cout << "\t\t\tShow All Clients\n";
        std::cout << "\t\t----------------------------\n";

        std::vector <sClient> vClients = loadClientsFromFile();

        printClientsListHeader(vClients.size());

        for (const sClient& client : vClients) {

            printClientRecord(client);
        }

        std::cout << "\n-------------------------------------------------------------------------------------------\n";
    }


    returnToMenu();
}

void updateClient(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_UPDATE_CLIENT)) {

        printAccessDenied();
    }

    else {

        std::cout << "\t\t---------------------------\n";
        std::cout << "\t\t\tUpdate Client\n";
        std::cout << "\t\t---------------------------\n\n";

        std::vector <sClient> vClients = loadClientsFromFile();

        std::string accountNum = readAccountNum();

        processUpdating(accountNum, vClients);
    }


    returnToMenu();
}

void removeClient(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_REMOVE_CLIENT)) {

        printAccessDenied();
        returnToMenu();

        return;
    }

    std::cout << "\t\t----------------------------\n";
    std::cout << "\t\t\tRemove Client\n";
    std::cout << "\t\t----------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();

    processRemoving(accountNum, vClients);

    returnToMenu();
}

void findClient(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_FIND_CLIENT)) {

        printAccessDenied();
        returnToMenu();

        return;
    }

    std::cout << "\t\t------------------------\n";
    std::cout << "\t\t\tFind Client\n";
    std::cout << "\t\t------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();

    int index = getClientIndex(accountNum, vClients);

    if (isClientExistsByIndex(index)) {

        printClientCard(vClients[index]);
    }

    else
        printClientNotFound(accountNum);


    returnToMenu();
}

void Deposit() {

    std::cout << "\t\t------------------------\n";
    std::cout << "\t\t\tDeposit\n";
    std::cout << "\t\t------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();
    int index = getClientIndex(accountNum, vClients);

    processDeposit(index, vClients);

    returnToMenu(menu::TRANSACTIONS);
}

void Withdraw() {

    std::cout << "\t\t------------------------\n";
    std::cout << "\t\t\tWithdraw\n";
    std::cout << "\t\t------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();
    int index = getClientIndex(accountNum, vClients);

    processWithdraw(index, vClients);

    returnToMenu(menu::TRANSACTIONS);
}

void showAllBalances() {

    std::cout << "\t\t-------------------------------\n";
    std::cout << "\t\t\tShow All Balances\n";
    std::cout << "\t\t-------------------------------\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    printBalancesListHeader(vClients.size());

    int totalBalance = 0;

    for (const sClient& client : vClients) {

        std::cout << "| " << std::setw(17) << client.accountNum;
        std::cout << "| " << std::setw(30) << client.name;
        std::cout << "| $" << std::setw(10) << client.balance << '\n';

        totalBalance += client.balance;
    }

    std::cout << "\n\n-- Total Balance: $" << totalBalance << "\n\n";

    returnToMenu(menu::TRANSACTIONS);
}

void applyTransaction(eTransactionsMenu choice) {

    clearScreen();

    switch (choice) {

    case eTransactionsMenu::DEPOSIT:

        Deposit();
        break;

    case eTransactionsMenu::WITHDRAW:

        Withdraw();
        break;

    case eTransactionsMenu::SHOW_ALL_BALANCES:

        showAllBalances();
        break;

    case eTransactionsMenu::RETURN_TO_MAIN_MENU:

        return;
    }
}

void Transactions(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_TRANSACTIONS)) {

        printAccessDenied();
    }

    else {

        eTransactionsMenu choice;

        do {

            printTransactionsMenu();
            choice = (eTransactionsMenu)readMenuChoice(1, 4);

            applyTransaction(choice);

        } while (choice != eTransactionsMenu::RETURN_TO_MAIN_MENU);
    }

    
    returnToMenu();
}

void addUser(const std::vector <sUser>& vUsers) {

    sUser user = readUserData(vUsers);
    addLineToFile(userRecordToLine(user), file::USERS_FILE);
}

void addUsers() {

    std::cout << "\t\t-------------------------\n";
    std::cout << "\t\t\tAdd User\n";
    std::cout << "\t\t-------------------------\n";

    std::vector <sUser> vUsers = loadUsersFromFile();

    std::cout << "\nAdding New User:\n\n";

    char addAnotherUser;

    do {

        addUser(vUsers);

        addAnotherUser = readChar("\nDo you want to add another user (Y/N):");

    } while (toupper(addAnotherUser) == 'Y');


    std::cout << '\n';
    returnToMenu(menu::MANAGE_USERS);
}

void showAllUsers() {

    std::cout << "\t\t----------------------------\n";
    std::cout << "\t\t\tShow All Users\n";
    std::cout << "\t\t----------------------------\n";

    std::vector <sUser> vUsers = loadUsersFromFile();

    printUsersListHeader(vUsers.size());

    for (const sUser& user : vUsers) {

        std::cout << "| " << std::setw(17) << user.name;
        std::cout << "| " << std::setw(20) << user.password;
        std::cout << "| " << std::setw(20) << user.permissions << '\n';
    }

    returnToMenu(menu::MANAGE_USERS);
}

void updateUser() {

    std::cout << "\t\t-----------------------------\n";
    std::cout << "\t\t\tUpdate User\n";
    std::cout << "\t\t-----------------------------\n\n";

    std::vector <sUser> vUsers = loadUsersFromFile();

    std::string username = readUsername();
    int index = getUserIndexByName(username, vUsers);

    processUpdating(index, vUsers);

    returnToMenu(menu::MANAGE_USERS);
}

void removeUser() {

    std::cout << "\t\t-----------------------------\n";
    std::cout << "\t\t\tDelete User\n";
    std::cout << "\t\t-----------------------------\n\n";

    std::vector <sUser> vUsers = loadUsersFromFile();

    std::string username = readUsername();
    int index = getUserIndexByName(username, vUsers);

    processRemoving(index, vUsers);

    std::cout << '\n';
    returnToMenu(menu::MANAGE_USERS);
}

void findUser() {

    std::cout << "\t\t-----------------------------\n";
    std::cout << "\t\t\tFind User\n";
    std::cout << "\t\t-----------------------------\n";

    std::vector <sUser> vUsers = loadUsersFromFile();

    std::string username = readUsername();
    int index = getUserIndexByName(username, vUsers);

    if (isUserExistsByIndex(index)) {

        printUserCard(vUsers[index]);
    }

    else
        printUserNotFound(username);


    returnToMenu(menu::MANAGE_USERS);
}

void applyManageUsersMenuChoice(eManageUsersMenu choice) {

    clearScreen();

    switch (choice) {

    case eManageUsersMenu::ADD_NEW_USER:

        addUsers();
        break;

    case eManageUsersMenu::LIST_USERS:

        showAllUsers();
        break;

    case eManageUsersMenu::UPDATE_USER:

        updateUser();
        break;

    case eManageUsersMenu::REMOVE_USER:

        removeUser();
        break;

    case eManageUsersMenu::FIND_USER:

        findUser();
        break;

    case eManageUsersMenu::uRETURN_TO_MAIN_MENU:

        return;
    }
}

void manageUsers(const sUser& user) {

    if (!isAllowedPermission(user.permissions, ePermissions::ALLOW_MANAGE_USERS)) {

        printAccessDenied();
    }

    else {

        eManageUsersMenu choice;

        do {

            printManageUsersMenu();
            choice = (eManageUsersMenu)readMenuChoice(1, 6);

            applyManageUsersMenuChoice(choice);

        } while (choice != eManageUsersMenu::uRETURN_TO_MAIN_MENU);
    }

    
    returnToMenu();
}

void applyMainMenuChoice(eMainMenu choice, sUser& user) {

    clearScreen();

    switch (choice) {

    case eMainMenu::ADD_CLIENT:

            addClients(user);
            break;

    case eMainMenu::SHOW_ALL_CLIENTS:

            showAllClients(user);
            break;

    case eMainMenu::UPDATE_CLIENT:

            updateClient(user);
            break;

    case eMainMenu::REMOVE_CLIENT:

            removeClient(user);
            break;

    case eMainMenu::FIND_CLIENT:

             findClient(user);
             break;

    case eMainMenu::TRANSACTIONS:

            Transactions(user);
            break;

    case eMainMenu::MANAGE_USERS:

            manageUsers(user);
            break;

    case eMainMenu::LOGOUT:

            Login();
            break;
    }
}

void startProgram(sUser& user) {

    eMainMenu choice;

    do {

        printMainMenu();
        choice = (eMainMenu)readMenuChoice(1, 8);

        applyMainMenuChoice(choice, user);

    } while (choice != LOGOUT);
}

void Login() {

    std::cout << "\t\t----------------------------\n";
    std::cout << "\t\t\tLogin Screen\n";
    std::cout << "\t\t----------------------------\n\n";

    std::vector <sUser> vUsers = loadUsersFromFile();
    sUser user;

    while (true) {

        user.name = readUsername("Enter username:");
        user.password = readPositiveNum("Enter password:");

        int index = getUserIndexByNameAndPassword(user.name, user.password, vUsers);

        if (isUserExistsByIndex(index)) {

            user.permissions = vUsers[index].permissions;
            break;
        }

        std::cout << "\nInvalid username/password\n";
    };

    clearScreen();

    startProgram(user);
}

int main() {

    Login();


    return 0;
}