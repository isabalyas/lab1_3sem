#pragma once
#include <iostream>
#include <fstream>
#include <string>


struct QueueItem
{
    std::string value;
    QueueItem* next;
};

struct Queue
{
    QueueItem* first, * last;
};

void push_back(const std::string& val, Queue& q);
void clear(Queue& q);

void pop_front(Queue& q);
std::string front(Queue q);

bool read_from_file(std::string filename, Queue& q);