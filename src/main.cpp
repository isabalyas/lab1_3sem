#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "../include/structures/singly_linked_list.hpp"
#include "../include/structures/doubly_linked_list.hpp"
#include "../include/structures/stack.hpp"
#include "../include/structures/queue.hpp"
#include "../include/structures/tree.hpp"
#include "../include/structures/array.hpp"

using namespace std;

// ИНТЕРАКТИВНЫЙ МЕТОД РАБОТЫ С АСД
struct Database {
    map<string, Array> arrays;
    map<string, ListItem*> singly_lists;
    map<string, DList> doubly_lists;
    map<string, StackItem*> stacks;
    map<string, Queue> queues;
    map<string, TreeNode*> trees;
};

Database db;

string executeCommand(const string& query) {
    istringstream iss(query);
    string command, structure_name, value1, value2, value3;
    
    iss >> command >> structure_name;
    
    // Массив
    if (command == "MPUSH") {
        iss >> value1;
        if (!db.arrays.count(structure_name)) {
            array_create(db.arrays[structure_name], 10);
        }
        if (iss >> value2) {
            array_insert(stoi(value2), value1, db.arrays[structure_name]);
        } else {
            array_push_back(value1, db.arrays[structure_name]);
        }
        return value1;
    }
    else if (command == "MDEL") {
        iss >> value1;
        if (db.arrays.count(structure_name)) {
            array_remove(stoi(value1), db.arrays[structure_name]);
        }
        return "OK";
    }
    else if (command == "MGET") {
        iss >> value1;
        if (db.arrays.count(structure_name)) {
            return array_get(stoi(value1), db.arrays[structure_name]);
        }
        return "";
    }
        else if (command == "MSET") {
        iss >> value1 >> value2;
        if (db.arrays.count(structure_name)) {
            array_set(stoi(value1), value2, db.arrays[structure_name]);
            return "OK";
        }
        return "ARRAY_NOT_FOUND";
    }
    
    // Односвязный список
    else if (command == "FPUSH") {
        iss >> value1;
        if (!db.singly_lists.count(structure_name)) {
            db.singly_lists[structure_name] = nullptr;
        }
        add_to_head(value1, db.singly_lists[structure_name]);
        return value1;
    }
    else if (command == "FPUSHT") {
        iss >> value1;
        if (!db.singly_lists.count(structure_name)) {
            db.singly_lists[structure_name] = nullptr;
        }
        add_to_tail(value1, db.singly_lists[structure_name]);
        return value1;
    }
    else if (command == "FDEL") {
        iss >> value1;
        if (db.singly_lists.count(structure_name)) {
            remove(value1, db.singly_lists[structure_name]);
        }
        return "OK";
    }
    else if (command == "FDELH") {
        if (db.singly_lists.count(structure_name) && db.singly_lists[structure_name] != nullptr) {
            remove_from_head(db.singly_lists[structure_name]);
            return "OK";
        }
        return "LIST_EMPTY";
    }
    else if (command == "FDELT") {
        if (db.singly_lists.count(structure_name) && db.singly_lists[structure_name] != nullptr) {
            remove_from_tail(db.singly_lists[structure_name]);
            return "OK";
        }
        return "LIST_EMPTY";
    }
    else if (command == "FGET") {
        iss >> value1;
        if (db.singly_lists.count(structure_name)) {
            auto found = find(value1, db.singly_lists[structure_name]);
            return (found != nullptr) ? "FOUND" : "NOT_FOUND";
        }
        return "NOT_FOUND";
    }
    
    // Двусвязный список
    else if (command == "LPUSH") {
        iss >> value1;
        if (!db.doubly_lists.count(structure_name)) {
            db.doubly_lists[structure_name] = {nullptr, nullptr};
        }
        add_to_head(value1, db.doubly_lists[structure_name]);
        return value1;
    }
    else if (command == "LPUSHT") {
        iss >> value1;
        if (!db.doubly_lists.count(structure_name)) {
            db.doubly_lists[structure_name] = {nullptr, nullptr};
        }
        add_to_tail(value1, db.doubly_lists[structure_name]);
        return value1;
    }
    else if (command == "LDEL") {
        iss >> value1;
        if (db.doubly_lists.count(structure_name)) {
            remove(value1, db.doubly_lists[structure_name]);
        }
        return "OK";
    }
    else if (command == "LDELH") {
        if (db.doubly_lists.count(structure_name) && db.doubly_lists[structure_name].head != nullptr) {
            remove_from_head(db.doubly_lists[structure_name]);
            return "OK";
        }
        return "LIST_EMPTY";
    }
    else if (command == "LDELT") {
        if (db.doubly_lists.count(structure_name) && db.doubly_lists[structure_name].tail != nullptr) {
            remove_from_tail(db.doubly_lists[structure_name]);
            return "OK";
        }
        return "LIST_EMPTY";
    }
    else if (command == "LGET") {
        iss >> value1;
        if (db.doubly_lists.count(structure_name)) {
            auto found = find(value1, db.doubly_lists[structure_name]);
            return (found != nullptr) ? "FOUND" : "NOT_FOUND";
        }
        return "NOT_FOUND";
    }

    //Стек
    else if (command == "SPUSH") {
        iss >> value1;
        if (!db.stacks.count(structure_name)) {
            db.stacks[structure_name] = nullptr;
        }
        push(value1, db.stacks[structure_name]);
        return value1;
    }
    else if (command == "SPOP") {
        if (db.stacks.count(structure_name) && db.stacks[structure_name] != nullptr) {
            string result = top(db.stacks[structure_name]);
            pop(db.stacks[structure_name]);
            return result;
        }
        return "STACK_EMPTY";
    }
    else if (command == "STOP") {
        if (db.stacks.count(structure_name) && db.stacks[structure_name] != nullptr) {
            try {
                return ::top(db.stacks[structure_name]);
            } catch (int) {
                return "STACK_EMPTY";
            }
        }
        return "STACK_EMPTY";
    }
    
    // Очередь
    else if (command == "QPUSH") {
        iss >> value1;
        if (!db.queues.count(structure_name)) {
            db.queues[structure_name] = {nullptr, nullptr};
        }
        push_back(value1, db.queues[structure_name]);
        return value1;
    }
    else if (command == "QPOP") {
        if (db.queues.count(structure_name) && db.queues[structure_name].first != nullptr) {
            string result = front(db.queues[structure_name]);
            pop_front(db.queues[structure_name]);
            return result;
        }
        return "QUEUE_EMPTY";
    }
        else if (command == "QFRONT") {
        if (db.queues.count(structure_name) && db.queues[structure_name].first != nullptr) {
            try {
                return front(db.queues[structure_name]);
            } catch (int) {
                return "QUEUE_EMPTY";
            }
        }
        return "QUEUE_EMPTY";
    }
    
    // Дерево
    else if (command == "TINSERT") {
        iss >> value1;
        if (!db.trees.count(structure_name)) {
            db.trees[structure_name] = nullptr;
        }
        add(value1, db.trees[structure_name]);
        return value1;
    }
    else if (command == "TDEL") {
        iss >> value1;
        if (db.trees.count(structure_name)) {
            remove(value1, db.trees[structure_name]);
        }
        return "OK";
    }
    else if (command == "TGET") {
        iss >> value1;
        if (db.trees.count(structure_name)) {
            auto found = find(value1, db.trees[structure_name]);
            return (found != nullptr) ? "FOUND" : "NOT_FOUND";
        }
        return "NOT_FOUND";
    }
    
    // Вывод
    else if (command == "PRINT") {
        if (db.arrays.count(structure_name)) {
            cout << "Array " << structure_name << ": ";
            array_print(db.arrays[structure_name]);
            cout << endl;
        }
        else if (db.singly_lists.count(structure_name)) {
            cout << "Singly List " << structure_name << ": ";
            print(db.singly_lists[structure_name]);
            cout << endl;
        }
        else if (db.doubly_lists.count(structure_name)) {
            cout << "Doubly List " << structure_name << " (forward): ";
            print_forward(db.doubly_lists[structure_name]);
            cout << endl;
            cout << "Doubly List " << structure_name << " (backward): ";
            print_backward(db.doubly_lists[structure_name]);
            cout << endl;
        }
        else if (db.stacks.count(structure_name)) {
            cout << "Stack " << structure_name << ": ";
            StackItem* temp = db.stacks[structure_name];
            while (temp != nullptr) {
                cout << temp->value << " ";
                temp = temp->next;
            }
            cout << endl;
        }
        else if (db.queues.count(structure_name)) {
            cout << "Queue " << structure_name << ": ";
            QueueItem* temp = db.queues[structure_name].first;
            while (temp != nullptr) {
                cout << temp->value << " ";
                temp = temp->next;
            }
            cout << endl;
        }
        else if (db.trees.count(structure_name)) {
            cout << "Tree " << structure_name << ": ";
            print(db.trees[structure_name]);
            cout << endl;
        }
        else {
            return "STRUCTURE_NOT_FOUND";
        }
        return "PRINTED";
    }
    
    return "UNKNOWN_COMMAND";
}

