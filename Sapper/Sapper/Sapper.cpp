#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

typedef const int keyPressedValue;
typedef const short int consolePosition;
typedef const int color;

char fileFirstTime[] = "first_time.txt";
HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);

consolePosition centerX = 45;
consolePosition centerY = 5;
keyPressedValue UP = 119, RIGHT = 100, DOWN = 115, LEFT = 97;
keyPressedValue Enter = 13;

color selected = 206;
color selectedNot = 62;
color black = 0;

void helpMenu() {
    system("cls");
    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY });
    cout << "Enter - Взаємодія з полем";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY + 1 });
    cout << "F - Поставити флаг";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY + 2 });
    cout << "УПРАВЛІННЯ:";
    SetConsoleTextAttribute(consoleWindow, black);


    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX, centerY + 4 });
    cout << "W";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX - 1, centerY + 5 });
    cout << "ASD";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY + 7 });
    SetConsoleTextAttribute(consoleWindow, selected);
    system("pause");
    SetConsoleTextAttribute(consoleWindow, black);
}


void menuHello() {
    int menuOption = 0;
    int exit = 1;
    int che = 0;

    do {
        SetConsoleTextAttribute(consoleWindow, selected);
        SetConsoleCursorPosition(consoleWindow, { centerX, centerY - 1 });
        cout << "САПЕР REALISE ";
        SetConsoleTextAttribute(consoleWindow, black);
        switch (1) {
        case 1: {

            SetConsoleCursorPosition(consoleWindow, { centerX + 1, centerY + 1 });
            if (menuOption == 0) {
                SetConsoleTextAttribute(consoleWindow, selected);
                cout << "> Нова гра" << endl;
            }
            else {
                SetConsoleTextAttribute(consoleWindow, selectedNot);
                cout << "Нова гра" << endl;
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        case 2: {

            SetConsoleCursorPosition(consoleWindow, { centerX + 1, centerY + 2 });
            if (menuOption == 1) {
                SetConsoleTextAttribute(consoleWindow, selected);
                cout << "> Допомога";
            }
            else {
                SetConsoleTextAttribute(consoleWindow, selectedNot);
                cout << "Допомога";
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        case 3: {

            SetConsoleCursorPosition(consoleWindow, { centerX + 1, centerY + 3 });
            if (menuOption == 2) {
                SetConsoleTextAttribute(consoleWindow, selected);
                cout << "> Таблиця лідерів";
            }
            else {
                SetConsoleTextAttribute(consoleWindow, selectedNot);
                cout << "Таблиця лідерів";
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        case 4: {
            SetConsoleCursorPosition(consoleWindow, { centerX + 1, centerY + 4 });
            if (menuOption == 3) {
                SetConsoleTextAttribute(consoleWindow, selected);
                cout << "> Вихід";
            }
            else {
                SetConsoleTextAttribute(consoleWindow, selectedNot);
                cout << "Вихід";
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        }

        switch (_getch()) {

        case UP: {
            menuOption > 0 ? menuOption-- : menuOption = 3;
            break;
        }

        case DOWN: {
            menuOption < 3 ? menuOption++ : menuOption = 0;
            break;
        }

        case Enter: {
            switch (menuOption) {
            case 0: {
                //authorization();
                break;
            }

            case 1: {
                helpMenu();
                break;
            }

            case 2: {
                //fileOpen();
                break;
            }

            case 3: {
                exit = 0;
                break;
            }
            }
            break;
        }
        }
        system("cls");
    } while (exit);
    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX,centerY + 3 });
    cout << "\tДо зустрічі!" << endl;
    SetConsoleCursorPosition(consoleWindow, { centerX,centerY + 7 });
    SetConsoleTextAttribute(consoleWindow, 15);
}

void firstTime() {
    int firstTime = 0;
    ifstream fileRead(fileFirstTime);
    ofstream fileCreate;
    if (fileRead.peek() == EOF) {
        fileCreate.open(fileFirstTime);
        fileCreate << ":)";
        helpMenu();
        system("cls");
    }
}

int main() {
    SetConsoleOutputCP(1251);
    firstTime();
    menuHello();
}