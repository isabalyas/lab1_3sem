#include <iostream>
#include <fstream>
#include <string>
#include "structures/singly_linked_list.hpp"

using namespace std;



void add_to_head(const string& val, ListItem*& head)
{
    if (head == nullptr)
    {
        head = new ListItem;
        head->value = val;
        head->next = nullptr;
        return;
    }
    ListItem* elem;
    elem = new ListItem;
    elem->value = val;
    elem->next = head;
    head = elem;
}

void add_to_tail(const string& val, ListItem*& head)
{
    if (head == nullptr)
    {
        head = new ListItem;
        head->value = val;
        head->next = nullptr;
        return;
    }
    ListItem* p = head;
    while (p->next != nullptr)
        p = p->next;
    ListItem* elem;
    elem = new ListItem;
    elem->value = val;
    elem->next = nullptr;
    p->next = elem;
}

void clear(ListItem*& head)
{
    ListItem* p;
    while (head != nullptr)
    {
        p = head;
        head = head->next;
        delete p;
    }
}

ListItem* find(const string& val, ListItem* head)
{
    while (head != nullptr)
    {
        if (head->value == val)
            return head;
        head = head->next;
    }
    return nullptr;
}

void add_after(const string& val, const string& after, ListItem* head)
{
    if (head == nullptr)
        return;
    ListItem* p = find(after, head);
    if (p == nullptr)
        return;
    ListItem* elem;
    elem = new ListItem;
    elem->value = val;
    elem->next = p->next;
    p->next = elem;
}

void add_before(const string& val, const string& before, ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head, *pred = nullptr;
    while (p != nullptr)
    {
        if (p->value == before)
            break;
        pred = p;
        p = p->next;
    }
    if (p == nullptr)
        return;
    if (pred == nullptr)
        add_to_head(val, head);
    else
    {
        ListItem* elem;
        elem = new ListItem;
        elem->value = val;
        elem->next = p;
        pred->next = elem;
    }
}

void remove(const string& val, ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head, * pred = nullptr;
    while (p != nullptr)
    {
        if (p->value == val)
            break;
        pred = p;
        p = p->next;
    }
    if (p == nullptr)
        return;
    if (pred == nullptr)
    {
        head = head->next;
        delete p;
    }
    else
    {
        pred->next = p->next;
        delete p;
    }
}

void remove_from_head(ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head;
    head = head->next;
    delete p;
}

void remove_from_tail(ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head, *pred = nullptr;
    while (p->next != nullptr)
    {
        pred = p;
        p = p->next;
    }
    if (pred == nullptr)
    {
        delete p;
        head = nullptr;
    }
    else
    {
        pred->next = p->next;
        delete p;
    }
}

void remove_before(const string& before, ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head, *pred1 = nullptr, *pred2 = nullptr;
    while (p != nullptr)
    {
        if (p->value == before)
            break;
        pred2 = pred1;
        pred1 = p;
        p = p->next;
    }
    if (p == nullptr || p == head) {

        return;
    }
    if (pred1 == head)
        remove_from_head(head);
    else
    {
        pred2->next = p;
        delete pred1;
    }
}

void remove_after(const string& after, ListItem*& head)
{
    if (head == nullptr)
        return;
    ListItem* p = head;
    while (p != nullptr)
    {
        if (p->value == after)
            break;        
        p = p->next;
    }
    if (p == nullptr || p->next == nullptr)
        return;
    ListItem* q = p->next;
    p->next = p->next->next;
    delete q;
}

void print(ListItem* head)
{
    if (head == nullptr)
    {
        cout << "List is empty!";
        return;
    }
    while (head != nullptr)
    {
        cout << head->value << ' ';
        head = head->next;
    }
}

void read_from_file(string filename, ListItem*& head)
{
    clear(head);
    ifstream in;
    in.open(filename);
    if (!in.is_open())
    {
        head = nullptr;
        return;
    }
    string val;
    while (!in.eof())
    {
        in >> val;
        add_to_head(val, head);
    }
    in.close();
}