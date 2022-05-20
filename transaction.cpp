#include <iostream>
#include "transaction.h"

int main()
{
    TransactionList tl = TransactionList("transactions.txt");   //m3naha eh?  // daa kda ndh el copy constr?
    TransactionList sorted = tl.sort();

    for (auto it = sorted.begin(); it != sorted.end(); ++it)
    {
        it->print();
        std::cout << std::endl;
    }

    return 0;
}
