
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

int main()
{
    // Build tree T
    Node* root = new Node(40);
    root->left = new Node(20);
    root->right = new Node(60);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(50);
    root->right->right = new Node(70);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    
    Node* parent = nullptr;
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    if (cur == nullptr)
    {
        Node* fresh = new Node(key);
        if (parent == nullptr)
        {
            root = fresh;
            cout << key << " was not found, inserted as the new root" << endl;
        }
        else if (key < parent->data)
        {
            parent->left = fresh;
            cout << key << " was not found, inserted as the left child of "
                 << parent->data << endl;
        }
        else
        {
            parent->right = fresh;
            cout << key << " was not found, inserted as the right child of "
                 << parent->data << endl;
        }
    }

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}