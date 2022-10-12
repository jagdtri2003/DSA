#include <iostream>
using namespace std;
class SparseMatrix {
    struct Node {
        int rowN, colN, value;
        Node *next;

        Node(int row, int col, int value, Node *next) {
            this->rowN = row;
            this->colN = col;
            this->value = value;
            this->next = next;
        }
    };

    Node *head;
    Node *last;
public:
    SparseMatrix(int row, int col, int value, Node *next) {
        head = new Node(row, col, value, next);
        last = head;
    }

    void appendNode(int row, int col, int value) {
        if (row >= head->rowN || col >= head->colN)
            return;
        last->next = new Node(row, col, value, nullptr);
        last = last->next;
    }

    void printMatrix(Node *head = nullptr) {
        if (head == nullptr) {
            head = this->head;
        }
        Node *cur = head->next;
        for (int i = 0; i < head->rowN; i++) {
            for (int j = 0; j < head->colN; j++) {
                if (cur != nullptr && i == cur->rowN && j == cur->colN) {
                    cout << cur->value << '\t';
                    cur = cur->next;
                } else
                    cout << "0\t";
            }
            cout << endl;
        }
    }

    static Node *addSparseMatrices(const SparseMatrix &firstM, const SparseMatrix &secondM) {
        Node *first = firstM.head;
        Node *second = secondM.head;
        if (first->rowN != second->rowN || first->colN != second->colN) {
            return nullptr;
        }
        int count = 0;
        Node *res = new Node(first->rowN, first->colN, 0, nullptr);
        Node *resHead = res;
        first = first->next;
        second = second->next;
        while (first != nullptr && second != nullptr) {
            if (first->rowN == second->rowN && first->colN == second->colN) {
                res->next = new Node(first->rowN, first->colN, (first->value + second->value), nullptr);
                res = res->next;
                //Move both the pointers
                first = first->next;
                second = second->next;
                count++;
            }
                //If first matrix entry comes first
            else if ((first->rowN < second->rowN) || ((first->rowN == second->rowN) && (first->colN < second->colN))) {
                res->next = new Node(first->rowN, first->colN, first->value, nullptr);
                res = res->next;
                //move the first pointer ahead
                first = first->next;
                count++;
            }
                //If second matrix entry comes first
            else if ((first->rowN > second->rowN) || ((first->rowN == second->rowN) && (first->colN > second->colN))) {
                res->next = new Node(second->rowN, second->colN, second->value, nullptr);
                res = res->next;
                //move the first pointer ahead
                second = second->next;
                count++;
            }
        }
        if (first == nullptr) {
            while (second != nullptr) {
                res->next = new Node(second->rowN, second->colN, second->value, nullptr);
                res = res->next;
                second = second->next;
                count++;
            }
        } else {
            while (first != nullptr) {
                res->next = new Node(first->rowN, first->colN, first->value, nullptr);
                res = res->next;
                first = first->next;
                count++;
            }
        }
        resHead->value = count;
        return resHead;
    }
};

int main() {
    SparseMatrix SP(5, 6, 5, nullptr);
    SP.appendNode(0, 0, 10);
    SP.appendNode(1, 0, 5);
    SP.appendNode(1, 3, 17);
    SP.appendNode(1, 5, 3);
    SP.appendNode(3, 4, 19);
    SP.printMatrix();
    cout << endl;
    SparseMatrix SP2(5, 6, 4, nullptr);
    SP2.appendNode(1, 3, 3);
    SP2.appendNode(2, 5, 3);
    SP2.appendNode(4, 4, 2);
    SP2.appendNode(4, 5, 1);
    SP2.printMatrix(SparseMatrix::addSparseMatrices(SP, SP2));
}
