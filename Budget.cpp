#include "Budget.h"
#include <algorithm>
#include <regex>
using namespace std;

//Getter for transactionName
string Transaction::getName()
{
    return transactionName;
}

//Setter for transactionName
void Transaction::setName(string newName)
{
    transactionName = newName;
}

//Getter for transaction
string Transaction::getCategory()
{
    return categoryName;
}

//Setter for transaction
void Transaction::setCategory(string newCategory)
{
    categoryName = newCategory;
}

//Getter for transactionAmount
double Transaction::getAmount()
{
    return transactionAmount;
}

//Setter for transactionAmount
void Transaction::setAmount(double newAmount)
{
    if (newAmount >= 0) {
        transactionAmount = newAmount;
    } else {
        cout << "Invalid transaction Amount" << endl;
    }
}

//Getter for date
Date Transaction::getDate()
{
    return transactionDate;
}

//Sets the date
void Transaction::setDate(int month, int day, int year)
{

    transactionDate.setMonth(month);
    transactionDate.setDay(day);
    transactionDate.setYear(year);
}

//Transaction constructor
Transaction::Transaction()
{
    transactionName = "";
    categoryName = "";
    transactionAmount = 0;
}

// Verifies that the transaction amount the user enters is a number
string Budget:: transactionInputChecker()
{
    string inputAmount;
    bool validTransaction;

    do
    {
        getline(cin, inputAmount);
        for (int i = 0; i < inputAmount.length(); i++)
        {
            if (isdigit(inputAmount[i]) ||
                inputAmount[i] == '.' && (inputAmount[i - 1] != '.' || inputAmount[i + 1] != '.'))
            {

                validTransaction = true;
            }
            else
            {
                cout << "Invalid entry, please enter valid amount" << endl;
                validTransaction = false;
                break;
            }
        }

        if (validTransaction)
        {
            validTransaction= true;
        }
        else
        {
            validTransaction= false;
        }
    }
    while(!validTransaction);

    return inputAmount;
}

//Checks if user enters a number when selecting menu options
int Budget:: userInputChecker()
{
    string userInput;
    int inputConverted;
    bool isNum;
    bool validEntry;
    do
    {
        getline(cin,userInput);
        int length = userInput.length();
        for (int i = 0; i < length; i++)
        {
            if (isdigit(userInput[i]))
            {
                isNum = true;

            }
            else
            {
                cout << "Invalid entry. Please try again: " << endl;
                isNum = false;
                break;
            }
        }
        if (!isNum)
        {
            validEntry = false;

        }
        else
        {
            inputConverted = stoi(userInput);
            validEntry = true;
        }

    }
    while(!validEntry);
    return inputConverted;
}

//Checks that user inputs a valid date in (MM/DD/YYYY) format
string Budget::userDateChecker()
{
    string date;
    bool validDate=false;
    bool leapYear;
    while(!validDate)
    {
        getline(cin,date);
        date.erase(remove_if(date.begin(), date.end(), ::isspace), date.end());
        //accounts for single digit days and sigle digit months
        regex regDate1 ("[0][1-9]/[0][1-9]/[^0][0-9]{3}");
        //accounts for single digit days and double digit months
        regex regDate2("[1][0-2]/[0][1-9]/[^0][0-9]{3}");
        //accounts for single digit months with double digit days 10-29
        regex regDate3 ("[0][^(0,2)]/[1-2][0-9]/[^0][0-9]{3}");
        //accounts for double digit months with double digit days 10-29
        regex regDate4 ("[1][0-2]/[1-2][0-9]/[^0][0-9]{3}");
        //accounts for single digit months with 31 days
        regex regDate5("[0][(1,3,5,7,8)]/[3][0-1]/[1-9][0-9]{3}");
        //accounts for double digit months with 31 days;
        regex regDate6("[1][(0,2)]/[3][0-1]/[1-9][0-9]{3}");
        // accounts for single digit months with 30 days
        regex regDate7("[0][4,6,9]/[3][0]/[1-9][0-9]{3}");
        // accounts for double digit months with 30 days
        regex regDate8 ("[1][1]/[3][0]/[1-9][0-9]{3}");
        // accounts for possible leap year day
        regex leapYearDate ("[0][2]/[2][9]/[1-9][0-9]{3}");
        //handles dates in February
        regex regDate9("[0][2]/[1][0-9]/[1-9][0-9]{3}");
        regex febDate ("[0][2]/[2][0-8]/[1-9][0-9]{3}");


        smatch match;
        // checks if user inputs a valid date that is not a possible leap year day
        if (regex_search(date, match, regDate1) || regex_search(date, match, regDate2)
            || regex_search(date, match, regDate3) || regex_search(date, match, regDate4)
            || regex_search(date,match,regDate5) || regex_search(date,match,regDate6)
            || regex_search(date,match,regDate7) || regex_search(date,match,regDate8)
            || regex_search(date,match,febDate) || regex_search(date,match,regDate9))
        {
            validDate = true;
        }
        else if(regex_search(date,match,leapYearDate))
        {
            int year = stoi(date.substr(6,9));
            if(year % 4 == 0 && year % 100 !=0)
            {
                leapYear = true;
            }
            else if((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0))
            {
                leapYear = true;
            }
            else
            {
                leapYear = false;
            }

            if(leapYear == true)
            {
                validDate = true;
            }
            else
            {
                cout << "Invalid entry. Please enter a valid date (MM/DD/YYYY): ";
                validDate = false;
            }
        }
        else
        {
            cout << "Invalid entry. Please enter a valid date (MM/DD/YYYY): ";
            validDate = false;
        }
    }
    return date;
}

