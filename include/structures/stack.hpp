#pragma once
#include <iostream>
#include <fstream>
#include <string>


struct StackItem
{
    std::string value;
    StackItem* next;
};

void push(const std::string& val, StackItem*& top);
void clear(StackItem*& top);

void pop(StackItem*& top);

std::string top(StackItem* top);

void read_from_file(std::string filename, StackItem*& head);