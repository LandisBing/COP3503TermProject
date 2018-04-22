
#ifndef BUDGET_BUDGET_H
#define BUDGET_BUDGET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include "Date.h"
#include "Quota.h"

using namespace std;

//Transaction class to group the data together
class Transaction {
private:
    //Member variables
    string transactionName;
    string categoryName;
    double transactionAmount;
    Date transactionDate;
    bool reOccuring;

public:
    //Member functions
    string getName();

    void setName(string newName);

    string getCategory();

    void setCategory(string newCategory);

    double getAmount();

    void setAmount(double newAmount);

    Date getDate();

    void setDate(int month, int day, int year);

    bool getOccurance();

    void setOccurance(bool reOccuring);

    Transaction();
};

//Bank account class to group the transactions together
class Budget {
private:
    ifstream fileData;
    string fileName;
    string quotaName;
    vector<Transaction> allTransactions;
    vector<Transaction> aprilTransactions;
    vector<Transaction> mayTransactions;
    vector<Quota> allQuotas;
    deque<Transaction> reminders;
    
    void updateReOccurance();
    
    void updateReminders();
    
    vector<Transaction> removeReoccurance(vector<Transaction> input);
    
    Date lastDate();

public:

    vector<Transaction> getAllTransactions();

    bool transactionInputChecker(string userInput);

    int userInputChecker();

    string userDateChecker();

    int userCategoryChecker();

    vector<Quota> getAllQuotas();

    vector<int> getTransactionAmounts();

    int getTransactionsTotal();

    vector<string> getCategoryNames();

    string getQuotaName();

    void setQuotaName(string newName);

    void parseQuotaData(string quotaName);

    void parseTransactionData();

    void addNewTransaction();

    void deleteTransaction();

    void saveTransactions(vector<Transaction> saveVector);

    void createBudget();

    void changeBudget();

    void useBudget();

    void closeFile();

    explicit Budget(string inputName);
};

#endif //BUDGET_BUDGET_H
