#include <iostream>
#include <cstdlib>

#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
    : m_treeSize(0)
{
    root = nullptr;
}

BinarySearchTree::BinarySearchTree(size_t treeSize)
    : m_treeSize(treeSize)
{
    root = nullptr;
}
BinarySearchTree::~BinarySearchTree()
{
    root = make_empty(root);
}

void BinarySearchTree::delete_tree()
{
    root = make_empty(root);
    delete root;
}
void BinarySearchTree::insert(size_t x)
{
    root = insert(root, x);
}
void BinarySearchTree::remove(size_t x)
{
    root = remove(root, x);

}
void BinarySearchTree::display()
{
    in_order(root);
    std::cout << std::endl;
}
bool BinarySearchTree::search(size_t x)
{
    m_foundValue = find(root, x);

    return m_foundValue;
}

//går igenom hela träder
//tar bort nod för nod
BinarySearchTree::Node* BinarySearchTree::make_empty(Node* n)
{
    if(n == nullptr)
    {
        return n;
    }
    make_empty(n->left);
    make_empty(n->right);

    delete n;
    return nullptr;
}
BinarySearchTree::Node* BinarySearchTree::new_node(size_t x)
{
    Node* temp = new Node;
    temp->data = x;
    temp->left = temp->right = nullptr;

    return temp;
}

BinarySearchTree::Node* BinarySearchTree::insert(Node* n, size_t x)
{   //if the tree is empty, return a new node
    if(n == nullptr)
    {
        return new_node(x);
    }
    //otherwise recur down the tree
    if(x < n->data)
    {
        n->left = insert(n->left, x);
    }
    else if(x > n->data)
    {
        n->right = insert(n->right, x);
    }

    return n;
}
BinarySearchTree::Node* BinarySearchTree::find_min(Node* n)
{
    if(n == nullptr)
    {
        return nullptr;
    }
    if(n->left == nullptr)
    {
        return n;
    }
    else
    {
        find_min(n->left);
    }
}
BinarySearchTree::Node* BinarySearchTree::find_max(Node* n)
{
    if(n == nullptr)
    {
        return nullptr;
    }
    if(n->right == nullptr)
    {
        return n;
    }
    else
    {
        find_max(n->right);
    }
}
BinarySearchTree::Node* BinarySearchTree::remove(Node* n, size_t x)
{
    Node* temp = new Node;
    if(n == nullptr)
    {
        return n;
    }
    if(x < n->data)
    {
        n->left = remove(n->left, x);
    }
    else if(x > n->data)
    {
        n->right = remove(n->right, x);
    }
    else if(n->left && n->right)
    {
        temp = find_min(n->right);
        n->data = temp->data;
        n->right = remove(n->right, n->data);
    }
    else
    {
        temp = n;
        if(n->left == nullptr)
        {
            n = n->right;
        }
        else if(n->right == nullptr)
        {
            n = n->left;
        }
        delete temp;
    }
    return n;
}

void BinarySearchTree::in_order(Node* n)
{
    if(n == nullptr)
    {
        return;
    }
    in_order(n->left);
    std::cout << n->data << " ";
    in_order(n->right);
}
bool BinarySearchTree::find(Node* n, size_t x)
{
    //traverse until the root reaches dead end
    while(root !=nullptr)
    {
        //pass right subtree as new tree
        if(x > n->data)
        {
            root = root->right;
        }
        //pass left subtree as new tree
        else if(x < n->data)
        {
            root = root->left;
        }
        else
        {   //value has been found
            return true;
        }

    }
    return false;
}


