#ifndef MIN_PRIORITY_QUEUE
#define MIN_PRIORITY_QUEUE

// implementation insert (del max) max
// unordered array 1 N N
// ordered array N 1 1
// binary heap log N log N 1
// d-ary heap logd N d logd N 1
// Fibonacci 1 log N † 1
// impossible 1 1 1

//also
// Immutability of keys.
// ・Assumption: client does not change keys while they're on the PQ.
// ・Best practice: use immutable keys
template <typename T>
class MinPQ
{
private:
    T *data;
    int capacity;
    int size;

    bool less(int, int);
    void exch(int, int);

    void swim(int);
    void sink(int);

    void resize(int);

    void del();

public:
    MinPQ();
    ~MinPQ();

    bool isEmpty() const;
    T delMin();
    void insert(const T &);
    int getSize();
    T getMin();
};

#endif
