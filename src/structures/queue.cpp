#include <iostream>
#include <fstream>
#include <string>

#include "structures/queue.hpp"

using namespace std;


void push_back(const string& val, Queue& q)
{
    if (q.first == nullptr)
    {
        q.first = new QueueItem;
        q.first->value = val;
        q.first->next = nullptr;
        q.last = q.first;
        return;
    }
    QueueItem* elem;
    elem = new QueueItem;
    elem->value = val;
    elem->next = nullptr;
    q.last->next = elem;
    q.last = elem;
}

void clear(Queue& q)
{
    QueueItem* p;
    while (q.first != nullptr)
    {
        p = q.first;
        q.first = q.first->next;
        delete p;
    }
    q.last = nullptr;
}

void pop_front(Queue& q)
{
    if (q.first == nullptr)
        return;
    QueueItem* p = q.first;
    q.first = q.first->next;
    delete p;
}

string front(Queue q)
{
    if (q.first == nullptr)
        throw - 2;
    return q.first->value;
}

bool read_from_file(string filename, Queue& q)
{
    clear(q);
    ifstream in;
    in.open(filename);
    if (!in.is_open())
    {
        q.first = q.last = nullptr;
        return false;
    }
    string val;
    while (!in.eof())
    {
        in >> val;
        push_back(val, q);
    }
    return true;
}