#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// constants

const std::string CLIENTS_FILE = "CLIENTS.txt";
const std::string SEPARATOR = " /##/ ";
const std::string CURRENCY = "$";

const int CLIENT_NOT_FOUND = -1;

// types (enums & structs)

enum eMainMenu {

    QUICK_WITHDRAW = 1,
    NORMAL_WITHDRAW = 2,
    DEPOSIT = 3,
    SHOW_BALANCE = 4,
    LOGOUT = 5,
};

enum eQuickWithdraw {

    WITHDRAW_20 = 1,
    WITHDRAW_50 = 2,
    WITHDRAW_100 = 3,
    WITHDRAW_200 = 4,
    WITHDRAW_400 = 5,
    WITHDRAW_600 = 6,
    WITHDRAW_800 = 7,
    WITHDRAW_1000 = 8,
    EXIT = 9,
};

struct sClient {

    std::string accountNum;
    int pincode;
    std::string name;
    std::string phoneNum;
    float balance;
};


// utility functions (declaration)

float readNum(const std::string& msg, const std::string& sep = " ");

std::string readText(const std::string& msg, const std::string& sep = " ");

float readNumInRange(const std::string& msg, int min, int max, const std::string& sep = " ");

float readPositiveNum(const std::string& msg, const std::string& sep = " ");

std::vector <std::string> splitText(const std::string& text, const std::string& sep);

char readChar(const std::string& msg, const std::string& sep = " ");

void clearScreen();

void returnToScreen(const std::string& menu = "Main Menu");
 

// input functions (declaration)

std::string readAccountNum();

int readPincode();

int readMenuChoice(int firstChoice, int lastChoice, const std::string& msg = "Enter your choice:");


// helper functions (declaration)

bool confirmTransaction(float amount, float& balance, bool isWithdraw = true);

sClient lineToRecord(const std::string& line);

std::string recordToLine(const sClient& record);

std::vector <sClient> loadClientsFromFile();

void saveClientsToFile(const std::vector <sClient>& vClients);

int getQuickWithdrawValue(eQuickWithdraw value);

int getClientIndexByAccountNum(const std::string& accountNum, const std::vector <sClient>& vClients);

bool isClientExistsByAccountNum(const std::string& accountNum, const std::vector <sClient>& vClients);

void confirmAndSaveTransaction(int amount, float& balance, const std::vector <sClient>& vClients, bool isWithdraw = true);

bool processQuickWithdraw(eQuickWithdraw choice, sClient& client, const std::vector <sClient>& vClients);


// output functions (declaration)

void printMainMenu();

void printQuickWithdrawMenu(float balance);

bool printAmountExceedBalance(float amount, float balance);


// core functions (declaration)

void quickWithdraw(sClient& client, const std::vector <sClient>& vClients);

void normalWithdraw(sClient& client, const std::vector <sClient>& vClients);

void Deposit(sClient& client, const std::vector <sClient>& vClients);

void showBalance(float balance);

void applyMenuChoice(eMainMenu choice, sClient& client, const std::vector <sClient>& vClients);

void startProgram(sClient& client, const std::vector <sClient>& vClients);

sClient processLoginAndGetClient(const std::vector <sClient>& vClients);

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

    std::cin.ignore();

    return num;
}

std::string readText(const std::string& msg, const std::string& sep) {

    std::string text;

    std::cout << msg << sep;
    std::getline(std::cin, text);

    return text;
}

