#include "MinPQ.h"
#include <cassert>

const int INITIAL_CAPACITY = 2;
const int INITIAL_SIZE = 0;

template <typename T>
MinPQ<T>::MinPQ() : size(INITIAL_SIZE), capacity(INITIAL_CAPACITY)
{
    this->data = new T[capacity];
}

template <typename T>
MinPQ<T>::~MinPQ()
{
    del();
}

template <typename T>
void MinPQ<T>::del()
{
    delete[] data;
}

template <typename T>
bool MinPQ<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
int MinPQ<T>::getSize()
{
    return size;
}

template <typename T>
T MinPQ<T>::getMin()
{
    return data[1];
}

template <typename T>
T MinPQ<T>::delMin()
{
    if (isEmpty())
    {
        throw "Queue empty.\n";
    }
    T max = data[1];
    exch(1, size--);
    sink(1);
    // delete data[size + 1];
    // if ((size > 0) && (size == (capacity - 1) / 4))
    //     resize(capacity / 2);
    return max;
}

template <typename T>
void MinPQ<T>::insert(const T &item)
{
    if (size == capacity - 1)
    {
        resize(capacity * 2);
    }
    data[++size] = item;
    swim(size);
}

template <typename T>
bool MinPQ<T>::less(int i, int j)
{
    return data[i] > data[j];
}

template <typename T>
void MinPQ<T>::exch(int i, int j)
{
    T t = data[i];
    data[i] = data[j];
    data[j] = t;
}

template <typename T>
void MinPQ<T>::swim(int x)
{
    while (x > 1 && less(x / 2, x))
    {
        exch(x / 2, x);
        x /= 2;
    }
}

template <typename T>
void MinPQ<T>::sink(int x)
{
    while (2 * x <= size)
    {
        int j = 2 * x;
        if (j < size && less(j, j + 1))
        {
            j++;
        }
        if (!less(x, j))
        {
            break;
        }
        exch(j, x);
        x = j;
    }
}

template <typename T>
void MinPQ<T>::resize(int newCapacity)
{
    assert(newCapacity > size);
    capacity = newCapacity;
    T *temp = new T[capacity];
    for (int i = 1; i <= size; i++)
    {
        temp[i] = data[i];
    }
    del();
    data = temp;
}