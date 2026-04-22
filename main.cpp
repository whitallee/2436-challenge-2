/* ******************************************
 * File:   main.cpp
 * Author: Whit Allee
 * Test driver for the Queue ADT.
 * ******************************************/

#include "main.h"

std::string rand_string() {
    /* ****************************************
    rand_string - generate a random uppercase string

    @param none
    @return a random string of length RAND_STR_LEN
    @exception none
    @note none
    *********************************************/
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(RAND_STR_FIRST, RAND_STR_LAST);
    std::string result;
    result.reserve(RAND_STR_LEN);
    for (int i = 0; i < RAND_STR_LEN; i++) {
        result += static_cast<char>(dist(gen));
    }
    return result;
}

int main() {
    /* ****************************************
    main - test queue ADT with LIFO and FIFO

    @param none
    @return int (0 for success)
    @exception none
    @note none
    *********************************************/

    srand(static_cast<unsigned>(time(NULL)));

    // ================================================
    // SECTION 1: Constructor
    // ================================================
    cout << "=== Section 1: Constructor ===" << endl;
    {
        int counted = 0, peeked = 0;

        // default constructor should produce a valid empty LIFO queue
        Queue defaultQueue;
        if (defaultQueue.count() == 0) {
            counted++;
        }
        if (defaultQueue.peek() == -1) {
            peeked++;
        }

        // explicit LIFO
        Queue lifo(LIFO);
        if (lifo.count() == 0) {
            counted++;
        }
        if (lifo.peek() == -1) {
            peeked++;
        }

        // explicit FIFO
        Queue fifo(FIFO);
        if (fifo.count() == 0) {
            counted++;
        }
        if (fifo.peek() == -1) {
            peeked++;
        }

        // counted: 3/3 | peeked: 3/3
        cout << "counted: " << counted << "/3 | ";
        cout << "peeked: " << peeked << "/3" << endl;
        cout << "total: " << (counted + peeked) << "/6" << endl << endl;
    }

    // ================================================
    // SECTION 2: Empty Queue
    // ================================================
    cout << "=== Section 2: Empty Queue ===" << endl;
    {
        int counted = 0, peeked = 0, pulled = 0, found = 0, located = 0, cleared = 0;
        Data dataBuffer;

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // count on empty should be 0
        if (lifo.count() == 0) {
            counted++;
        }
        if (fifo.count() == 0) {
            counted++;
        }

        // peek on empty should return -1
        if (lifo.peek() == -1) {
            peeked++;
        }
        if (fifo.peek() == -1) {
            peeked++;
        }

        // pull on empty should return false and set dataBuffer to {-1, ""}
        if (!lifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }
        if (!fifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }

        // exists on empty should return false
        if (!lifo.exists(1)) {
            found++;
        }
        if (!fifo.exists(1)) {
            found++;
        }

        // find on empty should return -1
        if (lifo.find(1) == -1) {
            located++;
        }
        if (fifo.find(1) == -1) {
            located++;
        }

        // clear on empty should not crash, count stays 0
        lifo.clear();
        fifo.clear();
        if (lifo.count() == 0) {
            cleared++;
        }
        if (fifo.count() == 0) {
            cleared++;
        }

        // counted: 2/2 | peeked: 2/2 | pulled: 2/2 | found: 2/2 | located: 2/2 | cleared: 2/2
        cout << "counted: " << counted << "/2 | ";
        cout << "peeked: " << peeked << "/2 | ";
        cout << "pulled: " << pulled << "/2 | ";
        cout << "found: " << found << "/2 | ";
        cout << "located: " << located << "/2 | ";
        cout << "cleared: " << cleared << "/2" << endl;
        cout << "total: " << (counted + peeked + pulled + found + located + cleared) << "/12" << endl << endl;
    }

    // ================================================
    // SECTION 3: Invalid Push
    // ================================================
    cout << "=== Section 3: Invalid Push ===" << endl;
    {
        int pushed = 0, counted = 0;
        string emptyString = "";
        string validString = rand_string();

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // id = 0 should fail
        if (!lifo.push(0, validString)) {
            pushed++;
        }
        if (!fifo.push(0, validString)) {
            pushed++;
        }

        // negative id should fail
        if (!lifo.push(-1, validString)) {
            pushed++;
        }
        if (!fifo.push(-1, validString)) {
            pushed++;
        }

        // large negative id should fail
        if (!lifo.push(-MAX_ID, validString)) {
            pushed++;
        }
        if (!fifo.push(-MAX_ID, validString)) {
            pushed++;
        }

        // empty string should fail
        if (!lifo.push(1, emptyString)) {
            pushed++;
        }
        if (!fifo.push(1, emptyString)) {
            pushed++;
        }

        // count should still be 0 after all invalid pushes
        if (lifo.count() == 0) {
            counted++;
        }
        if (fifo.count() == 0) {
            counted++;
        }

        // pushed: 8/8 | counted: 2/2
        cout << "pushed: " << pushed << "/8 | ";
        cout << "counted: " << counted << "/2" << endl;
        cout << "total: " << (pushed + counted) << "/10" << endl << endl;
    }

    // ================================================
    // SECTION 4: Single Element
    // ================================================
    cout << "=== Section 4: Single Element ===" << endl;
    {
        int pushed = 0, counted = 0, peeked = 0, found = 0, located = 0, pulled = 0;
        Data dataBuffer;
        string info = rand_string();

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // push one item into each
        if (lifo.push(1, info)) {
            pushed++;
        }
        if (fifo.push(1, info)) {
            pushed++;
        }

        // count should be 1
        if (lifo.count() == 1) {
            counted++;
        }
        if (fifo.count() == 1) {
            counted++;
        }

        // peek should return that id without removing it
        if (lifo.peek() == 1) {
            peeked++;
        }
        if (fifo.peek() == 1) {
            peeked++;
        }

        // count should still be 1 after peek
        if (lifo.count() == 1) {
            counted++;
        }
        if (fifo.count() == 1) {
            counted++;
        }

        // exists should return true
        if (lifo.exists(1)) {
            found++;
        }
        if (fifo.exists(1)) {
            found++;
        }

        // find should return position 0
        if (lifo.find(1) == 0) {
            located++;
        }
        if (fifo.find(1) == 0) {
            located++;
        }

        // pull should return true with correct data
        if (lifo.pull(dataBuffer) && dataBuffer.id == 1 && dataBuffer.information == info) {
            pulled++;
        }
        if (fifo.pull(dataBuffer) && dataBuffer.id == 1 && dataBuffer.information == info) {
            pulled++;
        }

        // count should be 0 after pull
        if (lifo.count() == 0) {
            counted++;
        }
        if (fifo.count() == 0) {
            counted++;
        }

        // second pull should fail and set dataBuffer to {-1, ""}
        if (!lifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }
        if (!fifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }

        // pushed: 2/2 | counted: 6/6 | peeked: 2/2 | found: 2/2 | located: 2/2 | pulled: 4/4
        cout << "pushed: " << pushed << "/2 | ";
        cout << "counted: " << counted << "/6 | ";
        cout << "peeked: " << peeked << "/2 | ";
        cout << "found: " << found << "/2 | ";
        cout << "located: " << located << "/2 | ";
        cout << "pulled: " << pulled << "/4" << endl;
        cout << "total: " << (pushed + counted + peeked + found + located + pulled) << "/18" << endl << endl;
    }

    return 0;
}
