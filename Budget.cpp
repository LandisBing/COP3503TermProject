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
        throw "Error: no transactions";
    }
}

vector<Transaction> Budget::getAprilTransactions() {
    if (!aprilTransactions.empty()) {
        return aprilTransactions;
    } else {
        throw "Error: no April transactions";
    }
}

vector<Transaction> Budget::getMayTransactions() {
    if (!mayTransactions.empty()) {
        return mayTransactions;
    } else {
        throw "Error: no May transactions";
    }
}

vector<Quota> Budget::getAllQuotas() {
    if (!allQuotas.empty()) {
        return allQuotas;
    } else {
        throw "Error: no quotas";
    }
}
string Budget::getQuotaName(){
    return quotaName;
}
void Budget::setQuotaName(string newName) {
    quotaName = newName;
}

// Updates all the transactions by checking for reoccuring transactions. then sets the reoccurance boolean to true or false
void Budget::updateReOccurance() {
	// First step is to make a new transaction vector that i can sort for easier iterability
	vector<Transaction> transactions = allTransactions;
	// Defining an operator for the sort method
	struct myclass {
		bool operator() (Transaction i, Transaction j) { return (i.getName().compare(j.getName()) < 0);}
	} myobject;
	// Sorting transactions by name
	sort(transactions.begin() , transactions.end() , myobject);

	// Define a "gap" or essentialy holds the number or repeated names so the next iteration of the for loop starts at the next named transaction and doesnt run more than once per transaction name
	int gap = 1;
	bool reOccurance;
	int length = transactions.size();
	for (int i = 0; i < length; i += gap){
		gap = 1;
		reOccurance = false;
		// Now find all transactions of the same name using another for loop
		for (int j = i+1; j < length; j ++) {
			if (transactions[i].getName()  == transactions[j].getName()){
				// Compare all transactions of the same name by amount and day to ensure they are repeated occurences
				gap++;
				if (transactions[i].getDate().getDay() == transactions[j].getDate().getDay() && transactions[i].getAmount() == transactions[j].getAmount()){
					reOccurance = true;
				}else {
					// If not the same for any transaction of the same name and same amount then it is not a reoccuring transaction that should be reminded of
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
		// Now update the transaction in allTransactions to hold the correct occurance value if determined to be a reOccurance
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
// Updates the reminders deQue based off the reOccurance. This method should always be run after update reOccurance
	// Once again we start with a transaction equal to allTransactions so we can sort it and iterate easier
	vector<Transaction> transactions = allTransactions;
	struct myclass {
		bool operator() (Transaction i, Transaction j) { return (i.getDate().getDay() > j.getDate().getDay());}
	} myobject;
	// I decided to sort by day for simpler iterability of the method
	sort(transactions.begin() , transactions.end() , myobject);
	// I needed to remove all reOccuring transactions so i wouldnt add the same transaction to reminders more than once
	removeReoccurance(transactions);
	int length = transactions.size();
	for (int i = 0; i < length; i ++){
		// For each transaction in transactions
		if (transactions[i].getOccurance()){
			// If it is a reOccurance then i save that as a temporary transaction
			Transaction temp = transactions[i];
			// I have to make sure that before i push to reminders the month and year are the same as the current month and year.
			temp.getDate().setMonth(lastDate().getMonth());
			temp.getDate().setYear(lastDate().getYear());
			// I then push the transaction to the list of reminders
			reminders.push_back(temp);
		}
	}
	int lastDay = lastDate().getDay();
	while(reminders.front().getDate().getDay() < lastDay){
		// Now that reminders has a list of things that need to be reminded i need to ensure we are only reminding for things in the future
		Transaction temp;
		temp = reminders.front();
		// So i make a temporary transaction to hold the front of the deque
		if (reminders.front().getDate().getMonth() < 11){
			// Move the month forward
			temp.getDate().setMonth(reminders.front().getDate().getMonth()+1);
		}else{
			// Or move the year forward and reset the month back to january
			temp.getDate().setMonth(reminders.front().getDate().getMonth()-11);
			temp.getDate().setYear(reminders.front().getDate().getYear()+1);
		}
		// Then i push the temporary transaction to the reminders
		reminders.push_back(temp);
		// And pop the front
		reminders.pop_front();
	}
}

vector<Transaction> Budget::removeReoccurance(vector<Transaction> input){
// Simple method to remove Reoccuring transactions and return a new list of transactions
	// Important note is that it is assumed the vector is already sorted by name before being entered into the method
	vector<Transaction> output = input;
	int length = input.size();
	int gap = 1;
	// gap holds the distance between the names in the sorted list
	for (int i = 0; i < length; i+= gap){
		gap = 1;
		for (int j = i+1; j < length; j++){
			// Checks every other transaction of same name and if it is Reoccuring then it removes it from the vector
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
	// Simple method that returns a Date of the date of the last transaction
	vector<Transaction> transactions = allTransactions;
	Date lastDate;
	lastDate.setDay(0);
	lastDate.setMonth(0);
	lastDate.setYear(0);
	// Initialize a temporary Date and set all the values to 0
	int length = transactions.size();
	for (int i = 0; i < length; i++){
		// I then compare every transactions date with the temporary date
		if (lastDate.getYear() <= transactions[i].getDate().getYear() && lastDate.getMonth() <= transactions[i].getDate().getMonth() && lastDate.getDay() <= transactions[i].getDate().getDay()){
			// If the date of the transaction is further in the future
			lastDate = transactions[i].getDate();
			// Then last date takes its place and holds the date of the last transaction
		}
	}
	return lastDate;
}

//Allows a new transaction to be inputed manually
void Budget::addNewTransaction() {
    //Initializes necessary variables to handle the transaction
    Transaction newTransaction;
    string inputString;
    string parseHelper;
    ofstream newFileData;
    int userChoice;
    double inputAmount;

    //Gets input from the user
    cout << "Enter the name of the transaction: " << endl;
    cin >> inputString;
    newTransaction.setName(inputString);
    cout << "Select the name of the transaction: " << endl;
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
    cout << "Enter the amount of the transaction : " << endl;
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
//parseHelper is the month at this line
parseHelper = inputString.substr(0, inputString.find('/'));
//Checks if there is an extra zero before converting parseHelper to an int
if (parseHelper[0] == '0') {
parseHelper.erase(0, 1);
}
int localMonth = stoi(parseHelper);
inputString.erase(0, inputString.find('/') + 1);

//parseHelper is day at this line
parseHelper = inputString.substr(0, inputString.find('/'));
if (parseHelper[0] == '0') {
parseHelper.erase(0, 1);
}
int localDay = stoi(parseHelper);
inputString.erase(0, inputString.find('/') + 1);
//Sets the transaction date
int localYear = stoi(inputString);
newTransaction.setDate(localMonth, localDay, localYear);
//Adds the transaction to the vector of transactions
allTransactions.push_back(newTransaction);
/*
updateReOccurance();
updateReminders(); */

}
//Allows a transaction to be deleted
void Budget::deleteTransaction() {
    string inputName;
    string inputDate;
    Budget functionBudget("account.txt");
    vector<Transaction> functionTransactions = functionBudget.getAllTransactions();
    functionBudget.closeFile();

    cout << "What transaction should be deleted?" << endl;
    cin >> inputName;
    cout << "When was this transaction (MM/DD/YYYY)?" << endl;
    cin >> inputDate;

    ofstream functionFile("account.txt");

    //Handles zeroes in the inputDate
    if (inputDate[0] == '0') {
        inputDate.erase(0, 1);
        if (inputDate[2] == '0') {
            string dateHelper;
            dateHelper += inputDate[0];
            dateHelper += inputDate[1];
            for (int i = 3; i < 9; i++) {
                dateHelper += inputDate[i];
            }
            inputDate = dateHelper;
        }
    }
    if (inputDate[3] == '0') {
        string dateHelper;
        dateHelper += inputDate[0];
        dateHelper += inputDate[1];
        dateHelper += inputDate[2];
        for (int i = 4; i < 10; i++) {
            dateHelper += inputDate[i];
        }
        inputDate = dateHelper;
    }
    cout << inputDate << endl;

    //Writes all transactions to the file except the one to be deleted
    int size = functionTransactions.size()-1;
    for (int i = 0; i < size - 1; i++) {
        if (functionTransactions[i].getName().find(inputName) == string::npos ||
            (functionTransactions[i].getDate().toString() != inputDate &&
             functionTransactions[i].getName().find(inputName) != string::npos)) {
            functionFile << functionTransactions[i].getCategory() << " | " << functionTransactions[i].getName() << " $"
                         << functionTransactions[i].getAmount() << " | " <<
                         functionTransactions[i].getDate().toString() << endl;
        }
    }
    //Prevents an extra newline at the end of the file
    if (functionTransactions[functionTransactions.size() - 1].getName().find(inputName) ==
        string::npos || (functionTransactions[functionTransactions.size() - 1].getDate().toString() != inputDate &&
                         functionTransactions[functionTransactions.size() - 1].getName() == inputName)) {
        functionFile << functionTransactions[functionTransactions.size() - 1].getCategory() << " | "
                     << functionTransactions[functionTransactions.size() - 1].getName() << " $"
                     << functionTransactions[functionTransactions.size() - 1].getAmount() << " | " <<
                     functionTransactions[functionTransactions.size() - 1].getDate().toString();
    }
    //Closes the file
    functionFile.close();
}

//Saves sorted Transactions
void Budget::saveTransactions(vector<Transaction> saveVector) {
    fileData.close();
    ofstream saveFile(fileName);
    //Writes content from the vector into the file
    int size = saveVector.size();
    for (int i = 0; i < size - 1; i++) {
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
    //Allows the parsing code to find the file
    quotaName = budgetName;
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

    //Takes in the transactionName of the user's budget and checks if it exists
    cout << "What is your existing budget called?" << endl;
    cin >> budgetName;
    budgetName.append(".txt");
    //Allows the parsing code to find the file
    quotaName = budgetName;
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
    int size = functionQuota.size();
    for (int i = 0; i < size-1; i++) {
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
    //Allows the parsing code to find the file
    quotaName = budgetName;
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
