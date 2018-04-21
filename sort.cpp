#include <algorithm>
#include <cmath>
#include "Budget.h"

using namespace std;

struct Expense
{
    string name;
    int amount;
    Date date;

    //prints expense
    string toString()
    {
        return this->name + "\t$" + to_string(this->amount) + "\t" + this->date.toString();
    }

    //sets everything
    void setExpenseName(string ExpenseName)
    {
        name = ExpenseName;
    }

    void setExpenseAmount(int expenseAmount)
    {
        amount = expenseAmount;
    }

    void setExpenseDate(Date expenseDate)
    {
        date = expenseDate;
    }

};

class Category
{
    public:
        string name;
        int budgetAmount = 0;
        vector<Expense> expenseVec;
        int percent = 0;

        void setBudgetAmount(int x)
        {
            budgetAmount = x;
        }

        void setCategoryName(string catName)
        {
            name = catName;
        }

        //prints category and their expenses
        string toString()
        {
            string printCategory;
            printCategory = this->name + "\t$" + to_string(budgetAmount) + "\t" + to_string(percent) + "%" + "\n";

            for (auto expense : expenseVec)
            {
                printCategory += "\t" + expense.toString() + "\n";
            }
            return printCategory;
        }

        //sorts all the expenses from either lowest to highest value or highest to lowest value
        void sortByExpenseName(bool lowToHigh)
        {
            //looks at the beginning of the line all the way to the end and uses a lambda expression
            //loops through all the expenses to see which order to sort in
            //compares the current expense to the following expense
            if (lowToHigh)
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.name.compare(b.name) < 0; });
            }
            else
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.name.compare(b.name) > 0; });
            }
        }

        void sortByExpenseAmount(bool lowToHigh)
        {
            if (lowToHigh)
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.amount < b.amount; });
            }
            else
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.amount > b.amount; });
            }
        }

        void sortByExpenseDate(bool lowToHigh)
        {
            if (lowToHigh)
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.date.compareTo(b.date) < 0; });
            }
            else
            {
                sort(expenseVec.begin(), expenseVec.end(), [](const Expense& a, const Expense& b) -> bool {  return a.date.compareTo(b.date) > 0; });
            }
        }
};

class BudgetManipulation
{
    public:

        vector<Category> categoryVec;

        // total amount of money user has to spend
        double totalBudget;
        /*
        the first percentage vector is the percentages per category
        that the user would like to be spending
        the second rPercentage is the real percentages per category that the user is spending based on the expenses
        */

        // vector of percentages based on inputted budget amount per category
        vector<int> percentages;

        // vector of percentages based on expenses per category
        vector<int> rPercentages;

        /*
        vector telling user how much money she has left to spend or gone
        over based on budget allowed per category, if value is negative it
        means the user has spent that amount of money over the budget for
        that category, if positive then that is amount left to spend for
        that category.
        */
        vector<int> underOver;

        //vector to get how much the budget is for each category
        vector<Quota> quotaVec;

        vector<Transaction> transactionVec;

        explicit BudgetManipulation(string quotaName)
        {
            Budget myBudget("account.txt");
            myBudget.parseQuotaData(quotaName);
            this->transactionVec = myBudget.getAllTransactions();
            this->quotaVec = myBudget.getAllQuotas();
            setCategories();
            setQuotas();
            calcTotalBudget();
            calculatePercentages();
            setCatPercent();
            setExpenses();
        }

        string toString()
        {
            string printBudget;

            for (auto category : categoryVec)
            {
                printBudget += category.toString() + "\n\n";
            }
            return printBudget;
        }

        void setCategories()
        {
            for (auto transactions : transactionVec)
            {
                string categoryName = transactions.getCategory();

                auto iterator = find_if(categoryVec.begin(), categoryVec.end(), [&categoryName](const Category& cat) {return cat.name == categoryName; });
                if (iterator == categoryVec.end())
                {
                    Category category = Category();
                    category.setCategoryName(categoryName);
                    //makes new category
                    categoryVec.push_back(category);
                }
                else
                {
                    (*iterator).setCategoryName(categoryName);
                }
            }
        }

