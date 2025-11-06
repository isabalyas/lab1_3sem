#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Array {
    string* data;
    size_t capacity;
    size_t size;
};

void array_create(Array& arr, size_t initial_capacity);
void array_clear(Array& arr);
void array_resize(Array& arr, size_t new_capacity);
void array_push_back(const string& val, Array& arr);
void array_insert(size_t index, const string& val, Array& arr);
string array_get(size_t index, Array& arr);
void array_remove(size_t index, Array& arr);
void array_set(size_t index, const string& val, Array& arr);
size_t array_length(Array& arr);
void array_print(Array& arr);
void array_read_from_file(const string& filename, Array& arr);