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

    // SECTION 1: Constructor

    cout << "=== Section 1: Constructor ===" << endl;
    {
        int passed = 0, failed = 0;

        // default constructor should produce a valid empty LIFO queue
        Queue def;
        if (def.count() == 0) {
            passed++;
        } else {
            failed++;
        }
        if (def.peek() == -1) {
            passed++;
        } else {
            failed++;
        }

        // explicit LIFO
        Queue lifo(LIFO);
        if (lifo.count() == 0) {
            passed++;
        } else {
            failed++;
        }
        if (lifo.peek() == -1) {
            passed++;
        } else {
            failed++;
        }

        // explicit FIFO
        Queue fifo(FIFO);
        if (fifo.count() == 0) {
            passed++;
        } else {
            failed++;
        }
        if (fifo.peek() == -1) {
            passed++;
        } else {
            failed++;
        }

        cout << "passed: " << passed << " | failed: " << failed << endl << endl;
    }

    return 0;
}
