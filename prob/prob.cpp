#include <iostream>
#include <clocale>
#include <Windows.h>
#include <stdio.h>

using namespace std;

void print_desk(int** D, int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < n; j++) {
            if (D[i][j] == -1) cout << 1 << "\t";
            else cout << 0 << "\t";
        }
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

void set_queen(int** D, int n, int i, int j) {
    for (int x = 0; x < 8; ++x) {
        ++D[x][j];
        ++D[i][x];
        int f;
        f = j - i + x;
        if (f >= 0 && f < n) ++D[x][f];
        f = j - i - x;
        if (f >= 0 && f < n) ++D[x][f];
    }
    D[i][j] = -1;
}

void delete_queen(int** D, int n, int i, int j) {
    for (int x = 0; x < 8; ++x) {
        --D[x][j];
        --D[i][x];
        int f;
        f = j - i + x;
        if (f >= 0 && f < n) --D[x][f];
        f = j - i - x;
        if (f >= 0 && f < n) --D[x][f];
    }
    D[i][j] = 0;
}

bool check_pos(int** D, int n, int i) {
    bool r = false;
    for (int j = 0; j < n; ++j) {
        if (D[i][j] == 0) {
            set_queen(D, n, i, j);
            if (i == n - 1) r = true;
            else
                if (!(r = check_pos(D, n, i + 1))) delete_queen(D, n, i, j);
        }
        if (r) break;
    }
    return r;
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int x0, y0, n;

    cout << "Введите размер доски: ";
    n = err_n();

    int** desk = new int* [n];
    for (int i = 0; i < n; i++)
        desk[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            desk[i][j] = 0;

    check_pos(desk, n, 0);

    print_desk(desk, n);
}