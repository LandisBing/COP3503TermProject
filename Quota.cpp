#include "Quota.h"

Quota::Quota() {
    spendLimit = 0;
}

int Quota::getSpendLimit() {
    return spendLimit;
}

void Quota::setSpendLimit(int newLimit) {
    spendLimit = newLimit;
}

string Quota::getCategory() {
    return category;
}

void Quota::setCategory(string newCategory) {
    category = newCategory;
}