int main() {
    cout << "Database Management System Started" << endl;
    cout << "Available commands: MPUSH, MDEL, MGET, MSET, FPUSH, FPUSHT, FDEL, FDELH, FDELT, FGET, LPUSH, LPUSHT, LDEL, LDELH, LDELT, LGET, SPUSH, SPOP, STOP, QPUSH, QPOP, QFRONT, TINSERT, TDEL, TGET, PRINT" << endl;
    
    // ИНТЕРАКТИВНЫЙ ВВОД ОПЕРАЦИЙ
    string input;
    cout << "\nEnter commands (or 'exit' to quit):" << endl;
    
    while (true) {
        cout << "> ";
        getline(cin, input);
        
        if (input == "exit" || input == "quit") {
            break;
        }
        
        if (!input.empty()) {
            string result = executeCommand(input);
            if (result != "PRINTED") {
                cout << "Result: " << result << endl;
            }
        }
    }
    
    for (auto& [name, list] : db.singly_lists) {
        clear(list);
    }
    for (auto& [name, list] : db.doubly_lists) {
        clear(list);
    }
    for (auto& [name, stack] : db.stacks) {
        clear(stack);
    }
    for (auto& [name, queue] : db.queues) {
        clear(queue);
    }
    for (auto& [name, tree] : db.trees) {
        clear(tree);
    }
    
    cout << "Program finished." << endl;
    return 0;
}