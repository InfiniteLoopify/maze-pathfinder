#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

class Dynamic2dArray {
private:
    char **m_array;
    int m_row;
    int m_col;
    char m_invalidMem = 0;    //a variable to be returned in bound check overload to show invalid data

private:
    void clearArray();

public:
    Dynamic2dArray();
    Dynamic2dArray(const Dynamic2dArray &obj);
    Dynamic2dArray(int r, int c);
    ~Dynamic2dArray();

    int getRow() const;
    int getCol() const;

    void readFile(const char* fileName);
    void writeFile(const char* fileName);
    void writeFile(const char* fileName, int i, int j);
    void writeFile(const char* fileName, const char* str);

    int findRow(char find);
    int findCol(char find);

    void fillArray(char ch);
    void display() const;

    char& operator() (int i, int j);
    Dynamic2dArray& operator= (const Dynamic2dArray &obj);
};


#endif // DYNAMICARRAY_H_INCLUDED
