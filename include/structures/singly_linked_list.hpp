#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct ListItem
{
    std::string value;
    ListItem* next;
};

void add_to_head(const std::string& val, ListItem*& head);
void add_to_tail(const std::string& val, ListItem*& head);

void clear(ListItem*& head);

ListItem* find(const std::string& val, ListItem* head);

void add_after(const std::string& val, const std::string& after, ListItem* head);

void add_before(const std::string& val, const std::string& before, ListItem*& head);

void remove(const std::string& val, ListItem*& head);

void remove_from_head(ListItem*& head);

void remove_from_tail(ListItem*& head);

void remove_before(const std::string& before, ListItem*& head);

void remove_after(const std::string& after, ListItem*& head);
void print(ListItem* head);

void read_from_file(std::string filename, ListItem*& head);
