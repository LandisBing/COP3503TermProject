#include "ui.h"
#include <iostream>

//to initialize fitScreen for the cropData function; ensures that the bar graph stays reasonably on screen while still in proportion
BarGraph::BarGraph()
{
   maxBarLength = 100;
}

//sets the original money value vector
void BarGraph::setMoney(vector<int> mon)
{
    money = mon;
}

//sets the category vector
void BarGraph::setCats(vector<string> cat)
{
    category = cat;
}

//sets the total budget
void BarGraph::setBudget(int budg)
{
    budget = budg;
}

//sets the new, altered money value vector
void BarGraph::setRatio(vector<int> rat)
{
    ratio = rat;
}

//puts the data in terms of each other so that everything is proportional regardless of the size of the budget
vector<int> BarGraph::ratioData()
{
    //holds the ratio'd money amounts
    vector<int> newMoney;
    int listLength = money.size();

    //puts the original values in proportion to each other, converts to int (with expected loss in accuracy), and adds to new vector
    for (int i = 0; i < listLength; i++)
    {
        double moneyRatio = money[i];
        moneyRatio = (moneyRatio / budget) * 100;

        //rounds the number
        if ((moneyRatio + .5) >= (int(moneyRatio) + 1))
        {
            moneyRatio = int(moneyRatio) + 1;
            newMoney.push_back(moneyRatio);
        }
        else
        {
            moneyRatio = int(moneyRatio);
            newMoney.push_back(moneyRatio);
        }
    }

    return newMoney;
}

//handles everything involved in printing the bar graph
void BarGraph::printGraph()
{
    int listLengthCat = category.size();
    int listLengthMon = ratio.size();

    //separates graph from rest of code
    for (int i = 0; i < 115; i++)
    {
        cout << "-";
    }
    cout << endl;

    //centers the title of the bar graph
    for (int i = 0; i < 43; i++)
    {
        cout << " ";
    }
    cout << "BAR GRAPH\n" << endl;

    //finds the amount of digits in the largest number, for aid in making the category names line up on the graph
    int digits = 0;
    for (int i = 0; i < listLengthMon; i++)
    {
        int tempDigits = 0;
        int moneyCopy = money[i];

        /*divides the money amount by 10 multiple times to determine the number of digits. adds another digit because of how
        numbers not divisible by 10 end up*/
        while (moneyCopy != 0)
        {
            moneyCopy = moneyCopy / 10;
            tempDigits++;
        }
        //if the current number of digits is greater than the current greatest number of digits, replace it
        if (tempDigits > digits)
        {
            digits = tempDigits;
        }
        else
        {
            continue;
        }
    }

    //the actual process of printing and formatting the graph is contained here
    for (int i = 0; i < listLengthCat; i++)
    {
        int currentDigits = 0;
        string currentCat = category[i];
        int moneyAmount = ratio[i];

        /*counter: crucial for the formatting process. Keeps track of how many '|', spaces, and digits there are so that
        category titles displayed on the graph will line up properly*/
        int counter = 0;

        int moneyCopy = money[i];

        //once again finds the number of digits in the current number, to compare against the greatest number of digits and aid in formatting
        while (moneyCopy != 0 || moneyCopy > 1)
        {
            moneyCopy = moneyCopy / 10;
            currentDigits++;
        }

        //the graph will fill up with '|' until it reaches the number determined in cropData
        while (counter < moneyAmount)
        {
            cout << "|";
            counter++;

            //once all of the '|' have printed, put a space than the actual dollar amount the bar represents
            if (counter == moneyAmount)
            {
                cout << " " << money[i];
            }
        }

        //to cover the edge case of either 0 dollar amounts in a category or numbers that are much smaller than another category and thus get rounded down to 0 in the process
        if (moneyAmount == 0)
        {
            //if the amount is 0 because of the latter case mentioned...
            if (money[i] != 0)
            {
                cout << "| " << money[i];
                counter++;
            }
                //if the amount is 0 because of the former case mentioned...
            else
            {
                cout << money[i];
            }
        }

        //adds up the digits of the line so the counter can properly keep track of everything
        for (int i = 0; i < currentDigits; i++) {
            counter++;
        }

        //crucial, denotes the " " in between the bar and the value
        counter++;

        //finally, pads out the graph with spaces until the category name reaches the uniform position
        if (counter < (maxBarLength-currentDigits))
        {
            //fill in spaces where the maximum bar may be so as to assist in formatting
            for (int i = 0; i < (maxBarLength - counter); i++)
            {
                cout << " ";
            }
        }

        //finally print the category name
        cout << currentCat << endl;
    }

    //separates the bar graph from the rest of the code
    for (int i = 0; i < 115; i++)
    {
        cout << "-";
    }

    cout << endl;
}

//for use in making the program seem more sophisticated/like an actual program
void UserInterface::welcomeScreen()
{
    cout << " ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n";
    cout << " ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n";
    cout << " ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n";
    cout << " ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n";
    cout << " ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n";
    cout << " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n";

}

//for use in making the program seem more sophisticated/like an actual program
void UserInterface::closingScreen()
{
    cout << " ██████╗  ██████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███████╗██╗\n";
    cout << " ██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝██║\n";
    cout << " ██║  ███╗██║   ██║██║   ██║██║  ██║██████╔╝ ╚████╔╝ █████╗  ██║\n";
    cout << " ██║   ██║██║   ██║██║   ██║██║  ██║██╔══██╗  ╚██╔╝  ██╔══╝  ╚═╝\n";
    cout << "╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝██████╔╝   ██║   ███████╗██╗\n";
    cout << "╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝╚═╝\n";
}