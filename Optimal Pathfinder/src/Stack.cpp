#include <iostream>
#include "Stack.h"

#ifndef STACK_IMP
#define STACK_IMP

template <class T, int N> Stack<T, N>::Stack() : m_size(-1){}
template <class T, int N> Stack<T, N>::~Stack(){}

template <class T, int N> Stack<T, N>::Stack(const Stack& other) : m_maxSize(50)
{
    m_size = other.m_size;
    for(int i = 0; i <= m_size; ++i)
        m_array[i] = other.m_array[i];
}

template <class T, int N> T Stack<T, N>::push(T num)
{
    if( !isFull() )
    {
        ++m_size;
        m_array[m_size] = num;
        return num;
    }
    else
        return -1;
}

template <class T, int N> T Stack<T, N>::pop()
{
    if( !isEmpty() )
    {
        --m_size;
        return m_array[m_size + 1];
    }
    else
        return -1;
}

template <class T, int N> T Stack<T, N>::peek() { return m_array[m_size]; }
template <class T, int N> bool Stack<T, N>::isEmpty() { return (m_size == -1); }
template <class T, int N> bool Stack<T, N>::isFull() { return (m_size == m_maxSize - 1); }

template <class T, int N> void Stack<T, N>::display() const
{
    for(int i = 0; i <= m_size; i += 2)
        std::cout << m_array[i] << m_array[i + 1] << " -> ";
}

template <class T, int N> Stack<T, N>& Stack<T, N>::operator = (const Stack &obj)
{
    if(this == &obj || m_maxSize < obj.m_size)
        return *this;

    m_size = obj.m_size;
    for(int i = 0; i <= m_size; ++i)
        m_array[i] = obj.m_array[i];
    return *this;
}

#endif // STACK_IMP
