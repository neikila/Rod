#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "drob.h"

using namespace std;

void printFormatMesAB () {
    cout << "Write fraction (format: \"a\\b\" where a/b)" << endl;
}

int main()
{
    Drob A;
    Drob B;
    char c = '+';
    int a, b;
    cout << "Operation (*+-/)" << endl;;
    printFormatMesAB();
    while(true) {
        c = '+';
        cin >> A;
        while (true) {
            while((c = getchar()) == ' ');
            if (c == '\n')
                break;
            cin >> B;
            cout << A << c << B << endl;
            switch(c) {
                case '+':
                    A = A + B;
                    break;
                case '-':
                    A = A - B;
                    break;
                case '*':
                    A = A * B;
                    break;
                case '/':
                    A = A / B;
                    break;
                case 'q':
                    cout << "Bye-bye" << endl;
                    exit(0);
                    break;
                default: cout << "Wrong operation: " << c << endl;
            }
            cout << "Result: ";
            cout << A << endl;
        }
    }
}
