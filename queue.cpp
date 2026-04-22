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
    /* ****************************************
    Constructor - initialize the queue

    @param type (bool) : LIFO or FIFO (true or false respectively)
    @return none
    @exception none
    @note defaults to LIFO if no argument is passed
    *********************************************/
    this->type = type;
    head = nullptr;
    tail = nullptr;
    size = 0;
}

Queue::~Queue() {
    /* ****************************************
    Destructor - clear all remaining nodes

    @param none
    @return none
    @exception none
    @note none
    *********************************************/
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
    /* ****************************************
    exists - check if an id is in the queue

    @param id (int) : id to search for
    @return true if found, false otherwise
    @exception none
    @note none
    *********************************************/
    bool found = false;
    Node *current = head;
    while (current != nullptr && !found) {
        if (current->data.id == id) {
            found = true;
        }
        current = current->next;
    }
    return found;
}

int Queue::find(int id) {
    /* ****************************************
    find - return the zero-based position of an id

    @param id (int) : id to search for
    @return zero-based position, or -1 if not found
    @exception none
    @note LIFO: position 0 is the tail, counting toward head.
          FIFO: position 0 is the head, counting toward tail.
    *********************************************/
    int position = -1;
    int index = 0;
    Node *current = (type == LIFO) ? tail : head;
    while (current != nullptr && position == -1) {
        if (current->data.id == id) {
            position = index;
        }
        index++;
        current = (type == LIFO) ? current->prev : current->next;
    }
    return position;
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

    @param dataOut (Data&) : struct to fill with pulled data
    @return true if pulled successfully, false if empty
    @exception none
    @note LIFO removes from head; FIFO removes from tail.
          Sets dataOut to {-1, ""} if queue is empty.
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
