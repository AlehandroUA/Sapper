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

enum MenuOption { NEW_GAME, HELP, LEADERBOARD, EXIT, MENU_OPTIONS_COUNT };

void setTextColor(color col) {
    SetConsoleTextAttribute(consoleWindow, col);
}

void printCentered(consolePosition x, consolePosition y, const string& text, color col) {
    SetConsoleCursorPosition(consoleWindow, { x, y });
    setTextColor(col);
    cout << text;
    setTextColor(black);
}

void helpMenu() {
    system("cls");
    printCentered(centerX - 5, centerY, "Enter - Взаємодія з полем", selected);
    printCentered(centerX - 5, centerY + 1, "F - Поставити флаг", selected);
    printCentered(centerX - 5, centerY + 2, "УПРАВЛІННЯ:", selected);
    printCentered(centerX, centerY + 4, "W", selected);
    printCentered(centerX - 1, centerY + 5, "ASD", selected);
    printCentered(centerX - 5, centerY + 7, "Натисніть будь-яку клавішу для продовження...", selected);
    _getch();
}
void authorizationTempFileInput(string userName,string passWord) {
    ofstream fileIn(fileTempUser);
    if (fileIn.is_open()) {
        fileIn << userName;
        fileIn << " ";
        fileIn << passWord;
    }
    fileIn.close();
}

void authorization() {
    system("cls");
    int comparison = 0;
    int menuOption = 0;
    int exit = 1;
    string passWord;
    string userName;
    do {
        nicknameenter:
        userName = inputUsername();
        comparison = fileOpen(1, userName,"");

        if (comparison == 1) {
            passwordAgain:
            system("cls");

            do {
                SetConsoleTextAttribute(consoleWindow, warningOrError);
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY - 1});
                cout << "нік зайнято! введіть:";
                SetConsoleTextAttribute(consoleWindow, black);
                switch (1) {
                    case 1: {
                        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 1});
                        if (menuOption == 0) {
                            SetConsoleTextAttribute(consoleWindow, selected);
                            cout << "> Новий нік";
                        }
                        else {
                            SetConsoleTextAttribute(consoleWindow, selectedNot);
                            cout << "Новий нік";
                        }
                        SetConsoleTextAttribute(consoleWindow, black);
                    }
                    case 2: {
                        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 2});
                        if (menuOption == 1) {
                            SetConsoleTextAttribute(consoleWindow, selected);
                            cout << "> Пароль";
                        }
                        else {
                            SetConsoleTextAttribute(consoleWindow, selectedNot);
                            cout << "Пароль";
                        }
                        SetConsoleTextAttribute(consoleWindow, black);
                    }
                }

                switch (_getch()) {
                case UP: {
                    menuOption > 0 ? menuOption-- : menuOption = 1;
                    break;
                }
                case DOWN: {
                    menuOption < 1 ? menuOption++ : menuOption = 0;
                    break;
                }
                case Enter: {
                    switch (menuOption) {
                        case 0: {
                            goto nicknameenter;
                        }
                        case 1: {
                            passWord = inputPassword();
                            comparison = fileOpen(2, userName, passWord);
                            if (comparison == 1) {
                                goto passwordAgain;
                            }
                            else {
                                exit = 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                }
                system("cls");
            } while (exit);
        }

    } while (comparison == 1);

    if (comparison == 0) {
        passWord = inputPassword();
    }

    authorizationTempFileInput(userName, passWord);
    difficultyMenu();
}

void displayMenuOption(consolePosition y, const string& text, bool isSelected) {
    printCentered(centerX + 1, y, (isSelected ? "> " : "") + text, isSelected ? selected : selectedNot);
}

void menuHello() {
    MenuOption menuOption = NEW_GAME;
    bool exit = false;

    do {
        system("cls");
        printCentered(centerX, centerY - 1, "САПЕР REALISE", selected);
        displayMenuOption(centerY + 1, "Нова гра", menuOption == NEW_GAME);
        displayMenuOption(centerY + 2, "Допомога", menuOption == HELP);
        displayMenuOption(centerY + 3, "Таблиця лідерів", menuOption == LEADERBOARD);
        displayMenuOption(centerY + 4, "Вихід", menuOption == EXIT);

        switch (_getch()) {
        case UP:
            menuOption = static_cast<MenuOption>((menuOption - 1 + MENU_OPTIONS_COUNT) % MENU_OPTIONS_COUNT);
            break;
        case DOWN:
            menuOption = static_cast<MenuOption>((menuOption + 1) % MENU_OPTIONS_COUNT);
            break;
        case Enter:
            switch (menuOption) {
            case NEW_GAME:
                // authorization();
                break;
            case HELP:
                helpMenu();
                break;
            case LEADERBOARD:
                // fileOpen();
                break;
            case EXIT:
                exit = true;
                break;
            }
            break;
        }
    } while (!exit);
    system("cls");
    printCentered(centerX, centerY + 3, "\tДо зустрічі!", selected);
    printCentered(centerX, centerY + 7, " ", 15); // Reset to white text
}

void firstTime() {
    ifstream fileRead(fileFirstTime);
    if (!fileRead || fileRead.peek() == EOF) {
        ofstream fileCreate(fileFirstTime);
        fileCreate << ":)";
        helpMenu();
    }
}

int main() {
    SetConsoleOutputCP(1251);
    firstTime();
    menuHello();
    return 0;
}

