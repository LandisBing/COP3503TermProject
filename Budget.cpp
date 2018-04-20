#include "Budget.h"
#include <algorithm>
using namespace std;

//Getter for transactionName
string Transaction::getName() {
    return transactionName;
}

//Setter for transactionName
void Transaction::setName(string newName) {
    transactionName = newName;
}

//Getter for transaction
string Transaction::getCategory() {
    return categoryName;
}

//Setter for transaction
void Transaction::setCategory(string newCategory) {
    categoryName = newCategory;
}

//Getter for transactionAmount
double Transaction::getAmount() {
    return transactionAmount;
}

//Setter for transactionAmount
void Transaction::setAmount(double newAmount) {
    if (newAmount >= 0) {
        transactionAmount = newAmount;
    } else {
        cout << "Invalid transactionAmount" << endl;
    }
}

//Getter for date
Date Transaction::getDate() {

    return transactionDate;
}

//Sets the date
void Transaction::setDate(int month, int day, int year) {

    transactionDate.setMonth(month);
    transactionDate.setDay(day);
    transactionDate.setYear(year);
}

void Transaction::setOccurance(bool input){
	reOccuring = input;
}
bool Transaction::getOccurance(){
	return reOccuring;
}

//Transaction constructor
Transaction::Transaction() {
    transactionName = "";
    categoryName = "";
    transactionAmount = 0;
    reOccuring = false;
}

//Takes one line of data from the file and puts it into a Transaction object, then adds those objects to the vector
void Budget::parseTransactionData() {

    string currentLine;
    string parseHelper;
    Transaction tempTransaction;

    while (fileData.good()) {

        getline(fileData, currentLine);
        //parseHelper is the categoryName at this line
        parseHelper = currentLine.substr(0, currentLine.find(' '));
        tempTransaction.setCategory(parseHelper);
        currentLine.erase(0, currentLine.find('|') + 2);

        //parseHelper is the transactionName at this line
        parseHelper = currentLine.substr(0, currentLine.find('$'));
        tempTransaction.setName(parseHelper);
        currentLine.erase(0, currentLine.find('$') + 1);

        //parseHelper is the dollar transactionAmount at this line
        parseHelper = currentLine.substr(0, currentLine.find(' '));
        tempTransaction.setAmount(stod(parseHelper));
        currentLine.erase(0, currentLine.find('|') + 2);

        //parseHelper is the month at this line
        parseHelper = currentLine.substr(0, currentLine.find('/'));
        //Checks if there is an extra zero before converting parseHelper to an int
        if (parseHelper[0] == '0') {
            parseHelper.erase(0, 1);
        }
        int localMonth = stoi(parseHelper);
        currentLine.erase(0, currentLine.find('/') + 1);

        //parseHelper is day at this line
        parseHelper = currentLine.substr(0, currentLine.find('/'));
        if (parseHelper[0] == '0') {
            parseHelper.erase(0, 1);
        }
        int localDay = stoi(parseHelper);
        currentLine.erase(0, currentLine.find('/') + 1);
        //Sets the transaction date
        int localYear = stoi(currentLine);
        tempTransaction.setDate(localMonth, localDay, localYear);
        //Adds the transaction to the budget
        allTransactions.push_back(tempTransaction);
        //Adds the transaction to its respective month
        if (localMonth == 4) {
            aprilTransactions.push_back(tempTransaction);
        }
        if (localMonth == 5) {
            mayTransactions.push_back(tempTransaction);
        }
    }
}

//Parses an existing budget file to get the user's spending limit
void Budget::parseQuotaData(string quotaName) {

    string currentLine;
    string parseHelper;
    Quota tempQuota;

    //Opens the existing budget file
    ifstream quotaFile;
    quotaFile.open(quotaName);
    //Parses through the budget file and puts the data into allQuotas
    while (quotaFile.good()) {

        getline(quotaFile, currentLine);

        //parseHelper is the categoryName at this line
        parseHelper = currentLine.substr(0, currentLine.find(' '));
        tempQuota.setCategory(parseHelper);
        currentLine.erase(0, currentLine.find('|') + 2);

        //parseHelper is the spending limit at this line
        tempQuota.setSpendLimit(stoi(currentLine));
        allQuotas.push_back(tempQuota);
    }
    //Closes the file
    quotaFile.close();

}

