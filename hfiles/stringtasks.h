//
// Created by Keller3D on 29.04.2025.
//
using namespace std;
#ifndef PROGA2_TWELVETASKS_H
#define PROGA2_TWELVETASKS_H
#include <cstring>
#endif //PROGA2_TWELVETASKS_H
void task1() {
    ifstream in("files/in1.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int count = 0;
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == '.') break;
        if (line[pos] == ' ') {
            flag = false;
        } else if (!flag) {
            flag = true;
            count++;
        }
        pos++;
    }
    cout << count;
}

void task2() {
    ifstream in("files/in2.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int count = 0;
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == ' ') {
            flag = false;
        } else if (!flag) {
            flag = true;
            if (line[pos] == 'b' || line[pos] == 'B') count++;
        }
        pos++;
    }
    cout << count;
}

void task3() {
    ifstream in("files/in3.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int max_len = INT_MIN;
    int min_len = INT_MAX;
    int pos = 0;
    int cur_len = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (flag && line[pos] == ' ') {
            flag = false;
            max_len = max(cur_len, max_len);
            min_len = min(cur_len, min_len);
            cur_len = 0;
        } else if (!flag && line[pos] != ' ') {
            flag = true;
            cur_len++;
        } else if (flag && line[pos] != ' ') {
            cur_len++;
        }
        pos++;
    }
    if (flag) {
        max_len = max(cur_len, max_len);
        min_len = min(cur_len, min_len);
    }
    cout << min_len << endl;
    cout << max_len << endl;
}

void task4() {
    ifstream in("files/in4.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == ')') {
            break;
        }
        if (line[pos] == '(') {
            flag = true;
        } else if (flag) {
            cout << line[pos];
        }
        pos++;
    }
}

void task5() {
    ifstream in("files/in5.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    while (line[pos + 2] != '\0') {
        if (line[pos] == 'a' && line[pos + 1] == 'b' && line[pos + 2] == 'c') {
            count++;
        }
        pos++;
    }
    cout << count;
}

void task6() {
    ifstream in("files/in6.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    while (line[pos] != '\0') {
        if (line[pos] == 'k') {
            count++;
        } else if (line[pos] == ' ') {
            count = 0;
        }
        pos++;
    }
    cout << count;
}

bool subchar(char *arr, char elem) {
    for (int i = 0; i < strlen(arr); i++) {
        if (elem == arr[i]) {
            return true;
        }
    }
    return false;
}

void task7() {
    ifstream in("files/in7.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    char c[500];
    while (line[pos] != '\0') {
        if (!subchar(c, line[pos])) {
            c[count] = line[pos];
            count++;
        }
        pos++;
    }
    cout << count;
}

void task8() {
    ifstream in("files/in8.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    int max_a = 0;
    bool f = false;
    while (line[pos] != '\0') {
        if (line[pos] == 'a' && !f) {
            f = true;
            count = 1;
        } else if (line[pos] == 'a' && f) {
            count++;
            max_a = max(max_a, count);
        } else if (line[pos] != 'a') {
            f = false;
            count = 0;
        }
        pos++;
    }
    cout << max_a;
}

void task9() {
    ifstream in("files/in9.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int index = 0;
    char word[500] = "";
    bool flag = false;
    while (line[pos] != '\0') {
        if (flag && line[pos] == ' ') {
            if (word[index - 1] == word[0]) {
                for (int i = 0; i < index; i++) {
                    cout << word[i];
                }
            }
            cout << ' ';
            index = 0;

        } else if (flag && line[pos] != ' ') {
            word[index] = line[pos];
            index++;
        } else if (!flag && line[pos] == ' ') {
            continue;
        } else {
            flag = true;
            word[index] = line[pos];
            index++;
        }
        pos++;
    }
    if (word[index - 1] == word[0]) {
        for (int i = index - 1; i >= 0; i--) {
            cout << word[i];
        }
    }
}

void task10() {
    ifstream in("files/in10.txt");
    char line[500];
    in.getline(line, sizeof(line));
    for (int i = 0, j = strlen(line) - 1; i < j; i++, j--) {
        if (line[i] != line[j]) {
            cout << false;
            return;
        }
    }
    cout << true;
}

void task11() {
    ifstream in("files/in11.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int index = 0;
    char word[500] = "";
    bool flag = false;
    while (line[pos] != '\0') {
        if (flag && line[pos] == ' ') {
            for (int i = index - 1; i >= 0; i--) {
                cout << word[i];
            }
            cout << ' ';
            index = 0;

        } else if (flag && line[pos] != ' ') {
            word[index] = line[pos];
            index++;
        } else if (!flag && line[pos] == ' ') {
            continue;
        } else {
            flag = true;
            word[index] = line[pos];
            index++;
        }
        pos++;
    }
    for (int i = index - 1; i >= 0; i--) {
        cout << word[i];
    }
}

void task12() {
    ifstream in("files/in12.txt");
    char a[500];
    char b[500];
    in.getline(a, sizeof(a));
    in.getline(b, sizeof(b));
    if (strlen(b) > strlen(a)) {
        swap(a, b);
    }
    int symb[256];
    for (int &i: symb) {
        i = 0;
    }
    for (int i = 0; i < strlen(a); ++i) {
        symb[(int) a[i]]++;
    }
    bool f = true;
    for (int i = 0; i < strlen(b) && f; i++) {
        if (symb[(int) b[i]] == 0) {
            f = false;
        } else {
            symb[(int) b[i]]--;
        }
    }
    if (f) {
        cout << "ДА";
    } else {
        cout << "НЕТ";
    }
}

void task13() {
    ifstream in("files/in13.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    char c[500];
    while (line[pos] != '\0') {
        if (!subchar(c, line[pos])) {
            cout << line[pos];
            c[count] = line[pos];
            count++;
        }
        pos++;
    }
}