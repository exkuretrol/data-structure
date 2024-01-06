#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class DoublyCircularLinkedList
{
    struct node
    {
        int data;
        struct node *prev;
        struct node *next;
    };

private:
    struct node *head, *tail;

    struct node *create_node(int el)
    {
        struct node *p = new node();
        p->data = el;
        p->next = nullptr;
        p->prev = nullptr;
        return p;
    }

    void initialization()
    {
        struct node *p = create_node(0);
        p->next = p;
        p->prev = p;
        head = tail = p;
    }

    struct node *search_node_by_data(int el)
    {
        struct node *c = head->next;
        while (c->data != el && c != head)
        {
            c = c->next;
        }
        return c;
    }

    struct node *search_node_by_address(struct node *t)
    {
        struct node *c = head->next;
        while (c != t && c != head)
        {
            c = c->next;
        }
        return c;
    }

    int delete_node_by_address(struct node *p)
    {
        struct node *o, *q;
        if (p == head)
            return -1;
        o = p->prev;
        q = p->next;
        if (p == tail)
            tail = o;
        o->next = q;
        q->prev = o;
        delete p;
        return 0;
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
            // cout << p << " ";
            cout << extract_last_4_chars(p) << " ";
            // cout << "[ " << p->prev;
            cout << "[ " << extract_last_4_chars(p->prev);
            cout << " | " << p->data;
            cout << " | " << extract_last_4_chars(p->next);
            // cout << " | " << p->next;
            cout << " ]" << endl;
        }
    }

public:
    DoublyCircularLinkedList()
    {
        this->initialization();
    }

    void insert_front(int el)
    {
        struct node *p = create_node(el);
        p->next = head->next;
        p->prev = head;
        head->next->prev = p;
        head->next = p;
        tail = head->prev;
    }

    void insert_rear(int el)
    {
        struct node *p = create_node(el);
        p->prev = tail;
        p->next = tail->next;
        tail->next = p;
        tail = p;
        head->prev = tail;
    }

    int insert_after(int target, int num)
    {
        struct node *p, *q;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        q = create_node(num);
        q->next = p->next;
        q->prev = p;
        p->next->prev = q;
        if (p->next == head)
            tail = q;
        p->next = q;
        return 0;
    }

    int insert_before(int target, int num)
    {
        struct node *o, *p;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        o = create_node(num);
        o->next = p;
        o->prev = p->prev;
        p->prev->next = o;
        p->prev = o;
        return 0;
    }

    void insert_n_nodes(int n, int m = 0, int M = 100)
    {
        srand(time(0));
        int num;

        for (int i = 0; i < n; i++)
        {
            num = rand() % (M - m + 1) + m;
            insert_rear(num);
            cout << num << " ";
        }
    }

    int delete_node(int target)
    {
        struct node *p;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        delete_node_by_address(p);
        return 0;
    }

    int delete_before(int target)
    {
        struct node *p;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        if (p == head->next)
            return -2;
        delete_node_by_address(p->prev);
        return 0;
    }

    int delete_after(int target)
    {
        struct node *p;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        if (p == tail)
            return -2;
        delete_node_by_address(p->next);
        return 0;
    }

    int delete_front()
    {
        if (head == tail)
            return -1;
        delete_node_by_address(head->next);
        return 0;
    }

    int delete_rear()
    {
        if (head == tail)
            return -1;
        delete_node_by_address(tail);
        return 0;
    }

    void invert()
    {
        struct node *t, *s, *r;
        t = nullptr;
        s = head;
        r = head->next;
        tail = head->next;
        while (r != head)
        {
            t = s;
            s = r;
            r = r->next;
            s->next = t;
            s->prev = r;
        }
        head->next = s;
    }

    int search_node(int el)
    {
        struct node *p = search_node_by_data(el);
        if (p == head)
            return -1;
        return 0;
    }

    /**
     * Prints the data of all nodes in the linked list.
     */
    void print_nodes()
    {
        struct node *p = head;
        cout << "[ ", print_node(p), cout << " (empty node)", p = p->next;
        if (head != p)
        {
            cout << " ↹ ", print_node(p), p = p->next;
            for (; p != head; p = p->next)
                cout << " ↹ ", print_node(p);
        }
        cout << " ↹ (empty node) ]" << endl;
    }

    void print_detailed_nodes()
    {
        struct node *p;
        cout << "(head)" << endl;
        print_node(head, true);
        cout << "(tail)" << endl;
        print_node(tail, true);
        cout << endl
             << endl;

        for (p = head->next; p != head; p = p->next)
        {
            print_node(p, true);
        }
        print_nodes();
    }

    void delete_all_nodes()
    {
        struct node *c = head->next;
        while (c != head)
        {
            struct node *t = c;
            c = c->next;
            delete t;
        }
        head->next = head;
        tail = c;
    }
};

// signed main()
// {
//     class DoublyCircularLinkedList list = DoublyCircularLinkedList();
//     // list.insert_n_nodes(5);
//     list.insert_rear(10);
//     list.insert_rear(20);
//     list.insert_rear(30);
//     list.insert_rear(40);
//     list.insert_rear(50);
//     list.print_detailed_nodes();
//     cout << list.insert_before(10, 60) << endl;
//     list.print_detailed_nodes();
// }