float readNumInRange(const std::string& msg, int min, int max, const std::string& sep) {

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

std::vector <std::string> splitText(const std::string& text, const std::string& sep) {

    int wordPos = 0;
    int sepPos;

    std::vector <std::string> vWords;

    while ((sepPos = text.find(sep, wordPos)) != std::string::npos) {

        std::string word = text.substr(wordPos, sepPos - wordPos);

        if (!word.empty())
            vWords.push_back(word);

        wordPos = sepPos + sep.length();
    }

    if (wordPos < text.length())
        vWords.push_back(text.substr(wordPos));

    return vWords;
}

char readChar(const std::string& msg, const std::string& sep) {

    char character;

    std::cout << msg << sep;
    std::cin >> character;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return character;
}

void clearScreen() {

    system("cls");
}

void returnToScreen(const std::string& screen) {

    std::cout << "\nPress any key to return to " << screen << " Screen...";
    system("pause>0");

    clearScreen();
}


// input functions (definition)

std::string readAccountNum() {

    return readText("Enter account number:");
}

int readPincode() {

    return readPositiveNum("Enter pincode number:");
}

int readMenuChoice(int firstChoice, int lastChoice, const std::string& msg) {

    return readNumInRange(msg, firstChoice, lastChoice);
}

bool confirmTransaction(float amount, float& balance, bool isWithdraw) {

    char confirm = readChar("\nAre you sure you want to perform this transaction (Y/N):");

    if (toupper(confirm) == 'Y') {

        if (isWithdraw)
            amount *= -1;

        balance += amount;

        std::cout << "\nTransaction Done Successfully, New Account Balance: " << CURRENCY << balance << '\n';

        return true;
    }

    return false;
}

bool printAmountExceedBalance(float amount, float balance) {

    if (amount > balance) {

        std::cout << "\nAmount Exceed Balance, Try another amount\n";
        return true;
    }

    return false;
}

sClient lineToRecord(const std::string& line) {

    std::vector <std::string> vClientInfo = splitText(line, SEPARATOR);


    sClient client;

    client.accountNum = vClientInfo[0];
    client.pincode = std::stoi(vClientInfo[1]);
    client.name = vClientInfo[2];
    client.phoneNum = vClientInfo[3];
    client.balance = std::stod(vClientInfo[4]);

    return client;
}

std::string recordToLine(const sClient& record) {

    std::string line;

    line += record.accountNum + SEPARATOR;
    line += std::to_string(record.pincode) + SEPARATOR;
    line += record.name + SEPARATOR;
    line += record.phoneNum + SEPARATOR;
    line += std::to_string(record.balance);

    return line;
}

std::vector <sClient> loadClientsFromFile() {

    std::vector <sClient> vClients;

    std::fstream file;

    file.open(CLIENTS_FILE, std::ios::in);

    if (file.is_open()) {

        std::string line;

        while (std::getline(file, line)) {

            sClient client = lineToRecord(line);
            vClients.push_back(client);
        }

        file.close();
    }

    return vClients;
}

void saveClientsToFile(const std::vector <sClient>& vClients) {

    std::fstream file;

    file.open(CLIENTS_FILE, std::ios::out);

    if (file.is_open()) {

        for (const sClient& client : vClients) {

            file << recordToLine(client) << '\n';
        }

        file.close();
    }
}

int getClientIndexByAccountNum(const std::string& accountNum, const std::vector <sClient>& vClients) {

    int index = 0;

    for (const sClient& client : vClients) {

        if (client.accountNum != accountNum)
            index++;

        else
            return index;
    }

    return CLIENT_NOT_FOUND;
}

bool isClientExistsByAccountNum(const std::string& accountNum, const std::vector <sClient>& vClients) {

    return getClientIndexByAccountNum(accountNum, vClients) != CLIENT_NOT_FOUND;
}

void confirmAndSaveTransaction(int amount, float& balance, const std::vector <sClient>& vClients,  bool isWithdraw) {

    if (confirmTransaction(amount, balance, isWithdraw)) {

        saveClientsToFile(vClients);
    }
}

int getQuickWithdrawValue(eQuickWithdraw value) {

    switch (value) {

    case eQuickWithdraw::WITHDRAW_20: return 20;

    case eQuickWithdraw::WITHDRAW_50: return 50;

    case eQuickWithdraw::WITHDRAW_100: return 100;

    case eQuickWithdraw::WITHDRAW_200: return 200;

    case eQuickWithdraw::WITHDRAW_400: return 400;

    case eQuickWithdraw::WITHDRAW_600: return 600;

    case eQuickWithdraw::WITHDRAW_800: return 800;

    case eQuickWithdraw::WITHDRAW_1000: return 1000;

    }
}

bool processQuickWithdraw(eQuickWithdraw choice, sClient& client, const std::vector <sClient>& vClients) {

    if (choice != eQuickWithdraw::EXIT) {

        int amount = getQuickWithdrawValue(choice);


        if (printAmountExceedBalance(amount, client.balance))
            return false;


        confirmAndSaveTransaction(amount, client.balance, vClients);
        return true;
    }
}


// output functions (definition)

void printMainMenu() {

    std::cout << "==================================\n";
    std::cout << "\tATM Main Menu\n";
    std::cout << "==================================\n";
    std::cout << "[1] Quick Withdraw\n";
    std::cout << "[2] Normal Withdraw\n";
    std::cout << "[3] Deposit\n";
    std::cout << "[4] Show Balance\n";
    std::cout << "[5] Exit\n";
    std::cout << "==================================\n";
}

void printQuickWithdrawMenu(float balance) {

    std::cout << "==================================\n";
    std::cout << "\tQuick Withdraw Menu\n";
    std::cout << "==================================\n";
    std::cout << "[1] 20" << "\t\t" << "[2] 50\n";
    std::cout << "[3] 100" << "\t\t" << "[4] 200\n";
    std::cout << "[5] 400" << "\t\t" << "[6] 600\n";
    std::cout << "[7] 800" << "\t\t" << "[8] 1000\n";
    std::cout << "[9] Exit\n";
    std::cout << "==================================\n";

    std::cout << "Your Current Balance: " << CURRENCY << balance << "\n";
}


// core functions (definition)

void quickWithdraw(sClient& client, const std::vector <sClient>& vClients) {

    while (true) {

        printQuickWithdrawMenu(client.balance);

        eQuickWithdraw choice = (eQuickWithdraw)readMenuChoice(1, 9);

        if (processQuickWithdraw(choice, client, vClients))
            break;


        returnToScreen("Quick Withdraw Menu");
        clearScreen();
    }

    returnToScreen();
}

void normalWithdraw(sClient& client, const std::vector <sClient>& vClients) {

    int amount;

    while (true) {

        std::cout << "===================================\n";
        std::cout << "\tNormal Withdraw Screen\n";
        std::cout << "===================================\n";

        int amountMultiple = 5;

        do {

            amount = readPositiveNum("Enter an amount multiple of " + std::to_string(amountMultiple) + "'s:");

        } while (amount % amountMultiple != 0);


        if (!printAmountExceedBalance(amount, client.balance))
            break;


        returnToScreen("Normal Withdraw");
        clearScreen();
    }

    confirmAndSaveTransaction(amount, client.balance, vClients);

    returnToScreen();
}

void Deposit(sClient& client, const std::vector <sClient>& vClients) {

    std::cout << "===================================\n";
    std::cout << "\tDeposit Screen\n";
    std::cout << "===================================\n";

    int amount = readPositiveNum("Enter deposit amount: ", CURRENCY);

    confirmAndSaveTransaction(amount, client.balance, vClients, false);

    returnToScreen();
}

void showBalance(float balance) {

    std::cout << "===================================\n";
    std::cout << "\tShow Balance Screen\n";
    std::cout << "===================================\n";

    std::cout << "\nYour balance ----> " << CURRENCY << balance << '\n';

    returnToScreen();
}

void applyMenuChoice(eMainMenu choice, sClient& client, const std::vector <sClient>& vClients) {

    clearScreen();

    switch (choice) {

    case eMainMenu::QUICK_WITHDRAW:

        quickWithdraw(client, vClients);
        break;

    case eMainMenu::NORMAL_WITHDRAW:

        normalWithdraw(client, vClients);
        break;

    case eMainMenu::DEPOSIT:

        Deposit(client, vClients);
        break;

    case eMainMenu::SHOW_BALANCE:

        showBalance(client.balance);
        break;

    case eMainMenu::LOGOUT:

        Login();
        break;
    }
}

void startProgram(sClient& client, const std::vector <sClient>& vClients) {

    eMainMenu choice;

    do {

        printMainMenu();
        choice = (eMainMenu)readMenuChoice(1, 5);

        applyMenuChoice(choice, client, vClients);

    } while (choice != eMainMenu::LOGOUT);
}

sClient processLoginAndGetClient(const std::vector <sClient>& vClients) {

    sClient client;
    int index;

    while (true) {

        client.accountNum = readAccountNum();
        client.pincode = readPincode();

        if ((index = getClientIndexByAccountNum(client.accountNum, vClients)) != CLIENT_NOT_FOUND)
            break;

        std::cout << "\nInvalid AccountNum/Pincode\n";
    }

    client.name = vClients[index].name;
    client.phoneNum = vClients[index].phoneNum;
    client.balance = vClients[index].balance;

    return client;
}

void Login() {

    std::cout << "===============================\n";
    std::cout << "\tLogin Screen\n";
    std::cout << "===============================\n";

    std::vector <sClient> vClients = loadClientsFromFile();
    
    sClient client = processLoginAndGetClient(vClients);

    clearScreen();

    startProgram(client, vClients);
}

int main() {

    Login();


    return 0;
}