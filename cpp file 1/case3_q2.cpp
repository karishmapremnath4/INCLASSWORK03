
#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;
    Node(int value) { data = value; left = nullptr; right = nullptr; }
};

void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

Node* insert(Node* root, int value)
{
    if (root == nullptr) return new Node(value);
    if (value < root->data) root->left = insert(root->left, value);
    else                    root->right = insert(root->right, value);
    return root;
}

int main()
{
    
    int keys[] = {45, 25, 65, 15, 35, 55, 75, 30, 60};
    Node* root = nullptr;
    for (int k : keys) root = insert(root, k);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    
    Node* parent = nullptr;
    Node* cur = root;
    int key = 35;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;   
    cout << "parent = " << parent->data
         << ", child that moves up = " << child->data << endl;
    if (parent->left == cur) parent->left = child;
    else                     parent->right = child;                  
    delete cur;
    

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}