#ifndef STACK_H
#define STACK_H

template <class T, int N>
class Stack
{
    public:
        Stack();
        ~Stack();
        Stack(const Stack& other);

        T push(T num);
        T pop();
        T peek();
        bool isEmpty();
        bool isFull();
        void display() const;
        Stack& operator = (const Stack &obj);

    private:
        const int m_maxSize = N;
        T m_array[N];
        int m_size;
};

#include "../src/Stack.cpp"
#endif // STACK_H
