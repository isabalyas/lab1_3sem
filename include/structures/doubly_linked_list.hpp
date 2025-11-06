#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct DListItem
{
    std::string value;
    DListItem* next, * pred;
};

struct DList
{
    DListItem* head, * tail;
};

void add_to_head(const std::string& val, DList& list);

void add_to_tail(const std::string& val, DList& list);

void clear(DList& list);

DListItem* find(const std::string& val, DList list);

void add_after(const std::string& val, const std::string& after, DList& list);

void add_before(const std::string& val, const std::string& before, DList& list);

void remove_from_head(DList& list);

void remove_from_tail(DList& list);
void remove(const std::string& val, DList& list);

void remove_before(const std::string& before, DList& list);

void remove_after(const std::string& after, DList& list);

void print_forward(DList list);
void print_backward(DList list);
void read_from_file(std::string filename, DList& list);