
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Drob {
private:
    int a;
    int b;
    int c; // (a+bM)/c
public:
    Drob operator + (Drob);
    Drob operator - (Drob);
    Drob operator * (int);
    Drob operator * (Drob);
    Drob(int cc = 1, int aa = 0, int bb = 0): a(aa), b(bb), c(cc) {};
    friend ostream &operator << (ostream &stream, Drob A);
    friend istream &operator >> (istream &stream, Drob &A);
};

istream &operator >> (istream &stream, Drob &A) {
    stream >> A.a >> A.b >> A.c;
    if (A.c == 0) {
        cout << "Wrong c" << endl;
        exit(1);
    }
    A = A + Drob(1, 0, 0);
    return stream;
} 

ostream &operator << (ostream &stream, Drob A) {
    if (A.b != 0 && A.a != 0)
        stream << '('; 
    if (A.a != 0)
        stream << A.a;
    if (A.b > 0 && A.a != 0)
        stream << " + ";
    if (A.b != 0)
        stream << A.b << "M";
    if (A.b != 0 && A.a != 0)
        stream << ")";
    if (A.b == A.a && A.a == 0)
        stream << 0;
    if (A.c != 1)
        stream << "/" << A.c;
    return stream;
} 

int abs(int a) {
    return a >= 0? a: -a;
}

int GetNOK(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (b == 0) {
        return a == 0? 1: a;
    }
    if (a == 0) {
        return b == 0? 1: b;
    }
    while(a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

Drob Drob::operator * (int A) {
    return Drob(c, a * A, b * A) + Drob(1,0,0);
}

Drob Drob::operator * (Drob A) {
    return Drob(c * A.c , a * A.a, b * A.a) + Drob(1,0,0);
}

Drob Drob::operator - (Drob A) {
    return *this + A * (-1);
}


Drob Drob::operator + (Drob A) {
    int temp_a, temp_b, temp_c;
    temp_a = a * A.c + A.a * c;
    temp_b = b * A.c + A.b * c;
    temp_c = c * A.c;
    
    int temp_NOK = GetNOK(temp_a, temp_b);
    temp_a /= temp_NOK;
    temp_b /= temp_NOK;
    int temp_NOK_2;
    if (temp_a == temp_b && temp_a == 0)
        temp_NOK_2 = temp_c;
    else
        temp_NOK_2 = GetNOK(temp_NOK, temp_c);
    temp_NOK /= temp_NOK_2;
    temp_c /= temp_NOK_2;

    temp_a *= temp_NOK;
    temp_b *= temp_NOK;
    return Drob(temp_c, temp_a, temp_b);
}

int main() {
    Drob A;
    Drob B;
    char c;
    int a, b;
    while(true) {
        cout << "Write first fraction (format: \"a b c\" where (a + bM)/c): ";
        cin >> A;
        cout << A << endl;
        cout << "Operation (*+-): ";
        cin >> c;
        if (c == '*') {
            cout << "Write fraction (format: \"a b\" where a/b): ";
            cin >> a >> b;
            if (b == 0) {
                cout << "Wrong b" << endl;
                exit(1);
            }
            cout << a << "/" << b << endl;
            B = Drob(b, a, 0); 
            cout << "Result: " << endl;
            cout << A * B << endl;
        }
        if (c == '-' || c == '+') {
            cout << "Write second fraction (format: \"a b c\" where (a + bM)/c): ";
            cin >> B;
            cout << B << endl;
            cout << "Result: " << endl;
            if (c == '-') {
                cout << A - B << endl;
            } else {
                cout << A + B << endl;
            }
        }
        while (getchar()!='\n');
    }
}
