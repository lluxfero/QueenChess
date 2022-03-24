#include <iostream>
#include <clocale>
#include <Windows.h>
#include <stdio.h>

using namespace std;
int k = 1;

void print_desk(int** D, int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < n; j++)
            cout << D[i][j] << "\t";
    }
    cout << endl;
}

int err_n() {
    int m, ival = 1;
    cin >> m;
    while (ival == 1) {
        if (cin.fail() || m < 3) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка! Попробуйте еще раз: ";
            cin >> m;
        }
        else
            ival = 0;
    }
    return m;
}

void set_occ(int** D, int n, int x, int y) {
    if (D[x][y] == 0) {
        for (int i = 0; i < 8; ++i) {
            if (D[i][y] == 0) D[i][y] = k;
            if (D[x][i] == 0) D[x][i] = k;
            int f;
            f = y - x + i;
            if (f >= 0 && f < n && D[i][f] == 0) D[i][f] = k;
            f = y - x - i;
            if (f >= 0 && f < n && D[i][f] == 0) D[i][f] = k;
        }
        D[x][y] = k;
        k++;
    }
}

void delete_occ(int** D, int n, int x, int y) {
    if (D[x][y] == k - 1) {
        for (int i = 0; i < 8; ++i) {
            if (D[i][y] == k - 1) D[i][y] = 0;
            if (D[x][i] == k - 1) D[x][i] = 0;
            int f;
            f = y - x + i;
            if (f >= 0 && f < n && D[i][f] == k - 1) D[i][f] = 0;
            f = y - x - i;
            if (f >= 0 && f < n && D[i][f] == k - 1) D[i][f] = 0;
        }
        D[x][y] = 0;
        k--;
    }
}

void set_queen(int** D, int n) {
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++) {
            set_occ(D, n, x, y);
        }
    print_desk(D, n);
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;

    cout << "Введите размер доски: ";
    n = err_n();

    int** desk = new int* [n];
    for (int i = 0; i < n; i++)
        desk[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            desk[i][j] = 0;

    set_queen(desk, n);
}