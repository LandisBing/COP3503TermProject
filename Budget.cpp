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
        cout << "Invalid transaction Amount" << endl;
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

bool Budget:: transactionInputChecker(string userInput){
    bool isNum;
    for (int i = 0; i < userInput.length(); i++) {
        if (isdigit(userInput[i]) || userInput[i]=='.' && (userInput[i-1]!='.' || userInput[i+1]!='.') ) {
            isNum = true;
        }
        else {
            isNum = false;
            break;
        }
    }
    return isNum;
}

int Budget:: userInputChecker(){
    string userInput;
    int inputConverted;
    bool isNum = false;
    bool validEntry = false;
    while(!validEntry){
        cin >> userInput;
        for (int i = 0; i < userInput.length(); i++) {
            if (isdigit(userInput[i])) {
                isNum = true;

            } else {
                isNum = false;
                break;
            }
        }

        if(!isNum){
            cout << "Invalid entry. Please try again: ";
            validEntry = false;
        }
        else{
            inputConverted = stoi(userInput);
            validEntry = true;
        }
    }
    return inputConverted;
}

string Budget::userDateChecker() {
    string date;
    bool validDate = false;
    while(!validDate){
        cin >> date;
        if(isdigit(date[0]) && isdigit(date[1]) && date[2]=='/' && isdigit(date[3]) && isdigit(date[4]) && date[5]=='/'
                && isdigit(date[6]) && isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9])){
           int month = stoi(date.substr(0,1));
            int day = stoi(date.substr(3,4));
            int year = stoi(date.substr(6,9));
            if((month < 1 || month > 12) || (day < 1 || day > 31) || (year < 1)){
                cout << "Invalid date entry. Please try again: ";
                validDate = false;
            }
            else{
                validDate = true;
            }
        }
        else{
            cout << "Invalid date entry. Please try again: ";
            validDate = false;

        }
    }
    return date;
    }

int Budget::userCategoryChecker() {
    string userInput;
    int inputConverted;
    bool isNum = false;
    bool validEntry = false;
    while(!validEntry){
        cin >> userInput;
        for (int i = 0; i < userInput.length(); i++) {
            if (isdigit(userInput[i])) {
                isNum = true;

            } else {
                isNum = false;
                break;
            }
        }

        if(isNum) {
            inputConverted = stoi(userInput);
            if (inputConverted >= 1 && inputConverted <= 9) {
                validEntry = true;
            } else {
                cout << "\nInvalid input please try again: ";
                validEntry = false;
            }
        }
        else
        { cout << "\nInvalid input please try again: ";
          validEntry = false;
        }
    }
    return inputConverted;
}



//Takes one line of data from the file and puts it into a Transaction object, then adds those objects to the vector
void Budget::parseTransactionData() {

    string currentLine;
    string parseHelper;
    Transaction tempTransaction;

    while (fileData.good()) {

        getline(fileData, currentLine);
        //Prevents the function from crashing if there's a blank line
        if(currentLine == ""){
            continue;
        }
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
//Gets all quotas
vector<Quota> Budget::getAllQuotas() {
    if (!allQuotas.empty()) {
        return allQuotas;
    } else {
        cout << "Error: no quotas" << endl;
    }
}
//Puts all transaction amounts into a single vector for use in graphing
vector<int> Budget::getTransactionAmounts(){
    vector<int> transactionAmounts;
    for (int i = 0; i < allTransactions.size(); i++) {
        transactionAmounts.push_back(allTransactions[i].getAmount());
    }
    return transactionAmounts;
}
//Gets the total quota amount for use in graphing
int Budget::getQuotaTotal() {
    int quotaTotal = 0;
    for (int i = 0; i < allQuotas.size(); i++) {
        quotaTotal += allQuotas[i].getSpendLimit();
    }
    return quotaTotal;
}
//Puts all category names into a single vector for use in graphing
vector<string> Budget::getCategoryNames(){
    vector<string> categoryNames;
    categoryNames.emplace_back("Housing");
    categoryNames.emplace_back("Entertainment");
    categoryNames.emplace_back("Food");
    categoryNames.emplace_back("Transportation");
    categoryNames.emplace_back("Medical");
    categoryNames.emplace_back("Clothing");
    categoryNames.emplace_back("Insurance");
    categoryNames.emplace_back("Utilities");
    categoryNames.emplace_back("Other");

    return categoryNames;
}
string Budget::getQuotaName(){
    return quotaName;
}
void Budget::setQuotaName(string newName) {
    quotaName = newName;
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
    string userChoice;
    string inputAmount;
    int categoryChoice;
    bool validTransaction=false;

    //Gets input from the user
    cout << "Enter the name of the transaction: (One word) " << endl;
    cin >> inputString;
    newTransaction.setName(inputString);
    cout << "Select the category of the transaction: " << endl;
    cout << "1. Housing" << endl;
    cout << "2. Entertainment" << endl;
    cout << "3. Food" << endl;
    cout << "4. Transportation" << endl;
    cout << "5. Medical" << endl;
    cout << "6. Clothing" << endl;
    cout << "7. Insurance" << endl;
    cout << "8. Utilities" << endl;
    cout << "9. Other" << endl;

    cin >> categoryChoice;
            switch (categoryChoice) {
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


    while(!validTransaction){
        cout << "Enter the amount of the transaction : " << endl;
        cin >> inputAmount;
        bool validTransactionEntry = transactionInputChecker(inputAmount);
        if(validTransactionEntry) {
            double finalinputAmount = stod(inputAmount);
            newTransaction.setAmount(finalinputAmount);
            validTransaction = true;
        }
        else{
            cout << "Invalid entry, please enter valid amount\n";
            validTransaction = false;
        }
    }



    cout << "Enter the date of the transaction (MM/DD/YYYY): " << endl;
    cin >> inputString;

    //Saves transaction to the file
    newFileData.open(fileName, ios::app);
    newFileData << "\n" << newTransaction.getCategory() << " | " << newTransaction.getName() << " $" << inputAmount
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

    cout << "What transaction should be deleted? (One Word)" << endl;
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

    //Writes all transactions to the file except the one to be deleted
    for (int i = 0; i < functionTransactions.size() - 1; i++) {
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
                         functionTransactions[functionTransactions.size() - 1].getName().find(inputName) != string::npos)) {
        //functionTransactions[functionTransactions.size() - 1].getName() == inputName)) {
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
    //Allows the parsing code to find the file
    quotaName = budgetName;
    ofstream budgetFile(budgetName);
    //Allows the user to choose how much they want to spend

    cout << "How much do you want to spend on housing?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Housing | " << userSpending << endl;
    cout << "How much do you want to spend on entertainment?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Entertainment | " << userSpending << endl;
    cout << "How much do you want to spend on food?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Food | " << userSpending << endl;
    cout << "How much do you want to spend on transportation?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Transportation | " << userSpending << endl;
    cout << "How much do you want to spend on medical expenses?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Medical | " << userSpending << endl;
    cout << "How much do you want to spend on clothing?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Clothing | " << userSpending << endl;
    cout << "How much do you want to spend on insurance?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Insurance | " << userSpending << endl;
    cout << "How much do you want to spend on utilities?" << endl;
    userSpending = userInputChecker();
    budgetFile << "Utilities | " << userSpending << endl;
    cout << "How much do you want to spend on things not listed above?" << endl;
    userSpending = userInputChecker();
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

