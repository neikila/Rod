#include "drob.h"

istream &operator >> (istream &stream, Drob &A) {
    char c;
    stream >> A.a;
    c = getchar();
    if (c != ' ' && c != '\n') {
        if (c != '/' && c != '\\') {
            cout << "Wrong format" << endl;
            exit(1);
        }
        stream >> A.c;
        if (A.c == 0) {
            cout << "Wrong c" << endl;
            exit(1);
        }
        A = A + Drob(1, 0);
    } else {
        A.c = 1;
    }
    return stream;
}

ostream &operator << (ostream &stream, Drob A) {
    stream << A.str();
    return stream;
}

int Drob::getIntBefore() {
    if (a >= 0)
        return a / c;
    else
        return (a / c) - 1;
}

bool Drob::isInt() {
    return c == 1;
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

Drob Drob::operator * (Drob A) {
    return Drob(c * A.c , a * A.a) + Drob(1,0);
}

Drob Drob::operator * (int A) {
    return Drob(c, a * A) + Drob(1,0);
}

Drob Drob::operator - (Drob A) {
    return *this + A * (-1);
}

Drob Drob::operator - (int A) {
    return Drob(c, a - c * A) + Drob(1,0);
}

Drob Drob::operator / (Drob A) {
    return Drob(c * A.a, a * A.c) + Drob(1,0);
}

Drob Drob::operator / (int A) {
    return Drob(c * A, a) + Drob(1,0);
}

Drob Drob::operator + (Drob A) {
    int temp_a, temp_c;
    temp_a = a * A.c + A.a * c;
    temp_c = c * A.c;

    int temp_NOK = GetNOK(temp_a, temp_c);
    temp_c /= temp_NOK;
    temp_a /= temp_NOK;

    if (temp_c < 0) {
        temp_c *= -1;
        temp_a *= -1;
    }
    return Drob(temp_c, temp_a);
}

Drob Drob::operator + (int A) {
    return Drob(c, a + c * A) + Drob(1,0);
}

string Drob::str() {
    stringstream stream;
    if (a != 0)
        stream << a;
    if (a == 0)
        stream << 0;
    if (c != 1)
        stream << "/" << c;
    return stream.str();
}

bool Drob::operator > (int A) {
    return (a - c * A) * c > 0;
}

bool Drob::operator > (Drob A) {
    Drob result = *this - A;
    return result.a * result.c > 0;
}

bool Drob::operator == (Drob A) {
    Drob result = *this - A;
    return result.a == 0;
}

Drob Drob::operator = (Drob A) {
    a = A.a;
    c = A.c;
    return *this;
}

bool Drob::operator < (Drob A) {
    Drob result = *this - A;
    return result.a * result.c < 0;
}
