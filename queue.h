/* ******************************************
 * File:   queue.h
 * Author: Whit Allee
 * The interface for a Queue ADT.
 * A single self-contained ADT that operates
 * as either a LIFO (stack) or FIFO queue,
 * implemented internally as a linked list.
 * ******************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <string>

#define LIFO true
#define FIFO false

struct Data {
    int id;
    std::string information;
};

struct Node {
    Data data;
    Node *next;
    Node *prev;
};

class Queue {

public:

    /**********************
     * Constructors/Destructor
     **********************/
    Queue(bool = LIFO); // LIFO is true and FIFO is false (defined in this header file)
    ~Queue();

    /**********************
     * Getters/Accessors
     **********************/
    int peek();
    int count();
    bool exists(int);
    int find(int);

    /**********************
     * Setters/Mutators
     **********************/
    bool push(int, std::string&);
    bool pull(Data&);
    void clear();

private:

    /**********************
     * Attributes
     **********************/
    bool type;
    Node *head;
    Node *tail;
    int size;

};

#endif // QUEUE_H
