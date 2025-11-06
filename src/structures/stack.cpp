#include <iostream>
#include <fstream>
#include <string>
#include "structures/stack.hpp"

using namespace std;


void push(const string& val, StackItem*& top)
{
    if (top == nullptr)
    {
        top = new StackItem;
        top->value = val;
        top->next = nullptr;
        return;
    }
    StackItem* elem;
    elem = new StackItem;
    elem->value = val;
    elem->next = top;
    top = elem;
}

void clear(StackItem*& top)
{
    StackItem* p;
    while (top != nullptr)
    {
        p = top;
        top = top->next;
        delete p;
    }
}

void pop(StackItem*& top)
{
    if (top == nullptr)
        throw -1;
    StackItem* p = top;
    top = top->next;
    delete p;
}

string top(StackItem* top)
{
    if (top == nullptr)
        throw -2;
    return top->value;
}

void read_from_file(string filename, StackItem*& head)
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
        push(val, head);
    }
    in.close();
}