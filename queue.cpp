/* ******************************************
 * File:   queue.cpp
 * Author: Whit Allee
 * The implementation for a Queue ADT.
 * A single self-contained ADT that operates
 * as either a LIFO (stack) or FIFO queue,
 * implemented internally as a linked list.
 * ******************************************/

#include "queue.h"

Queue::Queue(bool type) {
    this->type = type;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

Queue::~Queue() {
    clear();
}

int Queue::peek() {
    return -1;
}

int Queue::count() {
    return size;
}

bool Queue::exists(int id) {
    return false;
}

int Queue::find(int id) {
    return -1;
}

bool Queue::push(int id, std::string& information) {
    return false;
}

bool Queue::pull(Data& d) {
    return false;
}

void Queue::clear() {
}
