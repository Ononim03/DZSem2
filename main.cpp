//
// Created by tzina on 17.06.2025.
//
#include <iostream>
#include <fstream>
#include "hfiles/abiturients.h"
#include "hfiles/stringtasks.h"
#include "hfiles/binary.h"
#include <cstring>
using namespace std;

struct TreeNode {
    char data;
    TreeNode *left;
    TreeNode *right;
};

bool is_num(char c) {
    return c >= '0' && c <= '9';
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

TreeNode *createTree() {
    return nullptr;
}

TreeNode *createNode(char c) {
    TreeNode *node = new TreeNode;
    node->left = nullptr;
    node->right = nullptr;
    node->data = c;
    return node;
}

void delete_tree(TreeNode *&root) {
    if (root->left != nullptr) {
        delete_tree(root->left);
    }
    if (root->right != nullptr) {
        delete_tree(root->right);
    }
    delete root;
};

TreeNode *build_prefix_helper(istream &in) {
    char c;
    in >> c;
    TreeNode *node = createNode(c);
    if (is_num(c)) {
        return node;
    } else if (is_operator(c)) {
        node->left = build_prefix_helper(in);
        node->right = build_prefix_helper(in);
        return node;
    }
    return nullptr;
}

void build_prefix(istream &in, TreeNode *&root) {
    root = build_prefix_helper(in);
};

TreeNode *build_infix_helper(istream &in) {
    char c;
    in >> c;
    if (c == '(') {
        TreeNode *left = build_infix_helper(in);
        char op;
        in >> op;
        TreeNode *node = createNode(op);
        node->left = left;
        node->right = build_infix_helper(in);
        in >> c;
        return node;
    } else if (is_num(c)) {
        TreeNode *node = createNode(c);
        return node;
    }
    return nullptr;
};

void build_infix(istream &in, TreeNode *&root) {
    root = build_infix_helper(in);
};

void expression(ostream &out, TreeNode *root) {
    if (!root) return;

    if (isdigit(root->data)) {
        out << root->data;
    } else {
        out << "(";
        expression(out, root->left);
        out << " " << root->data << " ";
        expression(out, root->right);
        out << ")";
    }
};

int evaluate(TreeNode *root) {
    if (!root) return 0;

    if (isdigit(root->data)) {
        return root->data - '0';
    }

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    switch (root->data) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/':
            if (right == 0) {
                cout << "Деление на ноль!";
                return -1;
            }
            return left / right;
        default:
            return -1;
    }
};

void commute(TreeNode *&root) {
    if (!root) return;

    if (root->data == '+' || root->data == '*' || root->data == '-') {
        swap(root->left, root->right);
    }

    commute(root->left);
    commute(root->right);
};

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_letter(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void automat() {
    ifstream in("files/automat.txt");
    char c;
    int m = 4;
    int p = 5;
    char current_id[m + 1];
    int op_count = 0;
    int len_number = 0;
    int len_id = 0;

    int state = 0;
    bool f = true;

    while (in.get(c) && f) {
        // Пропускаем пробелы и табуляции

        switch (state) {
            case 0:
                if (is_letter(c)) {
                    len_id = 1;
                    state = 1;
                    current_id[0] = c;
                    current_id[1] = '\0';
                } else {
                    cout << state;
                    state = -1;
                }
                break;

            case 1:
                if ((is_letter(c) || is_digit(c)) && len_id < m) {
                    current_id[len_id++] = c;
                    current_id[len_id] = '\0';
                } else if (c == ':') {
                    state = 2;
                } else {
                    cout << state;
                    state = -1;
                }
                break;

            case 2:
                if (c == '=') {
                    state = 3;
                    break;
                } else {
                    cout << state;
                    state = -1;
                }
            case 3:
                if (c == '+' || c == '-') {
                    len_number = 0;
                    state = 4;
                } else if (is_letter(c)) {
                    state = 5;
                    len_id = 1;
                } else {
                    cout << c;
                    state = -1;
                }
            break;
            case 4:
                if (is_digit(c)) {
                    if (len_number < 5) {
                        len_number++;
                    } else {
                        cout << state;
                        state = -1;
                    }
                } else if (len_number != 5) {
                    cout << state;
                    state = -1;
                } else if (is_op(c)) {
                    if (op_count < p) {
                        op_count++;
                        state = 6;
                    } else {
                        cout << state;
                        state = -1;
                    }
                } else if (c == ';') {
                    current_id[0] = '\0';
                    op_count = 0;
                    state = 7;
                } else if (c == '.') {
                    state = 8;
                } else {
                    cout << state;
                    state = -1;
                }
                break;

            case 5:
                if ((is_digit(c) || is_letter(c)) && len_id < m) {
                    len_id++;
                } else if (is_op(c)) {
                    if (op_count < p) {
                        op_count++;
                        state = 6;
                    } else {
                        cout << state;
                        state = -1;
                    }
                } else if (c == ';') {
                    current_id[0] = '\0';
                    op_count = 0;
                    state = 7;
                } else if (c == '.') {
                    state = 0;
                } else {
                    cout << state;
                    state = -1;
                }
                break;
            case 6:
                if (is_letter(c)) {
                    state = 5;
                    len_id = 1;
                } else if (c == '+' || c == '-') {
                    state = 4;
                    len_number = 0;
                } else {
                    cout << state;
                    state = -1;
                }
                break;
            case 7:
                if (is_letter(c)) {
                    state = 1;
                    len_id = 1;
                    current_id[0] = c;
                    current_id[1] = '\0';
                } else {
                    state = -1;
                }
                break;

        }
    }
    if (state == -1) {
        cout << "NO (Syntax error)" << endl;
    } else if (state == 0 || state == 6) {
        cout << "YES (Valid program)" << endl;
    } else {
        cout << "NO (Unexpected end)" << endl;
    }
}

int main() {
    system("chcp 65001");
    TreeNode *root = createTree();
    ifstream in("files/s.txt");
    // build_prefix(in, root);
    build_infix(in, root);
    expression(cout, root);
    cout << endl;
    cout << evaluate(root);
    commute(root);
    cout << endl;
    expression(cout, root);
    return 0;
}
