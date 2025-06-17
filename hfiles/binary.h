//
// Created by tzina on 17.06.2025.
//

#ifndef BINARY_H
#define BINARY_H

#endif //BINARY_H
double operat(int n, double *arr, char oper[3]) {
    double arr_min = 10000000000.0;
    double arr_max = -100000000000.0;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        if (arr[i] > arr_max) {
            arr_max = arr[i];
        }
        if (arr[i] < arr_min) {
            arr_min = arr[i];
        }
    }
    if (oper[2] == 'N') {
        return arr_min;
    } else if (oper[2] == 'X') {
        return arr_max;
    } else {
        return sum;
    }
}

int txt_to_bin() {
    int count = 0;
    ifstream txtin("files/task1.txt");
    ofstream binout("files/task1.bin", ios::binary);
    int n;
    while (txtin >> n) {
        auto *arr = new double[n];
        for (int i = 0; i < n; ++i) {
            txtin >> arr[i];
        }
        auto *op = new char[3];
        txtin >> op;
        count++;
        binout.write((char *) &n, sizeof(n));
        binout.write((char *) arr, sizeof(double) * n);
        binout.write((char *) op, sizeof(char) * 3);
        delete[] arr;
        delete[] op;
    }
    txtin.close();
    binout.close();
    return count;
}

void solution(int count) {
    ifstream binin("files/task1.bin", ios::binary);
    ofstream txtout("files/task1final.txt");
    int n;
    for (int i = 0; i < count; ++i) {
        binin.read((char *) &n, sizeof(int));
        auto *arr = new double[n];
        auto *op = new char[3];
        binin.read((char *) arr, sizeof(double) * n);
        binin.read((char *) op, sizeof(char) * 3);
        cout << operat(n, arr, op) << endl;
        txtout << n << " ";
        for (int j = 0; j < n; j++) {
            txtout << arr[j] << " ";
        }
        for (int j = 0; j < 3; j++) {
            txtout << op[j];
        }
        txtout << endl;
        delete[] arr;
        delete[] op;
    }
    txtout.close();
    binin.close();
};

void task_first() {
    int a = txt_to_bin();
    solution(a);
}