#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>


// constants

const std::string CLIENTS_FILE = "CLIENTS.txt";
const std::string SEPARATOR = " /##/ ";


// types (enums & structs)

enum eMainMenu {

    ADD_CLIENT = 1,
    SHOW_ALL_CLIENTS = 2,
    UPDATE_CLIENT = 3,
    REMOVE_CLIENT = 4,
    FIND_CLIENT = 5,
    EXIT = 6,
};


struct sClient {

    std::string accountNum;
    int pincode;
    std::string name;
    std::string phoneNum;
    float balance;
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

int readPincode(const std::string& msg = "Enter pincode number:");

std::string readPhoneNum(const std::string& msg = "Enter phone number:");

std::string readName(const std::string& msg = "Enter client name:");

float readBalance(const std::string& msg = "Enter account balance:", const std::string& sep = " $");

sClient readClientData(const std::vector <sClient>& vClients);

void readUpdatedClientData(sClient& client);


// helper functions (declaration)

int getClientIndex(const std::string& accountNum, const std::vector <sClient>& vClients);

sClient lineToRecord(const std::string& line, const std::string& sep = SEPARATOR);

std::string recordToLine(const sClient& client, const std::string& sep = SEPARATOR);

void returnToMainMenu();

void processUpdatingClient(const std::string& accountNum, std::vector <sClient>& vClients);

void processRemovingClient(const std::string& accountNum, std::vector <sClient>& vClients);

void addClient(const std::vector <sClient>& vClients);


// output functions (declaration)

void printMainMenu();

void printClientsListHeader(int numOfClients);

void printClientRecord(const sClient& client);

void printClientCard(const sClient& client);


// data functions (declaration)

std::vector <sClient> loadClientsFromFile(const std::string& fileName = CLIENTS_FILE, const std::string& sep = SEPARATOR);

void saveClientsToFile(const std::vector <sClient> vClients, const std::string& fileName = CLIENTS_FILE);


// core functions (declaration)

void addClients();

void showAllClients();

void updateClient();

void removeClient();

void findClient();

void Exit();

void applyClientChoice(eMainMenu choice);

void startProgram();



// utility functions (definition)

float readNum(const std::string& msg, const std::string& sep) {

    float num;

    std::cout << msg << sep;
    std::cin >> num;

    while (std::cin.fail()) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());

        std::cout << "Invalid Number! Enter a valid number:";
        std::cin >> num;
    }

    std::cin.ignore();

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
    std::getline(std::cin, text);

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

int readPincode(const std::string& msg) {

    return readPositiveNum(msg);
}

std::string readPhoneNum(const std::string& msg) {

    return readText(msg);
}

std::string readName(const std::string& msg) {

    return readText(msg);
}

float readBalance(const std::string& msg, const std::string& sep) {

    return readPositiveNum(msg, sep);
}

sClient readClientData(const std::vector <sClient>& vClients) {

    sClient client;

    client.accountNum = readAccountNum();

    while (getClientIndex(client.accountNum, vClients) != -1) {

        std::cout << "\nClient with account number [" << client.accountNum << "] is already added, ";
        client.accountNum = readAccountNum();
    }

    client.pincode = readPincode();
    client.name = readName();
    client.phoneNum = readPhoneNum();
    client.balance = readBalance();

    return client;
}

void readUpdatedClientData(sClient& client) {

    client.pincode = readPincode();
    client.name = readName();
    client.phoneNum = readPhoneNum();
    client.balance = readBalance();
}


// helper functions (definition)

int getClientIndex(const std::string& accountNum, const std::vector <sClient>& vClients) {

    int index = 0;

    for (const sClient& client : vClients) {

        if (client.accountNum != accountNum)
            index++;

        else
            return index;
    }

    return -1;
}

sClient lineToRecord(const std::string& line, const std::string& sep) {

    std::vector <std::string> vRecord = splitText(line, sep);

    sClient client;

    client.accountNum = vRecord[0];
    client.pincode = std::stoi(vRecord[1]);
    client.name = vRecord[2];
    client.phoneNum = vRecord[3];
    client.balance = std::stod(vRecord[4]);

    return client;
}

std::string recordToLine(const sClient& client, const std::string& sep) {

    std::string line = "";

    line += client.accountNum + sep;
    line += std::to_string(client.pincode) + sep;
    line += client.name + sep;
    line += client.phoneNum + sep;
    line += std::to_string(client.balance);

    return line;
}

void returnToMainMenu() {

    std::cout << "\nPress any key to return to main menu...";
    system("pause>0");

    clearScreen();
}

void processUpdatingClient(const std::string& accountNum, std::vector <sClient>& vClients) {

    int index = getClientIndex(accountNum, vClients);

    if (index != -1) {

        printClientCard(vClients[index]);

        char sureToUpdate = readChar("\nAre you sure you want to update client data (Y/N):");

        if (toupper(sureToUpdate) == 'Y') {

            std::cout << '\n';

            readUpdatedClientData(vClients[index]);
            saveClientsToFile(vClients);
        }
    }

    else
        std::cout << "\nClient with account number [" << accountNum << "] isn't founded\n";
}

