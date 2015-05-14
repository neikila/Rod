#ifndef DROB
#define DROB

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

class Drob {
private:
    int a;
    int c;
public:
    bool isInt();
    int getIntBefore();

    Drob operator + (Drob);
    Drob operator + (int);
    Drob operator - (Drob);
    Drob operator - (int);
    Drob operator * (Drob);
    Drob operator * (int);
    Drob operator / (Drob);
    Drob operator / (int);
    Drob operator = (Drob);
    Drob(int cc = 1, int aa = 0): a(aa), c(cc) {};
    friend ostream &operator << (ostream &stream, Drob A);
    friend istream &operator >> (istream &stream, Drob &A);
    string str();
    bool operator > (int);
    bool operator > (Drob);
    bool operator < (Drob);
    bool operator == (Drob);
};

#endif
