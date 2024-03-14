#include <iostream>
using namespace std;

struct bst_node
{
    int data;
    bst_node *left;
    bst_node *right;
};
class BinarySearchTree
{

private:
    bst_node *root;
    bool first_node = true;

    /**
     * create a new binary search tree node.
     *
     * @param x the data of the node.
     * @return A pointer to the created binary search tree node.
     */
    bst_node *new_node(int x)
    {
        bst_node *node = new bst_node();
        node->data = x;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    /**
     * create a root node of binary search tree
     *
     * @param x the data of root node
     * @return a pointer to root node
     */
    bst_node *create_root_node(int x)
    {
        first_node = false;
        root = new_node(x);
        return root;
    }

    /**
     * insert a new node to the provided root node of binary search tree
     *
     * @param node provided root node of binary search tree
     * @param x node data
     */
    bst_node *insert_new_node(bst_node *node, int x)
    {
        if (first_node)
            return create_root_node(x);
        if (node == nullptr)
            return new_node(x);
        if (x < node->data)
            node->left = insert_new_node(node->left, x);
        else
            node->right = insert_new_node(node->right, x);
        return node;
    }

    /**
     * search the binary search tree with the given number, root node
     *
     * @param node root node of the binary tree
     * @param x the number to search
     * @return binary tree node pointer or nullptr
     */
    bst_node *search_from_node(bst_node *node, int x)
    {
        if (node == nullptr)
            return nullptr;
        if (x == node->data)
            return node;
        if (x < node->data)
            return search_from_node(node->left, x);
        else
            return search_from_node(node->right, x);
    }

    /**
     * use postorder traversal to delete the all child nodes of provided root node.
     *
     * @param node provided root node of binary search tree.
     */
    void postorder_traversal_delete(bst_node *node)
    {
        if (node != nullptr)
        {
            postorder_traversal_delete(node->left);
            postorder_traversal_delete(node->right);
            delete node;
        }
    }

    /**
     * get the root node
     *
     * @return return the root node of the binary search tree.
     */
    bst_node *get_root_node()
    {
        return this->root;
    }

    /**
     * performs an inorder traversal of a binary search tree.
     *
     * @param node a pointer to the root node of the binary search tree.
     */
    void inorder_traversal(bst_node *node)
    {
        if (node != nullptr)
        {
            inorder_traversal(node->left);
            cout << node->data << "_";
            inorder_traversal(node->right);
        }
    }

    /**
     * performs an postorder traversal of a binary search tree.
     *
     * @param node a pointer to the root node of the binary search tree.
     */
    void postorder_traversal(bst_node *node)
    {
        if (node != nullptr)
        {
            postorder_traversal(node->left);
            postorder_traversal(node->right);
            cout << node->data << "_";
        }
    }

    /**
     * performs an preorder traversal of a binary search tree.
     *
     * @param node a pointer to the root node of the binary search tree.
     */
    void preorder_traversal(bst_node *node)
    {
        if (node != nullptr)
        {
            cout << node->data << "_";
            preorder_traversal(node->left);
            preorder_traversal(node->right);
        }
    }

public:
    /**
     * Binary search tree constructor.
     */
    BinarySearchTree()
    {
    }

    /**
     * Binary search tree deconstructor.
     */
    ~BinarySearchTree()
    {
        postorder_traversal_delete(root);
    }

    /**
     * search binary search tree by the given number
     *
     * @param x target number
     * @return founded or not
     */
    bool search(int x)
    {
        if (search_from_node(root, x) == nullptr)
            return false;

        return true;
    }

    /**
     * insert new node with provided number
     *
     * @param x the data of new node
     */
    void insert(int x)
    {
        root = insert_new_node(root, x);
    }

    /**
     * Empties the binary search tree by deleting all nodes.
     */
    void empty()
    {
        postorder_traversal_delete(root);
        first_node = false;
        root = nullptr;
    }

    /**
     *  Print the binary search tree via provided method
     *
     * @param type preorder -> 0, inorder -> 1, postorder -> 2
     */
    void print(int type)
    {
        switch (type)
        {
        case 0:
            cout << "preorder traversal..." << endl;
            preorder_traversal(root);
            break;
        case 1:
            cout << "inorder traversal..." << endl;
            inorder_traversal(root);
            break;
        case 2:
            cout << "postorder traversal..." << endl;
            postorder_traversal(root);
            break;
        default:
            break;
        }
        cout << endl;
    }
};

// signed main()
// {
//     BinarySearchTree tree = BinarySearchTree();
//     tree.insert(20);
//     tree.insert(30);
//     tree.insert(10);
//     tree.insert(40);
//     tree.search(40);
//     tree.search(50);
//     tree.print(1);
// }