void processRemovingClient(const std::string& accountNum, std::vector <sClient>& vClients) {

    int index = getClientIndex(accountNum, vClients);

    if (index != -1) {

        printClientCard(vClients[index]);

        char sureToUpdate = readChar("\nAre you sure you want to remove client (Y/N):");

        if (toupper(sureToUpdate) == 'Y') {

            vClients[index].isDeleted = false;
            saveClientsToFile(vClients);
        }
    }

    else
        std::cout << "\nClient with account number [" << accountNum << "] isn't founded\n";
}

void addClient(const std::vector <sClient>& vClients) {

    sClient client = readClientData(vClients);

    addLineToFile(recordToLine(client), CLIENTS_FILE);
}


// output functions (definition)

void printMainMenu() {

    std::cout << "================================\n";
    std::cout << "\tMain Menu\n";
    std::cout << "================================\n";
    std::cout << "[1] Add New Client\n";
    std::cout << "[2] Show All Clients\n";
    std::cout << "[3] Update Client\n";
    std::cout << "[4] Remove Client\n";
    std::cout << "[5] Find Client\n";
    std::cout << "[6] Exit\n";
    std::cout << "================================\n";
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
    std::cout << "| " << std::setw(10) << client.balance << '\n';
}

void printClientCard(const sClient& client) {

    std::cout << "\nAccount Number: " << client.accountNum;
    std::cout << "\nPincode: " << client.pincode;
    std::cout << "\nClient Name: " << client.name;
    std::cout << "\nPhone Number: " << client.phoneNum;
    std::cout << "\nBalance: " << client.balance << '\n';
}


// data functions (definition)

std::vector <sClient> loadClientsFromFile(const std::string& fileName, const std::string& sep) {

    std::fstream file;

    file.open(fileName, std::ios::in);

    std::vector <sClient> vClients;

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            sClient client = lineToRecord(line, sep);
            vClients.push_back(client);
        }

        file.close();
    }

    return vClients;
}

void saveClientsToFile(const std::vector <sClient> vClients, const std::string& fileName) {

    std::fstream file;

    file.open(fileName, std::ios::out);

    if (file.is_open()) {

        for (const sClient& client : vClients) {

            if (client.isDeleted == false) {

                file << recordToLine(client) << '\n';
            }
        }

        file.close();
    }
}


// core functions (definition)

void addClients() {

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

    returnToMainMenu();
}

void showAllClients() {

    std::cout << "\t\t----------------------------\n";
    std::cout << "\t\t\tShow All Clients\n";
    std::cout << "\t\t----------------------------\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    printClientsListHeader(vClients.size());

    for (const sClient& client : vClients) {

        printClientRecord(client);
    }

    std::cout << "\n-------------------------------------------------------------------------------------------\n";

    returnToMainMenu();
}

void updateClient() {

    std::cout << "\t\t---------------------------\n";
    std::cout << "\t\t\tUpdate Client\n";
    std::cout << "\t\t---------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();

    processUpdatingClient(accountNum, vClients);

    returnToMainMenu();
}

void removeClient() {

    std::cout << "\t\t----------------------------\n";
    std::cout << "\t\t\tRemove Client\n";
    std::cout << "\t\t----------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();

    processRemovingClient(accountNum, vClients);

    returnToMainMenu();
}

void findClient() {

    std::cout << "\t\t------------------------\n";
    std::cout << "\t\t\tFind Client\n";
    std::cout << "\t\t------------------------\n\n";

    std::vector <sClient> vClients = loadClientsFromFile();

    std::string accountNum = readAccountNum();

    int index = getClientIndex(accountNum, vClients);

    if (index != -1) {

        printClientCard(vClients[index]);
    }

    else
        std::cout << "\nClient isn't founded\n";


    returnToMainMenu();
}

void Exit() {

    std::cout << "\t\t---------------------\n";
    std::cout << "\t\t\tExit\n";
    std::cout << "\t\t---------------------\n";
}

void applyClientChoice(eMainMenu choice) {

    clearScreen();

    switch (choice) {

    case eMainMenu::ADD_CLIENT:

        addClients();
        break;

    case eMainMenu::SHOW_ALL_CLIENTS:

        showAllClients();
        break;

    case eMainMenu::UPDATE_CLIENT:

        updateClient();
        break;

    case eMainMenu::REMOVE_CLIENT:

        removeClient();
        break;

    case eMainMenu::FIND_CLIENT:

        findClient();
        break;

    case eMainMenu::EXIT:

        Exit();
        break;
    }
}

void startProgram() {

    eMainMenu choice;

    do {

        printMainMenu();
        choice = (eMainMenu)readMenuChoice(1, 6);

        applyClientChoice(choice);

    } while (choice != EXIT);
}

int main() {

    startProgram();


    return 0;
}