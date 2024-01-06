#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class SinglyCircularLinkedList
{
    struct node
    {
        int data;
        struct node *next;
    };

private:
    struct node *head, *tail;

    struct node *create_node(int el)
    {
        struct node *p = new node();
        p->data = el;
        return p;
    }

    pair<struct node *, struct node *> search_node_by_address_with_previous(struct node *t, int depth = 1)
    {
        struct node *c = head->next, *p = nullptr, *pp = nullptr;
        if (c == t)
        {
            return depth == 1 ? make_pair(head, t) : make_pair(tail, t);
        }
        if (c->next == t)
        {
            return depth == 1 ? make_pair(c, t) : make_pair(head, t);
        }

        while (c != t && c != head)
        {
            pp = p;
            p = c;
            c = c->next;
        }
        return depth == 1 ? make_pair(p, c) : make_pair(pp, c);
    }

    void initialization()
    {
        struct node *p = create_node(0);
        p->next = p;
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

    void delete_node_by_address(struct node *p)
    {
        struct node *o, *q;
        tie(o, p) = search_node_by_address_with_previous(p, 1);
        q = p->next;
        o->next = q;
        delete p;
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
            cout << " | " << extract_last_4_chars(p->next);
            // cout << " | " << p->next;
            cout << " ]" << endl;
        }
    }

public:
    SinglyCircularLinkedList()
    {
        initialization();
    }

    void insert_front(int el)
    {
        struct node *p = create_node(el);
        p->next = head->next;
        // TODO: first node, move tail pointer to p
        if (head->next == head)
            tail = p;
        head->next = p;
    }

    void insert_rear(int el)
    {
        struct node *p = create_node(el);
        p->next = tail->next;
        tail->next = p;
        tail = p;
    }

    int insert_after(int target, int num)
    {
        struct node *p, *q;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        q = create_node(num);
        q->next = p->next;
        p->next = q;
        if (q->next == head)
            tail = q;
        return 0;
    }

    int insert_before(int target, int num)
    {
        struct node *n, *o, *p;
        p = search_node_by_data(target);
        if (p == head)
            return -1;
        o = create_node(num);
        tie(n, p) = search_node_by_address_with_previous(p, 1);
        o->next = p;
        n->next = o;
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
        }
    }

    int delete_node(int el)
    {
        struct node *p;
        p = search_node_by_data(el);
        if (p == head)
            return -1;
        delete_node_by_address(p);
        return 0;
    }

    int delete_front()
    {
        if (head->next == tail)
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

    int delete_after(int el)
    {
        struct node *p = search_node_by_data(el);
        if (p == head)
            return -1;
        if (p == tail)
            return -1;
        struct node *q = p->next;
        if (q == tail)
            tail = p;
        p->next = q->next;
        delete q;
        return 0;
    }

    int delete_before(int el)
    {
        struct node *n, *p = search_node_by_data(el);
        if (p == head)
            return -1;
        tie(n, p) = search_node_by_address_with_previous(p, 2);
        struct node *o = n->next;
        n->next = p;
        delete o;
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
            cout << " ↦ ", print_node(p), p = p->next;
            for (; p != head; p = p->next)
                cout << " ↦ ", print_node(p);
        }
        cout << " ↦ (empty node) ]" << endl;
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
//     SinglyCircularLinkedList list = SinglyCircularLinkedList();
//     list.insert_rear(100);
//     list.print_detailed_nodes();
// }
