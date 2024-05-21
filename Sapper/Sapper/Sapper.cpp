#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <limits>

using namespace std;

typedef const int keyPressedValue;
typedef const short int consolePosition;
typedef const int color;

char fileFirstTime[] = "first_time.txt";
char fileTempUser[] = "user_temp.txt";
char fileMainUsers[] = "users.txt";
HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);

consolePosition centerX = 45;
consolePosition centerY = 5;
keyPressedValue UP = 119, RIGHT = 100, DOWN = 115, LEFT = 97;
keyPressedValue Enter = 13;

color selected = 206;
color selectedNot = 62;
color black = 0;
color warningOrError = 79;

enum MenuOption { NEW_GAME, HELP, LEADERBOARD, EXIT, MENU_OPTIONS_COUNT };

struct user {
    string userName;
    string passWord;
    int score;
    int difficulty;
    int size;
    int sum;
};

int lines() {
    string check;
    ifstream file(fileMainUsers);
    int lines_count = 0;
    if (file.peek() == EOF)
    {
        return 0;
    }
    while (getline(file, check))
    {
        lines_count++;
    }

    file.close();
    return lines_count;
}

void fileBubleSort(int countOfLines, struct user ptr[]) {
    bool exit;
    short int centerMoveY = centerY;
    int tempSum = 0, tempScore = 0, tempSizeMap = 0, tempDifficulty = 0;
    string tempName, tempPassword;
    for (int i = 0; i < countOfLines; i++) {
        if (countOfLines > 1) {
            do {
                exit = false;
                for (int i = 0; i < countOfLines; i++) {
                    if (i + 1 != countOfLines && ptr[i + 1].sum > ptr[i].sum) {

                        tempSum = ptr[i].sum;
                        tempScore = ptr[i].score;
                        tempSizeMap = ptr[i].size;
                        tempDifficulty = ptr[i].difficulty;
                        tempName = ptr[i].userName;
                        tempPassword = ptr[i].passWord;

                        ptr[i].sum = ptr[i + 1].sum;
                        ptr[i].score = ptr[i + 1].score;
                        ptr[i].size = ptr[i + 1].size;
                        ptr[i].difficulty = ptr[i + 1].difficulty;
                        ptr[i].userName = ptr[i + 1].userName;
                        ptr[i].passWord = ptr[i + 1].passWord;

                        ptr[i + 1].sum = tempSum;
                        ptr[i + 1].score = tempScore;
                        ptr[i + 1].size = tempSizeMap;
                        ptr[i + 1].difficulty = tempDifficulty;
                        ptr[i + 1].userName = tempName;
                        ptr[i + 1].passWord = tempPassword;
                        exit = true;
                    }
                }
            } while (exit);
        }
    }
    for (int i = 0; i < countOfLines; i++) {
        SetConsoleCursorPosition(consoleWindow, { centerX - 40, centerMoveY });
        SetConsoleTextAttribute(consoleWindow, selected);
        cout << i + 1 << " Місце; - Нік: " << ptr[i].userName << " Мін залишилось: " << ptr[i].score << " Відсоток заповненості поля: " << ptr[i].difficulty << "%; Розмір поля: " << ptr[i].size << "; Рейтинг: " << ptr[i].sum;
        SetConsoleTextAttribute(consoleWindow, black);
        centerMoveY += 1;
    }
}

int fileOpen(int Comparison, string Name, string Password) {
    const int countOfLines = lines();
    int tempScore = 0, tempSizeMap = 0, tempDifficuty = 0, tempSum = 0;
    user* ptr = new user[countOfLines];
    bool exit = true;
    ifstream file(fileMainUsers);
    string tempName, tempPassword;
    system("cls");
    if (file.peek() == EOF)
    {
        if (Comparison == 0) {
            SetConsoleTextAttribute(consoleWindow, selected);
            SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY - 2 });
            cout << "Записів нема! Ви - перший!";
            SetConsoleTextAttribute(consoleWindow, black);

            SetConsoleCursorPosition(consoleWindow, { centerX - 5, centerY + 2 });
            SetConsoleTextAttribute(consoleWindow, selected);
            system("pause");
            SetConsoleTextAttribute(consoleWindow, black);
        }
        return 0;
    }
    for (int i = 0; i < countOfLines; i++) {
        file >> ptr[i].userName;
        file >> ptr[i].passWord;
        file >> ptr[i].score;
        file >> ptr[i].difficulty;
        file >> ptr[i].size;
        ptr[i].sum = ptr[i].difficulty + ptr[i].size - ptr[i].score;
        switch (Comparison) {
        case 1: {
            if (Name == ptr[i].userName) {
                return 1;
            }
        };
        case 2: {
            if (Name == ptr[i].userName) {
                if (Password == ptr[i].passWord) {
                    return -1;
                }
            }
        }
        }
    }
    file.close();

    if (Comparison == 1) {
        return 0;
    }
    else if (Comparison == 2) {
        return 1;
    }

    fileBubleSort(countOfLines, ptr);

    SetConsoleCursorPosition(consoleWindow, { centerX - 20, 0 });
    SetConsoleTextAttribute(consoleWindow, selected);
    system("pause");
    SetConsoleTextAttribute(consoleWindow, black);
    delete[]ptr;

    return 0;
}

void setTextColor(color col) {
    SetConsoleTextAttribute(consoleWindow, col);
}

void printCentered(consolePosition x, consolePosition y, const string& text, color col) {
    SetConsoleCursorPosition(consoleWindow, { x, y });
    setTextColor(col);
    cout << text;
    setTextColor(black);
}

void displayMenuOption(consolePosition y, const string& text, bool isSelected) {
    printCentered(centerX + 1, y, (isSelected ? "> " : "") + text, isSelected ? selected : selectedNot);
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

string inputPassword() {
    string passWord;
    do {
        system("cls");
        printCentered(centerX, centerY, "Введіть пароль(до 30 символів)!: ", selectedNot);
        setTextColor(selected);
        cin >> passWord;
        setTextColor(black);
    } while (passWord.size() > 30);
    SetConsoleTextAttribute(consoleWindow, black);
    return passWord;
}

string inputUsername() {
    string userName;
    do {
        system("cls");
        printCentered(centerX, centerY, "введіть нік(15 символів): ", selectedNot);
        setTextColor(selected);
        cin >> userName;
        setTextColor(black);
    } while (userName.size() > 15);

    return userName;
}

void authorizationTempFileInput(string userName, string passWord) {
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
        comparison = fileOpen(1, userName, "");

        if (comparison == 1) {
        passwordAgain:
            system("cls");

            do {
                printCentered(centerX, centerY - 1, "нік зайнято! введіть:", warningOrError);
                setTextColor(black);
                switch (1) {
                case 1: {
                    SetConsoleCursorPosition(consoleWindow, { centerX, centerY + 1 });
                    if (menuOption == 0) {
                        setTextColor(selected);
                        cout << "> Новий нік";
                    }
                    else {
                        setTextColor(selectedNot);
                        cout << "Новий нік";
                    }
                    setTextColor(black);
                }
                case 2: {
                    SetConsoleCursorPosition(consoleWindow, { centerX, centerY + 2 });
                    if (menuOption == 1) {
                        setTextColor(selected);
                        cout << "> Пароль";
                    }
                    else {
                        setTextColor(selectedNot);
                        cout << "Пароль";
                    }
                    setTextColor(black);
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
                authorization();
                break;
            case HELP:
                helpMenu();
                break;
            case LEADERBOARD:
                fileOpen(0, "", "");
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
    printCentered(centerX, centerY + 7, " ", 15);
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