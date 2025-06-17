//
// Created by Keller3D on 29.04.2025.
//

#ifndef PROGA2_ABITURIENTS_H
#define PROGA2_ABITURIENTS_H
using namespace std;
#endif //PROGA2_ABITURIENTS_H
#pragma once
const int MAX_NAME_LEN = 50; // Максимальная длина ФИО
const int DATE_LEN = 11; // Длина даты рождения в формате dd.mm.yyyy + '\0'
struct Applicant {
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char patronymic[MAX_NAME_LEN];
    char birthdate[DATE_LEN];
    int score1;
    int score2;
    int score3;
    int totalScore;
};

// Функция для чтения данных одного абитуриента из строки
void readApplicant(char *line, Applicant &applicant) {
    int pos = 0; // Текущая позиция в строке


    int i = 0;
    while (line[pos] != ' ') {
        applicant.surname[i++] = line[pos++];
    }
    applicant.surname[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.name[i++] = line[pos++];
    }
    applicant.name[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.patronymic[i++] = line[pos++];
    }
    applicant.patronymic[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.birthdate[i++] = line[pos++];
    }
    applicant.birthdate[i] = '\0';
    pos++;


    applicant.score1 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score1 = applicant.score1 * 10 + (line[pos++] - '0');
    }
    pos++;

    applicant.score2 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score2 = applicant.score2 * 10 + (line[pos++] - '0');
    }
    pos++;

    applicant.score3 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score3 = applicant.score3 * 10 + (line[pos++] - '0');
    }


    applicant.totalScore = applicant.score1 + applicant.score2 + applicant.score3;
}

// Функция для записи данных одного абитуриента в файл
void writeApplicant(ofstream &out, const Applicant &applicant) {
    out << applicant.surname << " " << applicant.name << " " << applicant.patronymic << " "
        << applicant.birthdate << " " << applicant.totalScore << endl;
}


// Функция сортировки массива абитуриентов
void sortApplicants(Applicant applicants[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (applicants[j].totalScore <= applicants[j + 1].totalScore) {
                swap(applicants[j], applicants[j + 1]);
            }
        }
    }
}
void taskA() {
    ifstream in("files/inA.txt");
    ofstream out("files/outA.txt");
    ofstream extraout("files/extraoutA.txt");

    if (!in || !out || !extraout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    int n; // Количество мест
    cin >> n;

    Applicant applicants[1000];
    int count = 0;

    char line[500];
    while (in.getline(line, sizeof(line)) && count < 1000) {
        readApplicant(line, applicants[count]);
        count++;
    }

    sortApplicants(applicants, count);

    int lastAcceptedIndex = 0;
    for (int i = 0; i < n && i < count; ++i) {
        writeApplicant(out, applicants[i]);
        lastAcceptedIndex = i;
    }

    if (lastAcceptedIndex < count - 1 &&
        applicants[lastAcceptedIndex].totalScore == applicants[lastAcceptedIndex + 1].totalScore) {
        for (int i = lastAcceptedIndex + 1; i < count; ++i) {
            if (applicants[i].totalScore == applicants[lastAcceptedIndex].totalScore) {
                writeApplicant(extraout, applicants[i]);
            } else {
                break;
            }
        }
    }

    in.close();
    out.close();
    extraout.close();
}