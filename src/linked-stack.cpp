#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class LinkedStack
{
    struct node
    {
        int data;
        struct node *prev;
    };

private:
    struct node *top, *base;

    struct node *create_node(int el)
    {
        struct node *p = new node();
        p->data = el;
        p->prev = nullptr;
        return p;
    }

    void initialization()
    {
        struct node *p = create_node(0);
        p->prev = p;
        base = p;
        top = p;
    }

    string extract_last_4_chars(struct node *p)
    {
        stringstream ss;
        ss << p;
        string address = ss.str();
        string last_4_chars = address.substr(address.length() - 4);
        return last_4_chars;
    }

    void print_node(struct node *p, bool detailed = false)
    {
        if (!detailed)
            cout << p->data;
        else
        {
            cout << extract_last_4_chars(p) << " ";
            // cout << p << " ";
            cout << "[ " << p->data;
            cout << " | " << extract_last_4_chars(p->prev);
            // cout << " | " << p->prev;
            cout << " ]" << endl;
        }
    }

public:
    LinkedStack()
    {
        initialization();
    }

    int push(int el)
    {
        struct node *p = create_node(el);
        p->prev = top;
        top = p;
        return top->data;
    }

    int pop()
    {
        struct node *p = top;
        if (top == base)
            return -1;
        top = top->prev;
        int el = p->data;
        delete p;
        return el;
    }

    void print_nodes()
    {
        struct node *p = top;
        for (; p != base; p = p->prev)
        {
            print_node(p, false);
            cout << " ↦ ";
        }
        print_node(p, false);
        cout << "⏚" << endl;
    }

    void print_detailed_nodes()
    {
        cout << "(top)\t";
        print_node(top, true);
        cout << "(base)\t";
        print_node(base, true);
        cout << endl
             << endl;

        struct node *p = top;
        for (; p != base; p = p->prev)
        {
            print_node(p, true);
        }
    }
};

signed main()
{
    LinkedStack stack = LinkedStack();
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    stack.print_detailed_nodes();
}