        void setCatPercent()
        {
            for (int i = 0; i <= percentages.size(); i++)
            {
                categoryVec[i].percent = percentages[i];
            }
        }

        void setExpenses()
        {
            for (auto transactions : transactionVec)
            {
                string categoryName = transactions.getCategory();
                string expenseName = transactions.getName();
                double expenseAmount = transactions.getAmount();
                Date expenseDate = transactions.getDate();

                Expense expense = Expense();
                expense.setExpenseName(expenseName);
                expense.setExpenseAmount(expenseAmount);
                expense.setExpenseDate(expenseDate);

                auto iterator = find_if(categoryVec.begin(), categoryVec.end(), [&categoryName](const Category& cat) {return cat.name == categoryName; });
                if (iterator != categoryVec.end())
                {
                    (*iterator).expenseVec.push_back(expense);
                }
            }
        }

        void setQuotas()
        {
            for (int i = 0; i <= quotaVec.size(); i++)
            {
                categoryVec[i].setBudgetAmount(quotaVec[i].getSpendLimit());
            }
        }

        vector<Transaction> getSortedCategories()
        {
            vector<Transaction> sortedTranVec;
            for(auto category: categoryVec)
            {
                for(auto expense: category.expenseVec)
                {
                    Transaction tran;
                    tran.setCategory(category.name);
                    tran.setName(expense.name);
                    tran.setAmount(expense.amount);
                    auto date = expense.date;
                    tran.setDate(date.month, date.day, date.year);

                    sortedTranVec.push_back(tran);
                }
            }
            return sortedTranVec;
        }

        //sums total budget of user based on budget amount for each category
        void calcTotalBudget()
        {
            double sum = 0;
            for (auto category : categoryVec)
            {
                sum += category.budgetAmount;
            }
            this->totalBudget = sum;
        }

        void sortByCategoryName(bool lowToHigh)
        {
            if (lowToHigh)
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.name.compare(b.name) < 0; });
            }
            else
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.name.compare(b.name) > 0; });
            }
        }

        void sortByCategoryBudget(bool lowToHigh)
        {
            if (lowToHigh)
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.budgetAmount < b.budgetAmount; });
            }
            else
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.budgetAmount > b.budgetAmount; });
            }
        }

        void sortByCategoryPercentage(bool lowToHigh)
        {
            if (lowToHigh)
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.percent < b.percent; });
            }
            else
            {
                sort(categoryVec.begin(), categoryVec.end(), [](const Category& a, const Category& b) -> bool {  return a.percent > b.percent; });
            }
        }

        void sortByExpensesName(bool lowToHigh)
        {
            for (auto & category : categoryVec)
            {
                category.sortByExpenseName(lowToHigh);
            }
        }

        void sortByExpensesAmount(bool lowToHigh)
        {
            for (auto & category : categoryVec)
            {
                category.sortByExpenseAmount(lowToHigh);
            }
        }

        void sortByExpensesDate(bool lowToHigh)
        {
            for (auto & category : categoryVec)
            {
                category.sortByExpenseDate(lowToHigh);
            }
        }

        /*
        calculates percent of total budget used by each category based on
        budget amount
        */
        void calculatePercentages()
        {
            for (auto category : categoryVec)
            {
                percentages.push_back(round(100 * (category.budgetAmount / totalBudget)));
            }
        }

        /*
        calculates percent of total budget used by each category based on
        expenses for that category
        */
        void calculateRPercentages()
        {
            for (auto category : categoryVec)
            {
                double amount = 0;
                for (auto expense : category.expenseVec)
                {
                    amount += expense.amount;
                }
                rPercentages.push_back(round(100 * (amount / totalBudget)));
            }
        }

        /*
        calculates amount left to spend or amount gone over in each category
        */
        void calcHowMuchLeft()
        {
            int amount;
            for (auto category : categoryVec)
            {
                amount = 0;
                for (auto expense : category.expenseVec)
                {
                    amount += expense.amount;
                }
                int left = category.budgetAmount - amount;
                underOver.push_back(left);
            }
        }
};