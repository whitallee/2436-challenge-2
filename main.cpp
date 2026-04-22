/* ******************************************
 * File:   main.cpp
 * Author: Whit Allee
 * Test driver for the Queue ADT.
 * ******************************************/

#include "main.h"

int main() {

    Data d;
    string s;

    // --- LIFO push/pull ---
    cout << "=== LIFO push/pull ===" << endl;
    Queue lifo(LIFO);

    s = "first";  lifo.push(1, s);
    s = "second"; lifo.push(2, s);
    s = "third";  lifo.push(3, s);

    // expect: 3, 2, 1
    while (lifo.pull(d)) {
        cout << "pulled: " << d.id << " - " << d.information << endl;
    }

    // pull from empty
    cout << "pull empty (expect false): " << lifo.pull(d) << ", id=" << d.id << endl;

    // --- FIFO push/pull ---
    cout << "\n=== FIFO push/pull ===" << endl;
    Queue fifo(FIFO);

    s = "first";  fifo.push(1, s);
    s = "second"; fifo.push(2, s);
    s = "third";  fifo.push(3, s);

    // expect: 1, 2, 3
    while (fifo.pull(d)) {
        cout << "pulled: " << d.id << " - " << d.information << endl;
    }

    // pull from empty
    cout << "pull empty (expect false): " << fifo.pull(d) << ", id=" << d.id << endl;

    // --- invalid push ---
    cout << "\n=== invalid push ===" << endl;
    Queue q(LIFO);
    s = "valid";
    cout << "push id=0  (expect false): " << q.push(0, s) << endl;
    s = "";
    cout << "push empty (expect false): " << q.push(1, s) << endl;

    return 0;
}