//Checks that user enters a number that corresponds with a category
int Budget::userCategoryChecker()
{
    string userInput;
    int inputConverted;
    bool isNum = false;
    bool validEntry = false;
    while(!validEntry)
    {
        getline(cin,userInput);
        for (int i = 0; i < userInput.length(); i++)
        {
            if (isdigit(userInput[i]))
            {
                isNum = true;

            }
            else
            {
                cout << "Invalid input please try again: ";
                isNum = false;
                break;
            }
        }

        if(isNum)
        {
            inputConverted = stoi(userInput);
            if (inputConverted >= 1 && inputConverted <= 9)
            {
                validEntry = true;
            }
            else
            {
                validEntry = false;
            }
        }
        else
        {
            validEntry = false;
        }
    }
    return inputConverted;
}

string Budget::transactionNameChecker()
{
    string transactionName;
    bool oneWord;
    do
    {
        getline(cin,transactionName);
        for(int i = 0; i < transactionName.length();i++)
        {
            if(transactionName[i]==' ')
            {
                cout << "Invalid name for transaction. Please enter a one word name: " << endl;
                oneWord = false;
                break;
            }
            else
            {
                oneWord = true;
            }
        }

    }
    while(!oneWord);
    return transactionName;
}

//Takes one line of data from the file and puts it into a Transaction object, then adds those objects to the vector
void Budget::parseTransactionData()
{
    string currentLine;
    string parseHelper;
    Transaction tempTransaction;

    while (fileData.good())
    {
        getline(fileData, currentLine);

        //Prevents the function from crashing if there's a blank line
        if(currentLine == "")
        {
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
        if (parseHelper[0] == '0')
        {
            parseHelper.erase(0, 1);
        }

        int localMonth = stoi(parseHelper);
        currentLine.erase(0, currentLine.find('/') + 1);

        //parseHelper is day at this line
        parseHelper = currentLine.substr(0, currentLine.find('/'));

        if (parseHelper[0] == '0')
        {
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
        if (localMonth == 4)
        {
            aprilTransactions.push_back(tempTransaction);
        }
        if (localMonth == 5)
        {
            mayTransactions.push_back(tempTransaction);
        }
    }
}

//Parses an existing budget file to get the user's spending limit
void Budget::parseQuotaData(string quotaName)
{

    string currentLine;
    string parseHelper;
    Quota tempQuota;

    //Opens the existing budget file
    ifstream quotaFile;
    quotaFile.open(quotaName);
    //Parses through the budget file and puts the data into allQuotas
    while (quotaFile.good())
    {

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
vector<Transaction> Budget::getAllTransactions()
{
    if (!allTransactions.empty())
    {
        return allTransactions;
    }
    else
        {
        cout << "Error: no transactions" << endl;
    }
}

vector<Quota> Budget::getAllQuotas()
{
    if (!allQuotas.empty())
    {
        return allQuotas;
    }
    else
        {
        cout << "Error: no quotas" << endl;
    }
}

//Puts all transaction amounts into a single vector for use in graphing
vector<int> Budget::getTransactionAmounts()
{
    vector<int> transactionAmounts;
    vector<string> categoryNames;
    int total = 0;
    categoryNames.push_back("Housing");
    categoryNames.push_back("Entertainment");
    categoryNames.push_back("Food");
    categoryNames.push_back("Transportation");
    categoryNames.push_back("Medical");
    categoryNames.push_back("Clothing");
    categoryNames.push_back("Insurance");
    categoryNames.push_back("Utilities");
    categoryNames.push_back("Other");

    for (int i = 0; i < categoryNames.size(); i++)
    {
        for (int j = 0; j < allTransactions.size(); j++)
        {
            if ((allTransactions[j].getCategory())==(categoryNames[i]))
            {
                total = total + allTransactions[j].getAmount();
            }
        }
        transactionAmounts.push_back(total);
        total = 0;
    }

    return transactionAmounts;
}

//Gets the total quota amount for use in graphing
int Budget::getTransactionsTotal()
{
    int transactionsTotal = 0;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        transactionsTotal += allTransactions[i].getAmount();
    }
    return transactionsTotal;
}

//Puts all category names into a single vector for use in graphing
vector<string> Budget::getCategoryNames()
{
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

string Budget::getQuotaName()
{
    return quotaName;
}

//Allows a new transaction to be inputted manually
void Budget::addNewTransaction()
{
    //Initializes necessary variables to handle the transaction
    Transaction newTransaction;
    string inputString;
    string parseHelper;
    ofstream newFileData;
    string userChoice;
    string inputAmount;
    int categoryChoice;

    //Gets input from the user
    cout << "Enter the name of the transaction: (One word) " << endl;
    inputString = transactionNameChecker();
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

    categoryChoice = userCategoryChecker();
    switch (categoryChoice)
    {
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
    inputAmount = transactionInputChecker();
    double finalinputAmount = stod(inputAmount);
    newTransaction.setAmount(finalinputAmount);

    cout << "Enter the date of the transaction (MM/DD/YYYY): " << endl;
    inputString = userDateChecker();

    //Saves transaction to the file
    newFileData.open(fileName, ios::app);
    newFileData << "\n" << newTransaction.getCategory() << " | " << newTransaction.getName() << " $" << inputAmount
                << " | " << inputString;


    //Handles user adding dates with 1-digit months and days
    if (inputString[0] == '0')
    {
        inputString.erase(0, 1);
    }
//parseHelper is the month at this line
    parseHelper = inputString.substr(0, inputString.find('/'));
//Checks if there is an extra zero before converting parseHelper to an int
    if (parseHelper[0] == '0')
    {
        parseHelper.erase(0, 1);
    }
    int localMonth = stoi(parseHelper);
    inputString.erase(0, inputString.find('/') + 1);

//parseHelper is day at this line
    parseHelper = inputString.substr(0, inputString.find('/'));
    if (parseHelper[0] == '0')
    {
        parseHelper.erase(0, 1);
    }
    int localDay = stoi(parseHelper);
    inputString.erase(0, inputString.find('/') + 1);
//Sets the transaction date
    int localYear = stoi(inputString);
    newTransaction.setDate(localMonth, localDay, localYear);
//Adds the transaction to the vector of transactions
    allTransactions.push_back(newTransaction);
}


//Allows a transaction to be deleted
void Budget::deleteTransaction()
{
    string inputName;
    string inputDate;
    Budget functionBudget("account.txt");
    vector<Transaction> functionTransactions = functionBudget.getAllTransactions();
    functionBudget.closeFile();

    cout << "What transaction should be deleted? (One Word)" << endl;
    inputName = transactionNameChecker();
    cout << "When was this transaction (MM/DD/YYYY)?" << endl;
    inputDate = userDateChecker();

    ofstream functionFile("account.txt");

    //Handles zeroes in the inputDate
    if (inputDate[0] == '0')
    {
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
    if (inputDate[3] == '0')
    {
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
                         functionTransactions[functionTransactions.size() - 1].getName().find(inputName) != string::npos))
    {
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
void Budget::saveTransactions(vector<Transaction> saveVector)
{
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
void Budget::closeFile()
{
    fileData.close();
}

//Creates a new budget file
void Budget::createBudget()
{
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
void Budget::changeBudget()
{
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
    if (!budgetFile)
    {
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
    switch (userChoice)
    {
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
    while (budgetFile.good())
    {

        getline(budgetFile, currentLine);

        //parseHelper is the categoryName at this line
        parseHelper = currentLine.substr(0, currentLine.find(' '));
        tempQuota.setCategory(parseHelper);
        currentLine.erase(0, currentLine.find('|') + 2);

        //parseHelper is the spending limit at this line
        tempQuota.setSpendLimit(stoi(currentLine));
        if(tempQuota.getCategory() == editCategory)
        {
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

    for (int i = 0; i < functionQuota.size()-1; i++)
    {
        budgetWrite << functionQuota[i].getCategory() << " | " << functionQuota[i].getSpendLimit() << endl;
    }
    //Prevents an extra newline character at the end of the file
    budgetWrite << functionQuota[functionQuota.size() - 1].getCategory() << " | "
                << functionQuota[functionQuota.size() - 1].getSpendLimit();
    budgetWrite.close();

}

//Allows the user to use an existing budget
void Budget::useBudget()
{
    string budgetName;
    cout << "What is your existing budget called?" << endl;

    cin >> budgetName;
    budgetName.append(".txt");
    //Allows the parsing code to find the file
    quotaName = budgetName;
    fstream budgetFile;
    budgetFile.open(budgetName);
    if (!budgetFile)
    {
        cout << "Budget not found" << endl;
    }
    parseQuotaData(budgetName);
}

//Budget constructor
Budget::Budget(string inputName)
{
    fileData.open(inputName);
    fileName = inputName;
    parseTransactionData();
}
