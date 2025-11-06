#include <iostream>
#include <fstream>
#include <string>
#include "structures/doubly_linked_list.hpp"

using namespace std;

void add_to_head(const string& val, DList& list)
{
    if (list.head == nullptr)
    {
        list.head = new DListItem;
        list.head->value = val;
        list.head->next = list.head->pred = nullptr;
        list.tail = list.head;
        return;
    }
    DListItem* elem;
    elem = new DListItem;
    elem->value = val;
    elem->next = list.head;
    elem->pred = nullptr;
    list.head->pred = elem;
    list.head = elem;
}

void add_to_tail(const string& val, DList& list)
{
    if (list.head == nullptr)
    {
        list.head = new DListItem;
        list.head->value = val;
        list.head->next = list.head->pred = nullptr;
        list.tail = list.head;
        return;
    }
    DListItem* elem;
    elem = new DListItem;
    elem->value = val;
    elem->next = nullptr;
    elem->pred = list.tail;
    list.tail->next = elem;
    list.tail = elem;
}

void clear(DList& list)
{
    DListItem* p;
    while (list.head != nullptr)
    {
        p = list.head;
        list.head = list.head->next;
        delete p;
    }
    list.tail = nullptr;
}

DListItem* find(const string& val, DList list)
{
    while (list.head != nullptr)
    {
        if (list.head->value == val)
            return list.head;
        list.head = list.head->next;
    }
    return nullptr;
}

void add_after(const string& val, const string& after, DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = find(after, list);
    if (p == nullptr)
        return;
    DListItem* elem;
    elem = new DListItem;
    elem->value = val;
    elem->next = p->next;
    p->next = elem;
    elem->pred = p;
    if (elem->next != nullptr)
        elem->next->pred = elem;
    else
        list.tail = elem;
}

void add_before(const string& val, const string& before, DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = find(before, list);
    if (p == nullptr)
        return;
    DListItem* elem;
    elem = new DListItem;
    elem->value = val;
    elem->next = p;    
    elem->pred = p->pred;
    if (elem->pred != nullptr)
        elem->pred->next = elem;
    else
        list.head = elem;
    p->pred = elem;
}

void remove_from_head(DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = list.head;
    list.head = list.head->next;
    if (list.head != nullptr)
        list.head->pred = nullptr;
    else
        list.tail = nullptr;
    delete p;
}

void remove_from_tail(DList& list)
{
    if (list.tail == nullptr)
        return;
    DListItem* p = list.tail;
    list.tail = list.tail->pred;
    if (list.tail != nullptr)
        list.tail->next = nullptr;
    else
        list.head = nullptr;
    delete p;
}

void remove(const string& val, DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = find(val, list);
    if (p == nullptr)
        return;    
    if (p == list.head)
        remove_from_head(list);
    else if (p == list.tail)
        remove_from_tail(list);
    else
    {
        p->pred->next = p->next;
        p->next->pred = p->pred;
        delete p;
    }
}

void remove_before(const string& before, DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = find(before, list);
    if (p == nullptr || p == list.head)
        return;
    if (p->pred == list.head)
        remove_from_head(list);    
    else
    {
        p = p->pred;
        p->pred->next = p->next;
        p->next->pred = p->pred;
        delete p;
    }
}

void remove_after(const string& after, DList& list)
{
    if (list.head == nullptr)
        return;
    DListItem* p = find(after, list);
    if (p == nullptr || p == list.tail)
        return;
    if (p->next == list.tail)
        remove_from_tail(list);
    else
    {
        p = p->next;
        p->pred->next = p->next;
        p->next->pred = p->pred;
        delete p;
    }
}

void print_forward(DList list)
{
    if (list.head == nullptr)
    {
        cout << "List is empty!";
        return;
    }
    while (list.head != nullptr)
    {
        cout << list.head->value << ' ';
        list.head = list.head->next;
    }
}

void print_backward(DList list)
{
    if (list.tail == nullptr)
    {
        cout << "List is empty!";
        return;
    }
    while (list.tail != nullptr)
    {
        cout << list.tail->value << ' ';
        list.tail = list.tail->pred;
    }
}

void read_from_file(string filename, DList& list)
{
    clear(list);
    ifstream in;
    in.open(filename);
    if (!in.is_open())
    {
        list.head = list.tail = nullptr;
        return;
    }
    string val;
    while (!in.eof())
    {
        in >> val;
        add_to_head(val, list);
    }
    in.close();
}