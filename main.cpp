#include <iostream>
#include "Budget.h"
#include "sortmenu.cpp"


using namespace std;

// Checks if user input is a valid option. This is achieved by using a for loop to analyze the user input string. If any value
// is not a string it will return input as false.
bool inputChecker(string userInput) {
	bool isNum;
	for (int i = 0; i < userInput.length(); i++) {
		if (isdigit(userInput[i])) {
			isNum = true;
		}
		else {
			isNum = false;
		}
	}
	return isNum;
}


//Prints out user menu and asks takes user input for the menu options.
void userMenu() {
	bool validInput = false;
	
	while (!validInput) {
		string userMenuInput;
		cout << "+--------------------------------+\n";
		cout << "|What would you like to do?      |\n";
		cout << "|================================|\n";
		cout << "|1. Print                        |\n";
		cout << "|--------------------------------|\n";
		cout << "|2. Change budget amount	  |\n";
		cout << "|--------------------------------|\n";
		cout << "|3. Add expense or transcation   |\n";
		cout << "|--------------------------------|\n";
		cout << "|4. Delete expense or transaction|\n";
		cout << "|--------------------------------|\n";
		cout << "|5. Sort                         |\n";
		cout << "|--------------------------------|\n";
		cout << "|6. Save                         |\n";
		cout << "|--------------------------------|\n";
		cout << "|7. Graph                        |\n";
		cout << "|--------------------------------|\n";
		cout << "|8. Exit                         |\n";
		cout << "+--------------------------------+\n";
		cin >> userMenuInput;
		
		// Sends user input for the menu option chosen to the inputChecker function to ensure the input is a number.
		// If the input is not valid it will print an error message and reprint the menu.
		bool validInput = inputChecker(userMenuInput);
		if (!validInput) {
			cout << "Invalid input please try again\n";
		}
		else {
		// If the input is a number it will parse the input from a string to a integer and use this number to direct
		// the user to the chosen menu function.
			int numInput = stoi(userMenuInput);
			switch (numInput) {
				case 1:

					break;

				case 2:
					break;

				case 3:

					break;

				case 4:

					break;

				case 5:

					break;

				case 6:
					break;

				case 7: 
					//graphMoney = b.cropData(b.ratioData(moneyAmounts, totalBudget));
    					//b.printGraph(graphMoney, categoryList, moneyAmounts);   
					break;
					
				case 8:
					
					//closingScreen();
					return;
					
				default: 
					 cout << "Invalid input please try again";
					 validInput = false;

				}
			}

		}
	}

// Prints welcome menu that will ask user if they want to create a new budget, change existing budget, or use an existing budget.
void welcomeMenu() {
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
		}
		else {
			int numInput = stoi(welcomeInput);
			// switch statement has cases that correspond to the menu options
			switch (numInput) {
			case 1:
				break;

			case 2:
				break;

			case 3:
				break;

			case 4:
				break;

			default:
				cout << "Invalid input please try again\n";
				validInput = false;
			}
		}

	}
}



int main(){
    Budget mainBudget("account.txt");
    // mainBudget.parseQuotaData("abc.txt");
    //vector<Quota> myQuota = mainBudget.getAllQuotas();
/*
    for (int i = 0; i < 9; ++i) {
        cout << myQuota[i].getCategory() << " | " << myQuota[i].getSpendLimit() << endl;
    }*/

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
        }
        else {
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

                    break;

                default:
                    cout << "Invalid input please try again";
                    validInput = false;
            }
        }
    }

    mainBudget.closeFile();
    string quotaName = mainBudget.getQuotaName();
    BudgetManipulation sortEverything(quotaName);
    validInput = false;
    while (!validInput) {
        string userMenuInput;
        cout << "+--------------------------------+\n";
        cout << "|What would you like to do?      |\n";
        cout << "|================================|\n";
        cout << "|1. Print                        |\n";
        cout << "|--------------------------------|\n";
        cout << "|2. Change budget amount	  |\n";
        cout << "|--------------------------------|\n";
        cout << "|3. Add expense or transcation   |\n";
        cout << "|--------------------------------|\n";
        cout << "|4. Delete expense or transaction|\n";
        cout << "|--------------------------------|\n";
        cout << "|5. Sort                         |\n";
        cout << "|--------------------------------|\n";
        cout << "|6. Save                         |\n";
        cout << "|--------------------------------|\n";
        cout << "|7. Graph                        |\n";
        cout << "|--------------------------------|\n";
        cout << "|8. Exit                         |\n";
        cout << "+--------------------------------+\n";
        cin >> userMenuInput;

        // Sends user input for the menu option chosen to the inputChecker function to ensure the input is a number.
        // If the input is not valid it will print an error message and reprint the menu.
        bool validInput = inputChecker(userMenuInput);
        if (!validInput) {
            cout << "Invalid input please try again\n";
        }
        else {
            // If the input is a number it will parse the input from a string to a integer and use this number to direct
            // the user to the chosen menu function.
            int numInput = stoi(userMenuInput);
            switch (numInput) {
                case 1:

                    cout << sortEverything.toString();
                    break;

                case 2:
                    //superfluous
                    break;

                case 3:
                    mainBudget.addNewTransaction();
                    break;

                case 4:
                    mainBudget.deleteTransaction();
                    break;

                case 5:
                    SortMenu::sortOption(sortEverything);
                    break;

                case 6:
                {
                    vector<Transaction> sortedTransactions = sortEverything.getSortedCategories();

                    for(auto transaction: sortedTransactions)
                    {
                        cout << transaction.getCategory() + " | " + transaction.getName() + "$" + to_string(transaction.getAmount()) + " | " + transaction.getDate().toString() + "\n";
                    }
                    //what to call here?
                    break;
                }

                case 7:


                    break;

                case 8:

                    //u.closingScreen();
                    return 0;

                default:
                    cout << "Invalid input please try again";
                    validInput = false;

            }
        }

    }
    mainBudget.closeFile();
  
return 0;
}
