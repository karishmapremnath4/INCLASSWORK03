#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
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

Node* deleteNode(Node* root, int key)
{
    if (root == nullptr) return nullptr;

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
        return root;
    }
    if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
        return root;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        return nullptr;
    }
    if (root->left == nullptr)
    {
        Node* child = root->right;
        delete root;
        return child;
    }
    if (root->right == nullptr)
    {
        Node* child = root->left;
        delete root;
        return child;
    }

    Node* succ = root->right;
    while (succ->left != nullptr) succ = succ->left;
    root->data = succ->data;
    root->right = deleteNode(root->right, succ->data);
    return root;
}

int main()
{
    Node* root = new Node(40);
    root->left = new Node(20);
    root->right = new Node(60);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(50);
    root->right->right = new Node(70);

    cout << "Before:      ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    int keys[] = {40, 10, 60, 25};
    for (int k : keys)
    {
        root = deleteNode(root, k);
        cout << "delete " << k << ":   ";
        printInorder(root);
        cout << "  (root = " << (root ? root->data : 0) << ")" << endl;
    }

    freeTree(root);
    return 0;
}