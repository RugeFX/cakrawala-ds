#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
private:
    Node *root;

    Node *insertHelper(Node *node, int value)
    {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertHelper(node->left, value);
        else if (value > node->data)
            node->right = insertHelper(node->right, value);

        return node;
    }

    Node *deleteHelper(Node *node, int value)
    {
        if (node == nullptr)
            return nullptr;

        if (value < node->data)
            node->left = deleteHelper(node->left, value);
        else if (value > node->data)
            node->right = deleteHelper(node->right, value);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node *temp = node->right;
                while (temp->left != nullptr)
                    temp = temp->left;

                node->data = temp->data;
                node->right = deleteHelper(node->right, temp->data);
            }
        }

        return node;
    }

    bool searchHelper(Node *node, int value)
    {
        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return searchHelper(node->left, value);

        return searchHelper(node->right, value);
    }

    void inorderTraversalHelper(Node *node)
    {
        if (node == nullptr)
            return;

        inorderTraversalHelper(node->left);
        cout << node->data << " ";
        inorderTraversalHelper(node->right);
    }

    int getHeightHelper(Node *node)
    {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeightHelper(node->left);
        int rightHeight = getHeightHelper(node->right);

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    int countLeavesHelper(Node *node)
    {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr && node->right == nullptr)
            return 1;

        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insertNode(int value)
    {
        root = insertHelper(root, value);
    }

    Node *deleteNode(int value)
    {
        return deleteHelper(root, value);
    }

    bool search(int value)
    {
        return searchHelper(root, value);
    }

    void inorderTraversal()
    {
        inorderTraversalHelper(root);
    }

    Node *findMin()
    {
        Node *current = root;
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node *findMax()
    {
        Node *current = root;
        while (current->right != nullptr)
            current = current->right;

        return current;
    }

    int getHeight()
    {
        return getHeightHelper(root);
    }

    int countLeaves()
    {
        return countLeavesHelper(root);
    }
};

int main()
{
    int values[] = {50, 30, 70, 80};
    BinarySearchTree *tree = new BinarySearchTree();

    for (int value : values)
        tree->insertNode(value);

    tree->inorderTraversal();

    cout << endl;

    cout << "Searching for 40: " << (tree->search(40) ? "Found" : "Not found") << endl;

    tree->deleteNode(40);

    cout << "Searching for 40: " << (tree->search(40) ? "Found" : "Not found") << endl;
    cout << "Searching for 90: " << (tree->search(90) ? "Found" : "Not found") << endl;
    cout << "Searching for 80: " << (tree->search(80) ? "Found" : "Not found") << endl;

    cout << "Minimum value: " << tree->findMin()->data << endl;
    cout << "Maximum value: " << tree->findMax()->data << endl;

    tree->inorderTraversal();

    cout << endl;

    cout << "Height of the tree: " << tree->getHeight() << endl;

    cout << "Number of leaves: " << tree->countLeaves() << endl;

    delete tree;

    return 0;
}
