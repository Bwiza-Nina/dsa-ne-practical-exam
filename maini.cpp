#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    string registeredDate;

public:
    Item(int id, string name, int quantity, string registeredDate) {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->registeredDate = registeredDate;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    string getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    string getRegisteredDate() const {
        return registeredDate;
    }

    void setRegisteredDate(string registeredDate) {
        this->registeredDate = registeredDate;
    }
};

class Inventory {
private:
    vector<Item> items;

public:
    vector<string> splitString(const string& input, char delimiter) {
        vector<string> tokens;
        stringstream ss(input);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    string toLowerCase(const string& input) {
        string result = input;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    bool compareFunction(string& a, string& b) {
        string first = a;
        string second = b;
        return a[2] < b[2];
    }

    void commandSyntaxes() {
        cout << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "*                  Commands Syntaxes                        " << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
        cout << "itemslist" << endl;
        cout << endl << endl;
    }

    void saveInventoryToFile(string filename) {
        ofstream file;
        file.open(filename, ios::out | ios::app);
        for (int i = 0; i < items.size(); i++) {
            Item p = items[i];
            file << p.getId() << "," << p.getName() << "," << p.getQuantity() << "," << p.getRegisteredDate() << endl;
        }
        file.close();
    }

    void addItem(Item item) {
        bool found = false;
        for (const auto& p : items) {
            if (p.getId() == item.getId() || p.getName() == item.getName()) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "The item already exists!" << endl;
        } else {
            ifstream file("inventory.csv");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string id, name;
                getline(ss, id, ',');
                getline(ss, name, ',');

                if (stoi(id) == item.getId() || name == item.getName()) {
                    found = true;
                    break;
                }
            }
            file.close();

            if (found) {
                cout << "The item already exists in the file!" << endl;
            } else {
                items.push_back(item);
                cout << "Item added successfully." << endl;
                saveInventoryToFile("inventory.csv");
            }
        }
    }

    void listItems() const {
        vector<Item> allItems{};
        ifstream file("inventory.csv");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, quantity, registeredDate;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, quantity, ',');
            getline(ss, registeredDate, ',');

            Item item(stoi(id), name, stoi(quantity), registeredDate);
            allItems.push_back(item);
        }
        file.close();

        sort(allItems.begin(), allItems.end(), [](const Item& p1, const Item& p2) {
            return p1.getName() < p2.getName();
        });

        for (const auto& item : allItems) {
            cout << "Item ID: " << item.getId() << "\t\t";
            cout << "Item Name: " << item.getName() << "\t\t";
            cout << "Quantity: " << item.getQuantity() << "\t\t";
            cout << "Reg Date: " << item.getRegisteredDate() << endl;
        }
    }

    int help() {
        string command;
        do {
            cout << "Console>";
            getline(cin, command);
            string commandCopy = toLowerCase(command);
            vector<string> splittedCommand = splitString(commandCopy, ' ');
            if (splittedCommand.at(0).compare("itemadd") == 0) {
                int id = stoi(splittedCommand.at(1));
                string name = splittedCommand.at(2);
                int quantity = stoi(splittedCommand.at(3));
                string registeredDate = splittedCommand.at(4);
                Item item(id, name, quantity, registeredDate);
                addItem(item);
                cout << "Item added successfully!" << endl;
            } else if (splittedCommand.at(0).compare("itemslist") == 0) {
                listItems();
            } else if (splittedCommand.at(0).compare("help") == 0) {
                commandSyntaxes();
            } else if (splittedCommand.at(0).compare("exit") == 0) {
                return 0;
            } else {
                cout << "Invalid Command. Retry again or type help to see available commands." << endl;
            }
        } while (command.compare("exit") != 0);

        return 0;
    }
};

int main() {
    Inventory inventory;
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Inventory Management System ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welcome! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;

    cout << "Need help? Type 'help' then press enter key" << endl;
    cout << "Type 'exit' to exit the program" << endl;

    inventory.help();
    return 0;
}

