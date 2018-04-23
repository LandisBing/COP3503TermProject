#include "sort.cpp"

class SortMenu
{
public:
    //call method on class without creating class first
    //implements function
    static void sortOption(BudgetManipulation &sortEverything)
    {
        int choice;
        while (true)
        {
            cout << "\nWhat do you want to sort?\n"
                    "1. Categories\n"
                    "2. Expenses\n"
                    "3. Back\n";
            cin >> choice;

            if (choice == 1)
            {
                sortCategories(&sortEverything);
                break;
            }
            else if (choice == 2)
            {
                sortExpenses(&sortEverything);
                break;
            }
            else if (choice == 3)
            {
                break;
            }
            else //loops back to submenu
            {
                cout << "Please enter a number from the menu." << endl;
            }
        }
    };

private:
    //call method on class without creating class first
    static void sortCategories(BudgetManipulation* sortEverything)
    {
        int choice;
        while (true)
        {
            cout << "\nHow do you want to sort categories?\n"
                    "1. Name\n"
                    "2. Budget Amount\n"
                    "3. Budget Percentage\n"
                    "4. Back\n";
            cin >> choice;

            if (choice == 1)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByCategoryName(lowToHigh); //lowToHigh false which actually makes it highToLow
                break;
            }
            else if (choice == 2)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByCategoryBudget(lowToHigh);
                break;
            }
            else if (choice == 3)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByCategoryPercentage(lowToHigh);
                break;
            }
            else if (choice == 4)
            {
                break;
            }
            else
            {
                cout << "Please enter a number from the menu." << endl;
            }
        }
    };

    static void sortExpenses(BudgetManipulation* sortEverything)
    {
        int choice;
        while (true)
        {
            cout << "\nHow do you want to sort expenses?\n"
                    "1. Name\n"
                    "2. Expense Amount\n"
                    "3. Date\n"
                    "4. Back\n";
            cin >> choice;

            if (choice == 1)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByExpensesName(lowToHigh);
                break;

            }
            else if (choice == 2)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByExpensesAmount(lowToHigh);
                break;
            }
            else if (choice == 3)
            {
                bool lowToHigh = selectSortOrder();
                sortEverything->sortByExpensesDate(lowToHigh);
                break;
            }
            else if (choice == 4)
            {
                break;
            }
            else
            {
                cout << "Please enter a number from the menu." << endl;
            }
        }
    }

    static bool selectSortOrder()
    {
        int choice;
        while (true)
        {
            cout << "\nWhich order do you want to sort in?\n"
                    "1. Low to High\n"
                    "2. High to low\n"
                    "3. Back\n";
            cin >> choice;

            if (choice == 1)
            {
                return true;
            }
            else if (choice == 2)
            {
                return false;
            }
            else if (choice == 3)
            {
                break;
            }
            else
            {
                cout << "Please enter a number from the menu." << endl;
            }
        }
    }
};
