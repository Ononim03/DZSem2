//
// Created by tzina on 17.06.2025.
//

#ifndef TREES_H
#define TREES_H

#endif //TREES_H
// 1. найти минимум и максимум в двоичном дереве поиска
//    не обходить все дерево!!

// 2. заменить все отрицательные элементы на их абсолютные
//    значения в ДДП (без перестройки)


// далее обычные деревья
// 3. найти минимум и максимум в дереве

// 4. найти число вхождений элемента x в дереве
typedef int tdata;


struct TreeNode {
    tdata data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *createNode(tdata x) {
    TreeNode *q = new TreeNode;
    q->data = x;
    q->left = nullptr;
    q->right = nullptr;
    return q;
}

void insert(TreeNode *&root, tdata x) {
    if (root == nullptr) {
        root = createNode(x);
        return;
    } else {
        TreeNode *q = root;
        while (q) {
            if (x < q->data) {
                if (q->left) {
                    q = q->left;
                } else {
                    q->left = createNode(x);
                    return;
                }
            } else if (x > q->data) {
                if (q->right) {
                    q = q->right;
                } else {
                    q->right = createNode(x);
                    return;
                }
            } else {
                cout << "Невозможно добавить, так как элемент уже в дереве";
                return;
            }
        }
    }
}

TreeNode *createTree(ifstream &in) {
    tdata x;
    TreeNode *root = nullptr;
    while (in >> x) {
        insert(root, x);
    }
    return root;
}

bool search(TreeNode *root, tdata x) {
    if (root == nullptr) return false;
    TreeNode *q = root;
    while (q) {
        if (x == q->data) {
            return true;
        } else if (x < q->data) {
            if (q->left) {
                q = q->left;
            } else {
                return false;
            }
        } else {
            if (q->right) {
                q = q->right;
            } else {
                return false;
            }
        }
    }
    return false;
}
struct Stack {
    TreeNode *data;
    Stack *next;

};

Stack *createStack() {
    return nullptr;
}

bool empty(Stack *stack) {
    return stack == nullptr;
}

void push(Stack *&stack, TreeNode *x) {
    Stack *p = new Stack;
    p->data = x;
    p->next = stack;
    stack = p;
}

TreeNode *pop(Stack *&stack) {
    TreeNode *x = stack->data;
    Stack *p = stack;
    stack = stack->next;
    delete p;
    return x;
}

void klp(TreeNode *&root) {
    if (root == nullptr) return;
    TreeNode *p;
    Stack *stack = createStack();
    push(stack, root);
    while (!empty(stack)) {
        p = pop(stack);
        cout << p->data << " ";
        if (p->right) {
            push(stack, p->right);
        }
        if (p->left) {
            push(stack, p->left);
        }
    }
}

void lkp(TreeNode *root) {
    if (root == nullptr) return;
    TreeNode *p = root;
    Stack *stack = createStack();
    while (!empty(stack) || p) {
        while (p) {
            push(stack, p);
            p = p->left;

        }
        TreeNode *q = pop(stack);
        cout << q->data << " ";
        p = q->right;

    }
}

void lpk(TreeNode *root) {
    if (root == nullptr) return;
    TreeNode *p;
    Stack *stack = createStack();
    Stack *skebob = createStack();
    push(stack, root);
    while (!empty(stack)) {
        p = pop(stack);
        push(skebob, p);
        if (p->left) push(stack, p->left);
        if (p->right) push(stack, p->right);

    }
    while (!empty(skebob)) {
        p = pop(skebob);
        cout << p->data << " ";

    }
}

struct queue_node {
    TreeNode *data;
    queue_node *next;
};
struct queue {
    queue_node *head;
    queue_node *tail;
};

queue qcreate() {
    queue q;
    q.head = nullptr;
    q.tail = nullptr;
    return q;
}

bool qempty(queue q) {
    return q.head == nullptr;
}


void bfs(TreeNode *root) {

}

void treetest() {
    ifstream in("tree.txt");
    TreeNode *root = createTree(in);
    lpk(root);
}

TreeNode *find(TreeNode *root, TreeNode *&pred, tdata x) {
    bool f = false;
    TreeNode *p = root;
    pred = root;
    while (p && !f) {
        if (p->data == x) f = true;
        else if (p->data < x) {
            pred = p;
            p = p->right;
        } else if (p->data > x) {
            pred = p;
            p = p->left;
        }
    }
    if (f) return p;
    else return nullptr;
}

TreeNode *maxi(TreeNode *root, TreeNode *&pred) {
    TreeNode *p = root;
    while (p->right) {
        pred = p;
        p = p->right;
    }
    return p;
}

TreeNode *mini(TreeNode *root, TreeNode *&pred) {
    TreeNode *p = root;
    while (p->left) {
        pred = p;
        p = p->left;
    }
    return p;
}

void deletenode(TreeNode *&p, TreeNode *pred) {
    if (!p->left && !p->right) {
        if (p == pred->left) {
            pred->left = nullptr;
            delete p;
        } else {
            pred->right = nullptr;
            delete p;
        }
    } else if ((p->left && !p->right) || (!p->left && p->right)) {
        if (p->left) {
            if (p == pred->left) {
                TreeNode *p1 = p;
                pred->left = p->left;
                delete p1;
            } else {
                TreeNode *p1 = p;
                pred->right = p->left;
                delete p1;
            }
        }else{
            if (p == pred->left) {
                TreeNode *p1 = p;
                pred->left = p->right;
                delete p1;
            } else {
                TreeNode *p1 = p;
                pred->right = p->right;
                delete p1;
            }
        }
    }else{
        TreeNode* maxx = maxi(p->left, pred);
        p->data = maxx->data;
        pred->right = nullptr;
        delete maxx;

    }
}

void deletex(TreeNode *&root, tdata x) {
    TreeNode *pred;
    TreeNode *p = find(root, pred, x);
    if (p) deletenode(p, pred);
    else cout << "Ошибка";
}
void insert_rec(TreeNode *&root, tdata x){
    if (root== nullptr){
        root = createNode(x);
        return;
    }if (root->data == x){
        return;
    }
    if (root->data < x) insert_rec(root->right, x);
    if (root->data > x) insert_rec(root->left, x);
}
bool search_x_rec(TreeNode *&root, tdata x){
    if (root == nullptr) return false;
    if (root->data == x) return true;
    if(root->data > x) return search_x_rec(root->right, x);
    if(root->data < x) return search_x_rec(root->left, x);
}
