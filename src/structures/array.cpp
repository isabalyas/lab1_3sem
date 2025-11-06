#include <iostream>
#include <fstream>
#include <string>
#include "../../include/structures/array.hpp"

using namespace std;

void array_create(Array& arr, size_t initial_capacity) {
    arr.data = new string[initial_capacity];
    arr.capacity = initial_capacity;
    arr.size = 0;
}

void array_clear(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.capacity = 0;
    arr.size = 0;
}

void array_resize(Array& arr, size_t new_capacity) {
    string* new_data = new string[new_capacity];
    
    for (size_t i = 0; i < arr.size && i < new_capacity; ++i) {
        new_data[i] = arr.data[i];
    }
    
    delete[] arr.data;
    arr.data = new_data;
    arr.capacity = new_capacity;
    if (arr.size > new_capacity) {
        arr.size = new_capacity;
    }
}

void array_push_back(const string& val, Array& arr) {
    if (arr.size >= arr.capacity) {
        array_resize(arr, arr.capacity * 2);
    }
    arr.data[arr.size] = val;
    arr.size++;
}

void array_insert(size_t index, const string& val, Array& arr) {
    if (index > arr.size) {
        index = arr.size;
    }
    
    if (arr.size >= arr.capacity) {
        array_resize(arr, arr.capacity * 2);
    }
    
    for (size_t i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    
    arr.data[index] = val;
    arr.size++;
}

string array_get(size_t index, Array& arr) {
    if (index >= arr.size) {
        return "";
    }
    return arr.data[index];
}

void array_remove(size_t index, Array& arr) {
    if (index >= arr.size) {
        return;
    }
    
    for (size_t i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    
    arr.size--;
    
    if (arr.size < arr.capacity / 4 && arr.capacity > 10) {
        array_resize(arr, arr.capacity / 2);
    }
}

void array_set(size_t index, const string& val, Array& arr) {
    if (index < arr.size) {
        arr.data[index] = val;
    }
}

size_t array_length(Array& arr) {
    return arr.size;
}

void array_print(Array& arr) {
    if (arr.size == 0) {
        cout << "Array is empty!";
        return;
    }
    
    for (size_t i = 0; i < arr.size; ++i) {
        cout << arr.data[i] << ' ';
    }
}

void array_read_from_file(const string& filename, Array& arr) {
    array_clear(arr);
    array_create(arr, 10);
    
    ifstream in;
    in.open(filename);
    if (!in.is_open()) {
        return;
    }
    
    string val;
    while (in >> val) {
        array_push_back(val, arr);
    }
    in.close();
}