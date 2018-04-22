#ifndef BUDGET_QUOTA_H
#define BUDGET_QUOTA_H

#include <string>

using namespace std;

class Quota
{
private:
    int spendLimit;
    string category;
public:
    Quota();

    int getSpendLimit();

    void setSpendLimit(int newLimit);

    string getCategory();

    void setCategory(string newCategory);

};

#endif //BUDGET_QUOTA_H