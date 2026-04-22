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
        int constructed = 0, notConstructed = 0;

        // default constructor should produce a valid empty LIFO queue
        Queue defaultQueue;
        if (defaultQueue.count() == 0) {
            constructed++;
        } else {
            notConstructed++;
        }
        if (defaultQueue.peek() == -1) {
            constructed++;
        } else {
            notConstructed++;
        }

        // explicit LIFO
        Queue lifo(LIFO);
        if (lifo.count() == 0) {
            constructed++;
        } else {
            notConstructed++;
        }
        if (lifo.peek() == -1) {
            constructed++;
        } else {
            notConstructed++;
        }

        // explicit FIFO
        Queue fifo(FIFO);
        if (fifo.count() == 0) {
            constructed++;
        } else {
            notConstructed++;
        }
        if (fifo.peek() == -1) {
            constructed++;
        } else {
            notConstructed++;
        }

        cout << "constructed: " << constructed << " | notConstructed: " << notConstructed << endl << endl;
    }

    // ================================================
    // SECTION 2: Empty Queue
    // ================================================
    cout << "=== Section 2: Empty Queue ===" << endl;
    {
        int correct = 0, incorrect = 0;
        Data dataBuffer;

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // count on empty should be 0
        if (lifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }

        // peek on empty should return -1
        if (lifo.peek() == -1) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.peek() == -1) {
            correct++;
        } else {
            incorrect++;
        }

        // pull on empty should return false and set d to {-1, ""}
        if (!lifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            correct++;
        } else {
            incorrect++;
        }
        if (!fifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            correct++;
        } else {
            incorrect++;
        }

        // exists on empty should return false
        if (!lifo.exists(1)) {
            correct++;
        } else {
            incorrect++;
        }
        if (!fifo.exists(1)) {
            correct++;
        } else {
            incorrect++;
        }

        // find on empty should return -1
        if (lifo.find(1) == -1) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.find(1) == -1) {
            correct++;
        } else {
            incorrect++;
        }

        // clear on empty should not crash and leave count at 0
        lifo.clear();
        fifo.clear();
        if (lifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }

        cout << "correct: " << correct << " | incorrect: " << incorrect << endl << endl;
    }

    // ================================================
    // SECTION 3: Invalid Push
    // ================================================
    cout << "=== Section 3: Invalid Push ===" << endl;
    {
        int rejected = 0, notRejected = 0;
        string emptyString = "";
        string validString = rand_string();

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // id = 0 should fail
        if (!lifo.push(0, validString)) {
            rejected++;
        } else {
            notRejected++;
        }
        if (!fifo.push(0, validString)) {
            rejected++;
        } else {
            notRejected++;
        }

        // negative id should fail
        if (!lifo.push(-1, validString)) {
            rejected++;
        } else {
            notRejected++;
        }
        if (!fifo.push(-1, validString)) {
            rejected++;
        } else {
            notRejected++;
        }

        // large negative id should fail
        if (!lifo.push(-MAX_ID, validString)) {
            rejected++;
        } else {
            notRejected++;
        }
        if (!fifo.push(-MAX_ID, validString)) {
            rejected++;
        } else {
            notRejected++;
        }

        // empty string should fail
        if (!lifo.push(1, emptyString)) {
            rejected++;
        } else {
            notRejected++;
        }
        if (!fifo.push(1, emptyString)) {
            rejected++;
        } else {
            notRejected++;
        }

        // count should still be 0 after all invalid pushes
        if (lifo.count() == 0) {
            rejected++;
        } else {
            notRejected++;
        }
        if (fifo.count() == 0) {
            rejected++;
        } else {
            notRejected++;
        }

        cout << "rejected: " << rejected << " | notRejected: " << notRejected << endl << endl;
    }

    // ================================================
    // SECTION 4: Single Element
    // ================================================
    cout << "=== Section 4: Single Element ===" << endl;
    {
        int correct = 0, incorrect = 0;
        Data dataBuffer;
        string info = rand_string();

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // push one item into each
        lifo.push(1, info);
        fifo.push(1, info);

        // count should be 1
        if (lifo.count() == 1) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.count() == 1) {
            correct++;
        } else {
            incorrect++;
        }

        // peek should return that id without removing it
        if (lifo.peek() == 1) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.peek() == 1) {
            correct++;
        } else {
            incorrect++;
        }

        // count should still be 1 after peek
        if (lifo.count() == 1) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.count() == 1) {
            correct++;
        } else {
            incorrect++;
        }

        // exists should return true
        if (lifo.exists(1)) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.exists(1)) {
            correct++;
        } else {
            incorrect++;
        }

        // find should return position 0
        if (lifo.find(1) == 0) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.find(1) == 0) {
            correct++;
        } else {
            incorrect++;
        }

        // pull should return true with correct data
        if (lifo.pull(dataBuffer) && dataBuffer.id == 1 && dataBuffer.information == info) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.pull(dataBuffer) && dataBuffer.id == 1 && dataBuffer.information == info) {
            correct++;
        } else {
            incorrect++;
        }

        // count should be 0 after pull
        if (lifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }
        if (fifo.count() == 0) {
            correct++;
        } else {
            incorrect++;
        }

        // second pull should fail and set dataBuffer to {-1, ""}
        if (!lifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            correct++;
        } else {
            incorrect++;
        }
        if (!fifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            correct++;
        } else {
            incorrect++;
        }

        cout << "correct: " << correct << " | incorrect: " << incorrect << endl << endl;
    }

    return 0;
}
