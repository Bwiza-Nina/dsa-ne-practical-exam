//Addin the required dependencies
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//Define the item class
class Item{
	private:
		int id;
		string name;
		int quantity;
		string registeredDate;
		
	public:
		Item(int id, string name, int quantity, string registeredDate){
			this->id = id;
			this->name = name;
			this->quantity = quantity;
			this->registeredDate = registeredDate;
		}
		int getId() const{
            return id;
        }

        void setId(int id){
            this->id=id;
        }
        string getName() const{
            return name;
        }

        void setName(string name){
            this->name=name;
        }
         int getQuantity() const{
            return quantity;
        }

        void setQuantity(int quantity){
            this->quantity=quantity;
        }
        string getRegisteredDate() const{
            return registeredDate;
        }

        void setRegisteredDate(string registeredDate){
            this->registeredDate=registeredDate;
        }
};

//Define the inventory
class Inventory{
	private:
		vector<Item> items;
	public:
		vector<string> splitString(const string& input, char delimiter){
			 vector<string> tokens;
    		stringstream ss(input);
    		string token;
    		while(getline(ss, token, delimiter)) {
        		tokens.push_back(token);
				}
    		return tokens;
		}
		// Function to convert a string to lowercase
		string toLowerCase(const string& input) {
    	string result = input;
    	transform(result.begin(), result.end(), result.begin(), ::tolower);
    	return result;
		}
		bool compareFunction (string &a, string &b) {
    			string first = a;
    			string second = b;
    			return a[2] < b[2];
		} 
		void command_syntaxes() {
    cout <<endl;
    cout <<endl;
    cout << "------------------------------------------------------------" <<endl;
    cout << "*                  Commands Syntaxes                        " <<endl;
    cout << "------------------------------------------------------------" <<endl;
    cout << "itemadd <item_id> <item_name> <quantity> <registration_date>" <<endl;
    cout << "itemslist"<<endl;
    cout <<endl;
    cout <<endl;
}
		void saveInventoryToFile(string filename){
			ofstream file;
			file.open(filename, ios::out | ios::app);
			for(int i=0; i<items.size(); i++){
				Item p = items[i];
				file << p.getId() <<"," << p.getName() << "," << p.getQuantity() << "," << p.getRegisteredDate() << endl;
			}
			file.close();
		}
		void addItem(Item item){
			bool found = false;
			for(auto& p: items){
				if(p.getId() == item.getId() || p.getName()==item.getName()){
					cout << "Product already exists." << endl;
					found = true;
					break;
				}
			}
			if(!found){
				items.push_back(item);
					cout << "Item added successfully.";
					saveInventoryToFile("inventory.csv");
					 cout << "-----------------------------------------------------------" <<endl;
			}
		}
		void listItems() const {
    // Create a vector to store items
    vector<Item> allItems{};

    // Read items from file and populate the vector
    ifstream file("inventory.csv");
    string line;
    while (getline(file, line)) {
        // Split the line into individual components
        stringstream ss(line);
        string id, name, quantity, registeredDate;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, registeredDate, ',');

        // Create an Item object and add it to the vector
        Item item(stoi(id), name, stoi(quantity), registeredDate);
        allItems.push_back(item);
    }

    // Sort the items vector by name
    sort(allItems.begin(), allItems.end(), [](const Item& p1, const Item& p2) {
        return p1.getName() < p2.getName();
    });

    // Print sorted items
    for (const auto& item : allItems) {
        cout << "Item ID: " << item.getId() << "\t\t";
        cout << "Item Name: " << item.getName() << "\t\t";
        cout << "Quantity: " << item.getQuantity() << "\t\t";
        cout << "Reg Date: " << item.getRegisteredDate() << endl;
    }
}

		int help(){
			string command;
			do{
				cout << "Console>";
				getline(cin, command);
				string commandCopy = toLowerCase(command);
				vector<string> splittedCommand = splitString(commandCopy, ' ');
				if(splittedCommand.at(0).compare("itemadd")==0){
					int id = std::stoi(splittedCommand.at(1));
					string name = splittedCommand.at(2);
					int quantity = std::stoi(splittedCommand.at(3));
					string registeredDate = splittedCommand.at(4);
					Item item(id, name,quantity, registeredDate);
					addItem(item);
					cout << "Item added successfully!" << endl;
				}else if(splittedCommand.at(0).compare("itemslist") == 0){
					listItems();
				}else if(splittedCommand.at(0).compare("help")==0){
					command_syntaxes();
				}else if(splittedCommand.at(0).compare("exit")==0){
					return 0;
				}else{
					cout << "Invalid Command. Retry again or type help to see available commands." << endl;
				}
			}
			while(command.compare("exit")!=0);
				return 0;
		}
};

int main(){
	 Inventory inventory;
     cout << "-----------------------------------------------------------" <<endl;
     cout << "---------------Inventory Management System ----------------" <<endl;   
     cout << "-----------------------------------------------------------" <<endl;
     cout << "------------------------- Welcome! ------------------------" <<endl;
     cout << "-----------------------------------------------------------" <<endl;
     
     cout << "Need help? Type 'help' then press enter key" << endl;
     cout << "Type 'exit' to exit the program" << endl;
     
     inventory.help();
     return 0;
     
}

