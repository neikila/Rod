#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "drob.h"

using namespace std;

const size_t width = 5;
const char filler = '-';

void output(vector < vector < Drob > > mas) {
    for (int i = 0; i < mas.size(); ++i) {
        cout << '|';
        for (int j = 0; j < mas[i].size(); ++j) {
            cout.fill(' ');
            cout.width(width);
            cout << mas[i][j].str() << '|';
        }
        cout << endl;
        cout << filler;
        for (int j = 0; j < mas[i].size(); ++j) {
            cout.fill(filler);
            cout.width(width + 1);
            cout << filler;
        }
        cout << endl;
    }
}

size_t getJ(vector < vector < Drob > > mas, size_t &iFound) {
    vector < Drob > curent = mas[iFound];
    size_t j = 0;
    for (size_t i = 1; i < curent.size() && j == 0; ++i) {
        if (!(curent[i] == Drob(1, 0))) {
            j = i;
        }
    }
    return j;
}

void getIJ(vector < vector < Drob > > mas, size_t &iFound, size_t &jFound) {
    vector < Drob > z = mas[0];
    Drob min = z[1];
    size_t minId = 1;
    for (size_t i = 2; i < z.size(); ++i) {
        if (z[i] < min) {
            min = z[i];
            minId = i;
        }
    }

    min = mas[1][minId];
    size_t minVertId = 0;
    for (size_t i = 2; i < mas.size(); ++i) {
        if (mas[i][minId] > 0) {
            if (mas[i][minId] < min || minVertId == 0) {
                min = mas[i][minId];
                minVertId = i;
            }
        }
    }

    iFound = minVertId;
    jFound = minId;
}

void toDefault(vector < vector < Drob > > &mas, size_t iEl, size_t jEl) {
    Drob temp = mas[iEl][jEl];
    if (temp == Drob(1, 0)) 
        return;
    for (int j = 0; j < mas[iEl].size(); ++j) {
        mas[iEl][j] = mas[iEl][j] / temp;
    }
}

void differ(vector < vector < Drob > > &mas, size_t iEl, size_t jEl) {
    Drob temp = mas[iEl][jEl];
    if (temp == Drob(1, 0)) 
        return;
    for (int i = 0; i < mas.size(); ++i) {
        if (i != iEl) {
            for (int j = 0; j < mas[iEl].size(); ++j) {
                if (j != jEl) {
                    mas[i][j] = mas[i][j] - mas[iEl][j] / temp * mas[i][jEl];
                }
            }
        }
    }
}

void divide(vector < vector < Drob > > &mas, size_t iEl, size_t jEl) {
    Drob temp = mas[iEl][jEl] * (-1);
    if (temp == Drob(1, 0)) 
        return;
    for (int i = 0; i < mas.size(); ++i) {
        mas[i][jEl] = mas[i][jEl] / temp;
    }
}


vector < Drob >  getNextLine(vector < vector < Drob > > &mas) {
    vector < Drob > nextLine(0);

    size_t toEdit = mas.size();

    for (int i = 0; i < mas.size() && toEdit > i; ++i) {
        if (!mas[i][0].isInt()) {
            toEdit = i;
        }
    }

    if (toEdit != mas.size()) {
        for(int j = 0; j < mas[toEdit].size(); ++j) {
            Drob temp = (mas[toEdit][j] - mas[toEdit][j].getIntBefore()) * (-1);
            nextLine.push_back(temp);
        }

    }

    return nextLine;
}

void toZero(vector < vector < Drob > > &mas, size_t iEl, size_t jEl) {
    for (int j = 0; j < mas[iEl].size(); ++j) {
        if (j != jEl) {
            mas[iEl][j] = Drob(1, 0);
        }
    }
}

int main() {
    Drob A;
    Drob B;
    int a, b;
    size_t sizeX, sizeY;
    cin >> sizeX >> sizeY;
    vector < vector < Drob > > mas(0);
    for (size_t i = 0; i < sizeY; ++i) {
        vector < Drob > temp(0);
        for (size_t j = 0; j < sizeX; ++j) {
            cin >> A;
            temp.push_back(A);
        }
        mas.push_back(temp);
    }
    cout << mas.size() << '|' << mas[0].size() << endl;
    output(mas);

    size_t minI, minJ;

    getIJ(mas, minI, minJ);

    cout << "i = " << minI << " | j = " << minJ << endl;

    if (mas[minI][minJ] == Drob(1, 0)) {
        cout << "Error. Dividing to zero.\n";
        exit(-1);
    }

    Drob save = mas[minI][minJ];

    toDefault(mas, minI, minJ);
    output(mas);

    putchar('\n');
    differ(mas, minI, minJ);
    output(mas);

    putchar('\n');
    mas[minI][minJ] = save;
    divide(mas, minI, minJ);
    toZero(mas, minI, minJ);
    output(mas);

    vector < Drob > nextLine = getNextLine(mas);
    while (nextLine.size() != 0) {
        mas.push_back(nextLine);
        putchar('\n');
        output(mas);
        minI = mas.size() - 1;
        minJ = getJ(mas, minI);
        cout << "i = " << minI << " | j = " << minJ << endl;

        if (mas[minI][minJ] == Drob(1, 0)) {
            cout << "Error. Dividing to zero.\n";
            exit(-1);
        }

        save = mas[minI][minJ];

        toDefault(mas, minI, minJ);
        output(mas);

        putchar('\n');
        differ(mas, minI, minJ);
        output(mas);

        putchar('\n');
        mas[minI][minJ] = save;
        divide(mas, minI, minJ);
        toZero(mas, minI, minJ);
        output(mas);
        nextLine = getNextLine(mas);
    }
    cout << "Result:" << endl;
    output(mas);

    for (int i = 0; i < mas.size(); ++i) {
        cout << "X" << i + 1 << " = " << mas[i][0] << endl;
    }
}