//Gets all the transactions for use in sorting
vector<Transaction> Budget::getAllTransactions() {
    if (!allTransactions.empty()) {
        return allTransactions;
    } else {
        cout << "Error: no transactions" << endl;
    }
}

vector<Transaction> Budget::getAprilTransactions() {
    if (!aprilTransactions.empty()) {
        return aprilTransactions;
    } else {
        cout << "Error: no April transactions" << endl;
    }
}

vector<Transaction> Budget::getMayTransactions() {
    if (!mayTransactions.empty()) {
        return mayTransactions;
    } else {
        cout << "Error: no May transactions" << endl;
    }
}

vector<Quota> Budget::getAllQuotas() {
    if (!allQuotas.empty()) {
        return allQuotas;
    } else {
        cout << "Error: no quotas" << endl;
    }
}

void Budget::updateReOccurance() {
	vector<Transaction> transactions = allTransactions;
	struct myclass {
		bool operator() (Transaction i, Transaction j) { return (i.getName().compare(j.getName()) < 0);}
	} myobject;

	sort(transactions.begin() , transactions.end() , myobject);

	int gap = 1;
	bool reOccurance;
	int length = transactions.size();
	for (int i = 0; i < length; i += gap){
		gap = 1;
		reOccurance = false;
		for (int j = i+1; j < length; j ++) {
			if (transactions[i].getName()  == transactions[j].getName()){
				gap++;
				if (transactions[i].getDate().getDay() == transactions[j].getDate().getDay() && transactions[i].getAmount() == transactions[j].getAmount()){
					reOccurance = true;
				}else {
					reOccurance = false;
					for (int k = gap;  gap < length - i -1; k++){
						if (transactions[i].getName()  == transactions[k].getName()){
							gap++;
						}else {
							break;
						}
					}
					break;
				}
			}
		}
		if (reOccurance) {
			for (int j = 0; j < length; j++) {
				if (allTransactions[j].getName().compare(transactions[i].getName()) == 0){
					allTransactions[j].setOccurance(true);
				}
			}
		}
	}
}

void Budget::updateReminders(){
	vector<Transaction> transactions = allTransactions;
	struct myclass {
		bool operator() (Transaction i, Transaction j) { return (i.getDate().getDay() > j.getDate().getDay());}
	} myobject;

	sort(transactions.begin() , transactions.end() , myobject);
	removeReoccurance(transactions);
	int length = transactions.size();
	for (int i = 0; i < length; i ++){
		if (transactions[i].getOccurance()){
			reminders.push_back(transactions[i]);
		}
	}
	int lastDay = lastDate().getDay();
	while(reminders.front().getDate().getDay() < lastDay){
		reminders.push_back(reminders.front());
		reminders.pop_front();
	}
}

vector<Transaction> Budget::removeReoccurance(vector<Transaction> input){
	vector<Transaction> output = input;
	int length = input.size();
	int gap = 1;
	for (int i = 0; i < length; i+= gap){
		gap = 1;
		for (int j = i+1; j < length; j++){
			if (output[i].getName().compare(output[j].getName()) == 0 && output[j].getOccurance()){
				output.erase(input.begin()+j);
				length--;
				j--;
			}
		}
	}
	return output;
}

Date Budget::lastDate(){
	vector<Transaction> transactions = allTransactions;
	Date lastDate;
	lastDate.setDay(0);
	lastDate.setMonth(0);
	lastDate.setYear(0);
	int length = transactions.size();
	for (int i = 0; i < length; i++){
		if (lastDate.getYear() <= transactions[i].getDate().getYear() && lastDate.getMonth() <= transactions[i].getDate().getMonth() && lastDate.getDay() <= transactions[i].getDate().getDay()){
			lastDate = transactions[i].getDate();
		}
	}
	return lastDate;
}

