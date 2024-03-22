#include <iostream>
#include <stack>
using namespace std;

class BinarySearchTree
{

private:
    struct bst_node
    {
        int data;
        bst_node *left;
        bst_node *right;
    };
    struct bst_stack_node
    {
        bst_stack_node *prev;
        bst_node *data;
    };
    struct bst_queue_node
    {
        bst_queue_node *next;
        bst_node *data;
    };

    bst_node *root = nullptr;
    bst_stack_node *top = nullptr;
    bst_queue_node *front = nullptr;
    bst_queue_node *rear = nullptr;
    stack<int> data_stack;
    bool first_node = true;
    bool allow_duplicated_node = false;

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
        if (node == nullptr)
            return new_node(x);
        if (x < node->data)
            node->left = insert_new_node(node->left, x);
        else
            node->right = insert_new_node(node->right, x);
        return node;
    }

    /**
     * search the binary search tree with the given number, root node (recursion)
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
     * search the binary search tree with the given number, root node (iterative)
     *
     * @param node root node of the binary tree
     * @param x the number to search
     * @return binary tree node pointer or nullptr
     */
    bst_node *search_from_node_iter(bst_node *node, int x)
    {
        while (node != nullptr)
        {
            if (x == node->data)
                return node;
            if (x < node->data)
                node = node->left;
            else if (x > node->data)
                node = node->right;
        }
        return nullptr;
    }

    /**
     * Find the inorder immediate successor
     *
     * @param node root node
     */
    bst_node *inorder_immediate_successor(bst_node *node)
    {
        bst_node *p;
        for (p = node->right; p->left != nullptr; p = p->left)
            ;
        return p;
    }

    /**
     * delete specific node from binary search tree if node x exist (recursive)
     *
     * @param x search node x
     */
    bst_node *delete_from_node(bst_node *node, int x)
    {
        bst_node *temp;
        // target node contain data x not found
        if (node == nullptr)
            return node;
        if (x < node->data)
            node->left = delete_from_node(node->left, x);
        else if (x > node->data)
            node->right = delete_from_node(node->right, x);
        // node found
        else
        {
            // node has zero or one children
            if ((node->left == nullptr) || (node->right == nullptr))
            {
                temp = (node->left == nullptr) ? node->right : node->left;

                // if node is leaf
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                // node has children
                else
                {
                    // override node with children node temp
                    *node = *temp;
                }

                delete temp;
            }
            // node has two children
            else
            {
                // find inorder_immediate_successor
                temp = inorder_immediate_successor(node);
                node->data = temp->data;
                // delete the duplicated temp node by node data
                node->right = delete_from_node(node->right, temp->data);
            }
        }
        return node;
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

    void preorder_traversal_stack(bst_node *node)
    {
        do
        {
            while (node != nullptr)
            {
                cout << node->data << "_";
                push(node);
                node = node->left;
            }
            if (top != nullptr)
            {
                node = pop();
                node = node->right;
            }
        } while ((!stack_is_empty()) || node != nullptr);
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

    void inorder_traversal_stack(bst_node *node)
    {
        do
        {
            while (node != nullptr)
            {
                push(node);
                node = node->left;
            }
            if (!stack_is_empty())
            {
                node = pop();
                cout << node->data << "_";
                node = node->right;
            }
        } while ((!stack_is_empty()) || (node != nullptr));
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

    void postorder_traversal_stack(bst_node *node)
    {
        do
        {
            while (node != nullptr)
            {
                data_stack.push(node->data);
                push(node);
                node = node->right;
            }
            if (!stack_is_empty())
            {
                node = pop();
                node = node->left;
            }
        } while ((!stack_is_empty() || (node != nullptr)));
        while (!data_stack.empty())
        {
            cout << data_stack.top() << "_";
            data_stack.pop();
        }
    }

    void levelorder_traversal(bst_node *node)
    {
        if (node != nullptr)
        {
            add(node);
            while (!queue_is_empty())
            {
                node = retrieve();
                cout << node->data << "_";
                if (node->left != nullptr)
                    add(node->left);
                if (node->right != nullptr)
                    add(node->right);
            }
        }
    }

    bst_stack_node *push(bst_node *node)
    {
        if (top == nullptr)
        {
            top = new bst_stack_node();
            top->data = nullptr;
            top->prev = nullptr;
        }
        bst_stack_node *stack_node = new bst_stack_node();
        stack_node->data = node;
        stack_node->prev = top;
        top = stack_node;
        return top;
    }

    bst_node *pop()
    {
        if (!stack_is_empty())
        {
            bst_stack_node *node_st = top;
            bst_node *node = node_st->data;
            top = top->prev;
            delete node_st;
            return node;
        }
        return nullptr;
    }

    bool stack_is_empty()
    {
        return top->prev == nullptr;
    }

    void add(bst_node *node)
    {
        bst_queue_node *queue_node = new bst_queue_node();
        queue_node->data = node;
        queue_node->next = nullptr;
        if (front == nullptr)
            front = queue_node;
        else
            rear->next = queue_node;
        rear = queue_node;
    }

    bst_node *retrieve()
    {
        if (queue_is_empty())
            return nullptr;
        bst_queue_node *queue_node = front;
        bst_node *node = queue_node->data;
        if (front->next == nullptr)
            rear = nullptr;
        front = front->next;
        delete queue_node;
        return node;
    }

    bool queue_is_empty()
    {
        return (front == rear) && (front == nullptr);
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

    bool search_iter(int x)
    {
        if (search_from_node_iter(root, x) == nullptr)
            return false;

        return true;
    }

    /**
     * insert new node with provided number (recursive)
     *
     * @param x the data of new node
     */
    void insert(int x)
    {
        if (root == nullptr)
            create_root_node(x);
        else
        {
            root = insert_new_node(root, x);
        }
    }

    /**
     * insert new node with provided number (iterative)
     *
     * @param x the data of new node
     */
    int insert_iter(int x)
    {
        // parent
        bst_node *p = nullptr;
        // children
        bst_node *c = root;
        while (c != nullptr)
        {
            p = c;
            if (!allow_duplicated_node && x == c->data)
                return -1;
            if (x < c->data)
                c = c->left;
            else
                c = c->right;
        }
        c = new_node(x);
        if (root == nullptr)
            root = c;
        else if (x < p->data)
            p->left = c;
        else
            p->right = c;
        return 0;
    }

    /**
     * delete target node x (recursive)
     *
     * @param x number to delete
     */
    bool dewete(int x)
    {
        if (delete_from_node(root, x) == nullptr)
            return false;
        return true;
    }

    /**
     * delete target node x (iteration)
     *
     * @param x number to delete
     */
    int dewete_iter(int x)
    {
        // parent node of node p
        bst_node *F;
        // current node; node to delete
        bst_node *p;
        // parent node of node k
        bst_node *f;
        // node to find inorder immediate node
        bst_node *k;

        // initial with root node
        p = root;
        // assumption parent node of root node is nullptr
        F = nullptr;
        while (p != nullptr)
        {
            // found
            if (x == p->data)
            {
                // p is leaf
                if (p->left == nullptr && p->right == nullptr)
                    k = nullptr;
                // left child node of p is exist
                else if (p->left != nullptr)
                {
                    // find the most right node of p->left
                    f = p;
                    k = p->left;
                    while (k->right != nullptr)
                    {
                        f = p;
                        k = k->right;
                    }
                    // if p->left has only one child node
                    if (f == p)
                        f->left = k->left;
                    else
                        f->right = k->left;
                }
                // right child node of p is exist
                else
                {
                    // find the most left node of p->right
                    f = p;
                    k = p->right;
                    while (k->left != nullptr)
                    {
                        f = p;
                        k = k->left;
                    }
                    // if p->right has only one child node
                    if (f == p)
                        f->right = k->right;
                    else
                        f->left = k->right;
                }

                // if k exist
                if (k != nullptr)
                {
                    // replace p with k
                    k->left = p->left;
                    k->right = p->right;
                }
                // if parent node of p isn't exist
                if (F == nullptr)
                    root = k;
                // left child of F is k
                else if (x < F->data)
                    F->left = k;
                // right child of F is k
                else
                    F->right = k;

                // free the pointer of p
                delete p;
                // x found and deleted
                return 0;
            }
            else
            {
                F = p;
                // keep search node which contains x
                if (x < p->data)
                    p = p->left;
                else
                    p = p->right;
            }
        }
        // node x not found
        return -1;
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
    void print(int type, bool iterative = true)
    {
        if (root == nullptr)
        {
            cout << "tree is empty" << endl;
            return;
        }
        switch (type)
        {
        case 0:
            cout << "preorder traversal... " << (iterative ? "(iteration)" : "(resursion)") << endl;
            if (iterative)
                preorder_traversal_stack(root);
            else
                preorder_traversal(root);
            break;
        case 1:
            cout << "inorder traversal... " << (iterative ? "(iteration)" : "(resursion)") << endl;
            if (iterative)
                inorder_traversal_stack(root);
            else
                inorder_traversal(root);
            break;
        case 2:
            cout << "postorder traversal... " << (iterative ? "(iteration)" : "(resursion)") << endl;
            if (iterative)
                postorder_traversal_stack(root);
            else
                postorder_traversal(root);
            break;
        case 3:
            cout << "levelorder traversal..." << endl;
            levelorder_traversal(root);
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
//     tree.insert_iter(2);
//     tree.insert_iter(3);
//     tree.insert_iter(1);
//     tree.insert_iter(4);
//     tree.print(0);
//     tree.print(0, false);
//     tree.print(1);
//     tree.print(1, false);
//     tree.print(2);
//     tree.print(2, false);
//     tree.print(3);

//     bst_node *n1 = new bst_node();
//     n1->data = 10;
//     bst_node *n2 = new bst_node();
//     n2->data = 20;
//     tree.push(n1);
//     tree.push(n2);
//     tree.pop();
//     tree.pop();
//     if (tree.pop() == nullptr)
//         cout << "ok" << endl;
// }
