#include <iostream>
#include <ctime>
#include <windows.h>
#include <stack>
#include <string>
#include <stdlib.h> // ����� ��� ������ ������� rand(), srand()
#include <time.h> // ����� ��� ������ ������� time()
int count_of_nodes = 8;
using namespace std;


struct Node
{
    float key;                   //�������������� �����
    Node* leftTree = nullptr;     //������ �������
    Node* rightTree = nullptr;    //������ �������
    Node* root = nullptr;         //������ ������
    string path;				//���� �� ����
    ~Node() {
        key = NULL;
        path.clear();
        delete leftTree, rightTree;
    }
};

class Tree {
    Node* root;

public:
    //����� �������� ������
    void CreateTree(Node* treeRoot, int node_count, string path) {
        int nl = 0, nr = 0;
        if (node_count != 0) {
            treeRoot->key = (1 + rand() % 100) / 2.4;
            treeRoot->path = path;
            nl = node_count / 2;
            nr = node_count - nl - 1;
            if (nl != 0) {
                treeRoot->leftTree = new Node;
                treeRoot->leftTree->path += treeRoot->path + "-->left";
                CreateTree(treeRoot->leftTree, nl, treeRoot->leftTree->path);
            }
            if (nr != 0) {
                treeRoot->rightTree = new Node;
                treeRoot->rightTree->path += treeRoot->path + "-->right";
                CreateTree(treeRoot->rightTree, nr, treeRoot->rightTree->path);
            }
        }
    }

    //����� ������
    void printTree(Node* treeRoot, int node_count) {
        if (node_count == count_of_nodes) cout << treeRoot->path << ": " << treeRoot->key << "\n";
        int nl = 0, nr = 0;
        if (node_count != 0) {
            nl = node_count / 2;
            nr = node_count - nl - 1;
            if (nl != 0) {
                cout << treeRoot->leftTree->path << ": " << treeRoot->leftTree->key
                     << "\n";
                printTree(treeRoot->leftTree, nl);
            }
            if (nr != 0) {
                cout << treeRoot->rightTree->path << ": " << treeRoot->rightTree->key << "\n";
                printTree(treeRoot->rightTree, nr);
            }
        }
    }

    //����� ��� ����������� ��������� ������
    void mirroringOperation(Node* T, int n) {
        int nl = 0, nr = 0;
        if (n != 0) {
            Node* temp_node = new Node;
            temp_node = T->rightTree;
            T->rightTree = T->leftTree;
            T->leftTree = temp_node;
            nl = n / 2;
            nr = n - nl - 1;
            //�������������� ��������� ������ ����
            mirroringOperation(T->leftTree, nl);
            //�������������� ��������� ������� ����
            mirroringOperation(T->rightTree, nr);
        }
    }

    //����� ���-�� �����
    int arithmetic_nodes(Node* node) {
        if (node->leftTree == NULL && node->rightTree == NULL)
            return 1;
        int left, right;
        if (node->leftTree != NULL)
            left = arithmetic_nodes(node->leftTree);
        else
            left = 0;
        if (node->rightTree != NULL)
            right = arithmetic_nodes(node->rightTree);
        else
            right = 0;
        return left + right + 1;
    }
    //����� ����� �������������� �����
    int arithmetic_summ(Node* node) {
        int summa = node->key;
        if (node->leftTree != NULL) {
            summa += arithmetic_summ(node->leftTree);
        }
        if (node->rightTree != NULL) {
            summa += arithmetic_summ(node->rightTree);
        }
        return summa;
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    int i = 0;
    Node* treeRoot = new Node;
    treeRoot->path = "root";
    Tree* tree = new Tree();
    int left_count,right_count = 0;
    int left_sum, right_sum = 0;
    while (i != -1) {
        cout << "�������� �����:" << endl
             << "1 -- �������� ������" << endl
             << "2 -- ����� ������" << endl
             << "3 -- ��������� ������" << endl
             << "4 -- �������� ����������� �������� ��������������� ������" << endl
             << "5 -- ���������� ������ ������ ������� ������ " << endl
             << "-1 -- ��������� ���������"  << endl
             <<"�����: ";
        cin >> i;
        switch (i)
        {
            case 1:
                tree->CreateTree(treeRoot, count_of_nodes, "root");
                cout << "������ ������� �������.\n\n";
                break;

            case 2:
                cout << "����� ������...\n";
                tree->printTree(treeRoot, count_of_nodes);
                cout << "\n";
                break;

            case 3:
                cout << "��������� ������ ������ ������.."<<endl;
                tree->mirroringOperation(treeRoot, count_of_nodes);
                tree->printTree(treeRoot, count_of_nodes);
                cout << "������ ������� ��������.\n\n";
                break;
            case 4:
                cout << "�������� ����������� �������� ��������������� ����� ����������� \n";
                left_count = tree->arithmetic_nodes(treeRoot->leftTree);
                right_count =  tree->arithmetic_nodes(treeRoot->rightTree);
                left_sum = tree->arithmetic_summ(treeRoot->leftTree);
                right_sum = tree->arithmetic_summ(treeRoot->rightTree);
                cout << "������� �������������� ����� ������ ���������: " << left_sum/left_count <<endl;
                cout << "������� �������������� ����� ������� ���������: " << right_sum/right_count <<endl;
                break;

            case 5:
                cout << " ���������� �������� ������... " << endl;
                cout << " ������ ������� �������." << endl;
                break;
            case -1:
                return 0;
                break;
            default:
                cout << "���������� ��� ���." << endl;
                break;
        }
    }
}
