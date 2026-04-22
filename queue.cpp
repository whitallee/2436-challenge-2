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
    /* ****************************************
    peek - return the id of the next item to be pulled

    @param none
    @return id of next item, or -1 if empty
    @exception none
    @note does not remove anything from the queue.
          LIFO peeks at head; FIFO peeks at tail.
    *********************************************/
    int id = -1;
    if (head != nullptr) {
        id = (type == LIFO) ? head->data.id : tail->data.id;
    }
    return id;
}

int Queue::count() {
    /* ****************************************
    count - return the number of items in the queue

    @param none
    @return int number of items currently in the queue
    @exception none
    @note none
    *********************************************/
    return size;
}

bool Queue::exists(int id) {
    return false;
}

int Queue::find(int id) {
    return -1;
}

bool Queue::push(int id, std::string& information) {
    /* ****************************************
    push - add an item to the head of the queue

    @param id (int) : id of item to add
    @param information (string&) : data to store
    @return true if pushed successfully, false otherwise
    @exception none
    @note id must be > 0 and information non-empty
    *********************************************/
    bool pushed = false;
    if (id > 0 && !information.empty()) {
        Node *newNode = new Node;
        newNode->data.id = id;
        newNode->data.information = information;
        newNode->prev = nullptr;
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
        size++;
        pushed = true;
    }
    return pushed;
}

bool Queue::pull(Data& dataOut) {
    /* ****************************************
    pull - remove the next item from the queue

    @param d (Data&) : struct to fill with pulled data
    @return true if pulled successfully, false if empty
    @exception none
    @note LIFO removes from head; FIFO removes from tail.
          Sets d to {-1, ""} if queue is empty.
    *********************************************/
    bool pulled = false;
    if (head != nullptr) {
        Node *toDelete = nullptr;
        if (type == LIFO) {
            dataOut = head->data;
            toDelete = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else {
            dataOut = tail->data;
            toDelete = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        }
        delete toDelete;
        size--;
        pulled = true;
    } else {
        dataOut.id = -1;
        dataOut.information = "";
    }
    return pulled;
}

void Queue::clear() {
    /* ****************************************
    clear - remove all items from the queue

    @param none
    @return void
    @exception none
    @note deletes all nodes without returning data;
          resets head, tail, and size.
    *********************************************/
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}
