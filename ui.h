#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
using namespace std;

//the class for graphing data received from other parts of the program
class BarGraph {
private:
    int maxBarLength;
    vector<int> money;
    vector<string> category;
    vector<int> ratio;
    int budget;
public:
    BarGraph();
    void setMoney(vector<int>);
    void setBudget(int);
    void setCats(vector<string>);
    void setRatio(vector<int>);
    vector<int> ratioData();
    void printGraph();
};

//the class responsible for the displays the user is greeted with
class UserInterface
{
public:
    void welcomeScreen();
    void closingScreen();
    void clearScreen();
};

//the class responsible for printing the data from other parts of the program
class DataFormatting
{
public:
    void billReminder();
    void budgetRemainder();
};

#endif
