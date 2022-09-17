#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


class BinarySearchTree
{

private:
    struct Node
    {
        size_t data;
        Node* left;
        Node* right;
    };

    Node* root;

    Node* make_empty(Node*);
    Node* new_node(size_t);

    Node* insert(Node*, size_t);
    Node* find_min(Node*);
    Node* find_max(Node*);
    Node* remove(Node*, size_t);

    void in_order(Node*);
    bool find(Node*, size_t);


public:
    BinarySearchTree();
    BinarySearchTree(size_t);
    ~BinarySearchTree();

    void delete_tree();
    void insert(size_t);
    void remove(size_t);
    void display();
    bool search(size_t);

private:
    bool m_foundValue{false};
    size_t m_treeSize;
};


#endif // BINARYSEARCHTREE_H