//Allows a new transaction to be inputted manually
void Budget::addNewTransaction() {
    //Initializes necessary variables to handle the transaction
    Transaction newTransaction;
    string inputString;
    string parseHelper;
    ofstream newFileData;
    int userChoice;
    double inputAmount;

    //Gets input from the user
    cout << "Enter the transactionName of the transaction: " << endl;
    cin >> inputString;
    newTransaction.setName(inputString);
    cout << "Select the categoryName of the transaction: " << endl;
    cout << "1. Housing" << endl;
    cout << "2. Entertainment" << endl;
    cout << "3. Food" << endl;
    cout << "4. Transportation" << endl;
    cout << "5. Medical" << endl;
    cout << "6. Clothing" << endl;
    cout << "7. Insurance" << endl;
    cout << "8. Utilities" << endl;
    cout << "9. Other" << endl;
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            newTransaction.setCategory("Housing");
            break;
        case 2:
            newTransaction.setCategory("Entertainment");
            break;
        case 3:
            newTransaction.setCategory("Food");
            break;
        case 4:
            newTransaction.setCategory("Transportation");
            break;
        case 5:
            newTransaction.setCategory("Medical");
            break;
        case 6:
            newTransaction.setCategory("Clothing");
            break;
        case 7:
            newTransaction.setCategory("Insurance");
            break;
        case 8:
            newTransaction.setCategory("Utilities");
            break;
        case 9:
            newTransaction.setCategory("Other");
            break;
        default:
            cout << "Invalid selection" << endl;
    }
    cout << "Enter the transactionAmount of the transaction : " << endl;
    cin >> inputAmount;
    newTransaction.setAmount(inputAmount);
    cout << "Enter the date of the transaction (MM/DD/YYYY): " << endl;
    cin >> inputString;

    //Saves transaction to the file
    newFileData.open(fileName, ios::app);
    newFileData << "\n" << newTransaction.getCategory() << " | " << newTransaction.getName() << ": $" << inputAmount
                << " | " << inputString;

    //Handles user adding dates with 1-digit months and days
    if (inputString[0] == '0') {
        inputString.erase(0, 1);
    }

    //Uses parsing code from a previous function to handle the date
    parseHelper = inputString.substr(0, inputString.find('/'));
    newTransaction.getDate().setMonth(stoi(parseHelper));
    inputString.erase(0, inputString.find('/') + 1);
    if (inputString[0] == '0') {
        inputString.erase(0, 1);
    }

    parseHelper = inputString.substr(0, inputString.find('/'));
    newTransaction.getDate().setDay(stoi(parseHelper));
    inputString.erase(0, inputString.find('/') + 1);

    //parseHelper is the year at this line
    parseHelper = inputString;
    newTransaction.getDate().setYear(stoi(parseHelper));
    //Adds the transaction to the vector of transactions
    allTransactions.push_back(newTransaction);
    updateReOccurance();
    updateReminders();
    
}
//Allows a transaction to be deleted
void Budget::deleteTransaction() {
    string inputName;
   // size_t nameFinder;
    cout << "What transaction should be deleted?" << endl;
    cin >> inputName;
    for (int i = 0; i < allTransactions.size(); i++) {
        if(allTransactions[i].getName().find(inputName) != string::npos){
            cout << "Found it" << endl;
        }else{
            cout << "Didn't find it " << endl;
        }
    }
}

//Saves sorted Transactions
void Budget::saveTransactions(vector<Transaction> saveVector) {
    fileData.close();
    ofstream saveFile(fileName);
    //Writes content from the vector into the file
    for (int i = 0; i < saveVector.size() - 1; i++) {
        saveFile << saveVector[i].getCategory() << " | " << saveVector[i].getName() << " $"
                 << saveVector[i].getAmount() << " | " << saveVector[i].getDate().toString() << endl;
    }
    //Prevents an extra newline character at the end of the file
    saveFile << saveVector[saveVector.size() - 1].getCategory() << " | " << saveVector[saveVector.size() - 1].getName()
             << " $"
             << saveVector[saveVector.size() - 1].getAmount() << " | "
             << saveVector[saveVector.size() - 1].getDate().toString();
    saveFile.close();
}
//Closes the file
void Budget::closeFile() {
    fileData.close();
}

