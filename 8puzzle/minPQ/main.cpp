#include <iostream>
#include "MinPQ.cpp"
#include <string>

#define TYPE int

int main()
{
    MinPQ<TYPE> *pq = new MinPQ<TYPE>;
    std::string word;
    while (std::cin >> word)
    {
        if (word.compare("-") == 0)
        {
            std::cout << "Min: " << pq->delMin() << "\n";
        }
        else
        {
            int val = stoi(word);
            pq->insert(val);
        }
    }

    delete pq;
    return 0;
}