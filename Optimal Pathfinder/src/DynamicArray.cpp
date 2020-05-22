#include "DynamicArray.h"
#include <fstream>
#include <iostream>
#include <cstring>

Dynamic2dArray::Dynamic2dArray()
{
    m_array = nullptr;
    m_row = 0;
    m_col = 0;
}

Dynamic2dArray::Dynamic2dArray(const Dynamic2dArray &obj)
{
    m_array = nullptr;
    m_row = 0;
    m_col = 0;
    *this = obj;    //call = operator
}

Dynamic2dArray::Dynamic2dArray(int r, int c)
{
    m_row = r;
    m_col = c;
    m_array = new char*[m_row];

    for(int i = 0; i < m_row; ++i)
    {
        m_array[i] = new char[m_col];
        //initialize 2d array to character '?'
        for(int j = 0; j < m_col; ++j)
            m_array[i][j] = '?';
    }
}

Dynamic2dArray::~Dynamic2dArray()
{
    clearArray();
}

void Dynamic2dArray::clearArray()
{
    //if array is not empty than delete allocated memory
    if(m_array != nullptr)
    {
        for(int i = m_row - 1; i >= 0; --i)
        {
            if(m_array[i] != nullptr)
            {
                delete[] m_array[i];
                m_array[i] = nullptr;
            }
        }
        delete[] m_array;
    }
    m_array = nullptr;
}

int Dynamic2dArray::getRow() const {return m_row;}
int Dynamic2dArray::getCol() const {return m_col;}

//read data from the file
void Dynamic2dArray::readFile(const char* fileName)
{
    std::ifstream inf(fileName);
    //if file cannot open
    if(!inf)
    {
        std::cout << "Cannot open File " << fileName << std::endl;
        std::cin.get();
        exit(1);
    }
    clearArray();

    inf >> m_row;
    inf >> m_col;

    m_array = new char*[m_row];

    for(int i = 0; i < m_row; ++i)
    {
        m_array[i] = new char[m_col];
    }

    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            char ch;
            if(!inf)
            {
                std::cout << "File Format is Invalid for " << fileName << std::endl;
                std::cin.get();
                exit(1);
            }
            //read characters from file and save in array
            inf >> ch;
            m_array[i][j] = ch;
        }
    }
}

//write the whole array into a file
void Dynamic2dArray::writeFile(const char* fileName)
{
    std::ofstream outf(fileName, std::ios::app);
    outf << "\n";
    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            outf << m_array[i][j] << " ";
        }
        outf << "\n";
    }
}

//write only a single coordinate onto file
void Dynamic2dArray::writeFile(const char* fileName, int i, int j)
{
    std::ofstream outf(fileName, std::ios::app);
    outf << "(" << i << ", " << j << ")\n";
}

//write a string on the file
void Dynamic2dArray::writeFile(const char* fileName, const char* str)
{
    std::ofstream outf(fileName, std::ios::app);
    outf << str << "\n";
}

//return the row in which the character is found
int Dynamic2dArray::findRow(char find)
{
    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            if(m_array[i][j] == find)
                return i;
        }
    }
    std::cout << "Character " << find << " not found\n";
    return -1;
}

//return the column in which the character is found
int Dynamic2dArray::findCol(char find)
{
    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            if(m_array[i][j] == find)
                return j;
        }
    }
    std::cout << "Character " << find << " not found\n";
    return -1;
}

//fill the whole array with a character provided by user
void Dynamic2dArray::fillArray(char ch)
{
    for(int i = 0; i < m_row; ++i)
        for(int j = 0; j < m_col; ++j)
            m_array[i][j] = ch;
}

//display the array
void Dynamic2dArray::display() const
{
    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            std::cout << m_array[i][j] << " ";
        }
        std::cout << "\n";
    }
}

//make sure the array is inside bound
char& Dynamic2dArray::operator() (int i, int j)
{
    if((i >= 0 && i < m_row) && (j >= 0 && j < m_col))
        return m_array[i][j];
    else
        return m_invalidMem;    //return address of invalid memory if array is out of bound
}

Dynamic2dArray& Dynamic2dArray::operator= (const Dynamic2dArray &obj)
{
    if(this == &obj)
        return *this;

    //clear data from array
    clearArray();
    this->m_row = obj.m_row;
    this->m_col = obj.m_col;
    m_array = new char*[m_row];

    //copy data from object to current object
    for(int i = 0; i < m_row; ++i)
    {
        m_array[i] = new char[m_col];
        memcpy(m_array[i], obj.m_array[i], sizeof(char) * m_col);
    }
    return *this;
}