//Creates a new budget file
void Budget::createBudget() {
    //Keeps track of the user's input
    string budgetName;
    int userSpending;
    //Creates a new text file to hold the budget
    cout << "Choose a name for your new budget" << endl;
    cin >> budgetName;
    budgetName.append(".txt");
    ofstream budgetFile(budgetName);
    //Allows the user to choose how much they want to spend
    cout << "How much do you want to spend on housing?" << endl;
    cin >> userSpending;
    budgetFile << "Housing | " << userSpending << endl;
    cout << "How much do you want to spend on entertainment?" << endl;
    cin >> userSpending;
    budgetFile << "Entertainment | " << userSpending << endl;
    cout << "How much do you want to spend on food?" << endl;
    cin >> userSpending;
    budgetFile << "Food | " << userSpending << endl;
    cout << "How much do you want to spend on transportation?" << endl;
    cin >> userSpending;
    budgetFile << "Transportation | " << userSpending << endl;
    cout << "How much do you want to spend on medical expenses?" << endl;
    cin >> userSpending;
    budgetFile << "Medical | " << userSpending << endl;
    cout << "How much do you want to spend on clothing?" << endl;
    cin >> userSpending;
    budgetFile << "Clothing | " << userSpending << endl;
    cout << "How much do you want to spend on insurance?" << endl;
    cin >> userSpending;
    budgetFile << "Insurance | " << userSpending << endl;
    cout << "How much do you want to spend on utilities?" << endl;
    cin >> userSpending;
    budgetFile << "Utilities | " << userSpending << endl;
    cout << "How much do you want to spend on things not listed above?" << endl;
    cin >> userSpending;
    budgetFile << "Other | " << userSpending;
    //Closes the file after writing to it
    budgetFile.close();
}

//Changes an existing Budget file
void Budget::changeBudget() {
    string budgetName;
    int userChoice;
    string editCategory;
    string parseHelper;
    size_t categoryFinder;

    //Takes in the transactionName of the user's budget and checks if it exists
    cout << "What is your existing budget called?" << endl;
    cin >> budgetName;
    budgetName.append(".txt");
    ifstream budgetFile;
    budgetFile.open(budgetName);
    if (!budgetFile) {
        cout << "Budget not found" << endl;
        return;
    }
    //Lets the user select what they want to change
    cout << "Which category do you want to change?" << endl;
    cout << "1. Housing" << endl;
    cout << "2. Entertainment" << endl;
    cout << "3. Food" << endl;
    cout << "4. Transportation" << endl;
    cout << "5. Medical" << endl;
    cout << "6. Clothing" << endl;
    cout << "7. Insurance" << endl;
    cout << "8. Utilities" << endl;
    cout << "9. Other" << endl;
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            editCategory = "Housing";
            break;
        case 2:
            editCategory = "Entertainment";
            break;
        case 3:
            editCategory = "Food";
            break;
        case 4:
            editCategory = "Transportation";
            break;
        case 5:
            editCategory = "Medical";
            break;
        case 6:
            editCategory = "Clothing";
            break;
        case 7:
            editCategory = "Insurance";
            break;
        case 8:
            editCategory = "Utilities";
            break;
        case 9:
            editCategory = "Other";
            break;
        default:
            cout << "Invalid selection" << endl;
    }
    cout << "How much do you want to spend on " << editCategory << endl;
    cin >> userChoice;
    vector<Quota> functionQuota;
    string currentLine;
    Quota tempQuota;

    //Parses through the budget file and puts the data into functionQuota
    while (budgetFile.good()) {

        getline(budgetFile, currentLine);

        //parseHelper is the categoryName at this line
        parseHelper = currentLine.substr(0, currentLine.find(' '));
        tempQuota.setCategory(parseHelper);
        currentLine.erase(0, currentLine.find('|') + 2);

        //parseHelper is the spending limit at this line
        tempQuota.setSpendLimit(stoi(currentLine));
        if(tempQuota.getCategory() == editCategory){
            tempQuota.setCategory(editCategory);
            tempQuota.setSpendLimit(userChoice);
        }
        functionQuota.push_back(tempQuota);
    }
    //Closes the file
    budgetFile.close();
    //Writes quota data to new file
    ofstream budgetWrite;
    budgetWrite.open(budgetName);

    for (int i = 0; i < functionQuota.size()-1; i++) {
        budgetWrite << functionQuota[i].getCategory() << " | " << functionQuota[i].getSpendLimit() << endl;
    }
    //Prevents an extra newline character at the end of the file
    budgetWrite << functionQuota[functionQuota.size() - 1].getCategory() << " | "
                << functionQuota[functionQuota.size() - 1].getSpendLimit();
    budgetWrite.close();

}
//Allows the user to use an existing budget
void Budget::useBudget() {
    string budgetName;
    cout << "What is your existing budget called?" << endl;

    cin >> budgetName;
    budgetName.append(".txt");
    fstream budgetFile;
    budgetFile.open(budgetName);
    if (!budgetFile) {
        cout << "Budget not found" << endl;
    }
    parseQuotaData(budgetName);
}

//Budget constructor
Budget::Budget(string inputName) {
    fileData.open(inputName);
    fileName = inputName;
    parseTransactionData();

}
