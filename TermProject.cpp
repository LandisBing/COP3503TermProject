#include <iostream>
#include "Budget.h"
#include "ui.h"
#include "sortmenu.cpp"

using namespace std;

// Checks if user input is a valid option. This is achieved by using a for loop to analyze the user input string. If any value
// is not a string it will return input as false.
bool inputChecker(string userInput) {
    bool isNum;
    for (int i = 0; i < userInput.length(); i++) {
        if (isdigit(userInput[i])) {
            isNum = true;
        } else {
            isNum = false;
        }
    }
    return isNum;
}


//Prints out user menu and asks takes user input for the menu options.

// Prints welcome menu that will ask user if they want to create a new budget, change existing budget, or use an existing budget.
void welcomeMenu(Budget b) {
    bool validInput = false;
    while (!validInput) {
        string welcomeInput;

        cout << "+--------------------------------+\n";
        cout << "|Choose a budget option:         |\n ";
        cout << "|================================|\n";
        cout << "|1. Create New Budget            |\n";
        cout << "|--------------------------------|\n";
        cout << "|2. Change Existing Budget       |\n";
        cout << "|--------------------------------|\n";
        cout << "|3. Use Existing Budget          |\n";
        cout << "|--------------------------------|\n";
        cout << "|4. Exit Program                 |\n";
        cout << "+--------------------------------+\n";
        cin >> welcomeInput;
        // takes user input and sends it to a function that will check if the input is a number.
        validInput = inputChecker(welcomeInput);
        if (!validInput) {
            cout << "Invalid input please try again\n";
        } else {
            int numInput = stoi(welcomeInput);
            // switch statement has cases that correspond to the menu options
            switch (numInput) {
                case 1:
                    b.createBudget();
                    break;

                case 2:
                    b.changeBudget();
                    break;

                case 3:
                    b.useBudget();
                    break;

                case 4:

                    break;

                default:
                    cout << "Invalid input please try again";
                    validInput = false;
            }
        }

    }
}


int main() {

    Budget mainBudget("account.txt");

    //this is how you use the graph code
    BarGraph b;
    UserInterface u;
    Transaction t;
    u.welcomeScreen();

    vector<string> categoryList;
    vector<int> moneyAmounts;

    vector<int> graphMoney;
    int totalBudget;

    bool validInput = false;

    while (!validInput) {
        string welcomeInput;

        cout << "+--------------------------------+\n";
        cout << "|Choose a budget option:         |\n";
        cout << "|================================|\n";
        cout << "|1. Create New Budget            |\n";
        cout << "|--------------------------------|\n";
        cout << "|2. Change Existing Budget       |\n";
        cout << "|--------------------------------|\n";
        cout << "|3. Use Existing Budget          |\n";
        cout << "|--------------------------------|\n";
        cout << "|4. Exit Program                 |\n";
        cout << "+--------------------------------+\n";
        cin >> welcomeInput;
        // takes user input and sends it to a function that will check if the input is a number.
        validInput = inputChecker(welcomeInput);
        if (!validInput) {
            cout << "Invalid input please try again\n";
        } else {
            int numInput = stoi(welcomeInput);
            // switch statement has cases that correspond to the menu options
            switch (numInput) {
                case 1:
                    mainBudget.createBudget();
                    break;

                case 2:
                    mainBudget.changeBudget();
                    break;

                case 3:
                    mainBudget.useBudget();
                    break;

                case 4:
                    //Ends the program
                    return 0;

                default:
                    cout << "Invalid input please try again";
                    validInput = false;
            }
        }
    }
    validInput = false;
    while (!validInput) {
        string userMenuInput;
        string quotaName = mainBudget.getQuotaName();
        BudgetManipulation sortEverything(quotaName);
        cout << "+--------------------------------+\n";
        cout << "|What would you like to do?      |\n";
        cout << "|================================|\n";
        cout << "|1. Print                        |\n";
        cout << "|--------------------------------|\n";
        cout << "|2. Add expense or transcation   |\n";
        cout << "|--------------------------------|\n";
        cout << "|3. Delete expense or transaction|\n";
        cout << "|--------------------------------|\n";
        cout << "|4. Sort                         |\n";
        cout << "|--------------------------------|\n";
        cout << "|5. Save                         |\n";
        cout << "|--------------------------------|\n";
        cout << "|6. Graph                        |\n";
        cout << "|--------------------------------|\n";
        cout << "|7. Exit                         |\n";
        cout << "+--------------------------------+\n";
        cin >> userMenuInput;

        // Sends user input for the menu option chosen to the inputChecker function to ensure the input is a number.
        // If the input is not valid it will print an error message and reprint the menu.
        bool validInput = inputChecker(userMenuInput);
        vector<Transaction> localVector;
        if (!validInput) {
            cout << "Invalid input please try again\n";
        } else {
            // If the input is a number it will parse the input from a string to a integer and use this number to direct
            // the user to the chosen menu function.
            int numInput = stoi(userMenuInput);
            switch (numInput) {
                case 1:
                    cout << sortEverything.toString();
                    break;

                case 2:
                    mainBudget.addNewTransaction();
                    break;

                case 3:
                    mainBudget.deleteTransaction();
                    break;

                case 4:
                    SortMenu::sortOption(sortEverything);
                    mainBudget.saveTransactions(sortEverything.getSortedCategories());
                    break;

                case 5:
                    mainBudget.saveTransactions(sortEverything.getSortedCategories());
                    break;

                case 6:
                    //Graph code

                    break;

                case 7:

                    u.closingScreen();
                    return 0;

                default:
                    cout << "Invalid input please try again";
                    validInput = false;

            }
        }

    }
    return 0;
}