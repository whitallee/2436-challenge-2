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

    int sectionsPassed = 0;

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

        if (counted == 3 && peeked == 3) {
            sectionsPassed++;
        }
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

        if (counted == 2 && peeked == 2 && pulled == 2 && found == 2 && located == 2 && cleared == 2) {
            sectionsPassed++;
        }
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

        if (pushed == 8 && counted == 2) {
            sectionsPassed++;
        }
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

        if (pushed == 2 && counted == 6 && peeked == 2 && found == 2 && located == 2 && pulled == 4) {
            sectionsPassed++;
        }
    }

    // ================================================
    // SECTION 5: LIFO Order
    // ================================================
    cout << "=== Section 5: LIFO Order ===" << endl;
    {
        int pushed = 0, counted = 0, peeked = 0, found = 0, located = 0, pulled = 0;
        Data dataBuffer;
        string info = rand_string();

        Queue lifo(LIFO);

        // push 5 items in order 1-5; head will be 5, tail will be 1
        for (int i = 1; i <= 5; i++) {
            if (lifo.push(i, info)) {
                pushed++;
            }
        }

        // count should be 5
        if (lifo.count() == 5) {
            counted++;
        }

        // peek should return 5 (head, last pushed)
        if (lifo.peek() == 5) {
            peeked++;
        }

        // exists should be true for all 5 ids
        for (int i = 1; i <= 5; i++) {
            if (lifo.exists(i)) {
                found++;
            }
        }

        // find: position 0 = tail = id 1, position 4 = head = id 5
        if (lifo.find(1) == 0) {
            located++;
        }
        if (lifo.find(2) == 1) {
            located++;
        }
        if (lifo.find(3) == 2) {
            located++;
        }
        if (lifo.find(4) == 3) {
            located++;
        }
        if (lifo.find(5) == 4) {
            located++;
        }

        // pull should return 5, 4, 3, 2, 1 (LIFO: removes from head)
        for (int i = 5; i >= 1; i--) {
            if (lifo.pull(dataBuffer) && dataBuffer.id == i) {
                pulled++;
            }
            if (lifo.count() == i - 1) {
                counted++;
            }
        }

        // count should be 0 after all pulls
        if (lifo.count() == 0) {
            counted++;
        }

        // pushed: 5/5 | counted: 7/7 | peeked: 1/1 | found: 5/5 | located: 5/5 | pulled: 5/5
        cout << "pushed: " << pushed << "/5 | ";
        cout << "counted: " << counted << "/7 | ";
        cout << "peeked: " << peeked << "/1 | ";
        cout << "found: " << found << "/5 | ";
        cout << "located: " << located << "/5 | ";
        cout << "pulled: " << pulled << "/5" << endl;
        cout << "total: " << (pushed + counted + peeked + found + located + pulled) << "/28" << endl << endl;

        if (pushed == 5 && counted == 7 && peeked == 1 && found == 5 && located == 5 && pulled == 5) {
            sectionsPassed++;
        }
    }

    // ================================================
    // SECTION 6: FIFO Order
    // ================================================
    cout << "=== Section 6: FIFO Order ===" << endl;
    {
        int pushed = 0, counted = 0, peeked = 0, found = 0, located = 0, pulled = 0;
        Data dataBuffer;
        string info = rand_string();

        Queue fifo(FIFO);

        // push 5 items in order 1-5; head will be 5, tail will be 1
        for (int i = 1; i <= 5; i++) {
            if (fifo.push(i, info)) {
                pushed++;
            }
        }

        // count should be 5
        if (fifo.count() == 5) {
            counted++;
        }

        // peek should return 1 (tail, first pushed)
        if (fifo.peek() == 1) {
            peeked++;
        }

        // exists should be true for all 5 ids
        for (int i = 1; i <= 5; i++) {
            if (fifo.exists(i)) {
                found++;
            }
        }

        // find: position 0 = head = id 5 (last pushed), counting toward tail
        if (fifo.find(5) == 0) {
            located++;
        }
        if (fifo.find(4) == 1) {
            located++;
        }
        if (fifo.find(3) == 2) {
            located++;
        }
        if (fifo.find(2) == 3) {
            located++;
        }
        if (fifo.find(1) == 4) {
            located++;
        }

        // pull should return 1, 2, 3, 4, 5 (FIFO: removes from tail)
        for (int i = 1; i <= 5; i++) {
            if (fifo.pull(dataBuffer) && dataBuffer.id == i) {
                pulled++;
            }
            if (fifo.count() == 5 - i) {
                counted++;
            }
        }

        // count should be 0 after all pulls
        if (fifo.count() == 0) {
            counted++;
        }

        // pushed: 5/5 | counted: 7/7 | peeked: 1/1 | found: 5/5 | located: 5/5 | pulled: 5/5
        cout << "pushed: " << pushed << "/5 | ";
        cout << "counted: " << counted << "/7 | ";
        cout << "peeked: " << peeked << "/1 | ";
        cout << "found: " << found << "/5 | ";
        cout << "located: " << located << "/5 | ";
        cout << "pulled: " << pulled << "/5" << endl;
        cout << "total: " << (pushed + counted + peeked + found + located + pulled) << "/28" << endl << endl;

        if (pushed == 5 && counted == 7 && peeked == 1 && found == 5 && located == 5 && pulled == 5) {
            sectionsPassed++;
        }
    }

    // ================================================
    // SECTION 7: Clear
    // ================================================
    cout << "=== Section 7: Clear ===" << endl;
    {
        int pushed = 0, counted = 0, peeked = 0, pulled = 0;
        Data dataBuffer;
        string info = rand_string();

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // push several items into each
        for (int i = 1; i <= 5; i++) {
            if (lifo.push(i, info)) {
                pushed++;
            }
            if (fifo.push(i, info)) {
                pushed++;
            }
        }

        // count should be 5 before clear
        if (lifo.count() == 5) {
            counted++;
        }
        if (fifo.count() == 5) {
            counted++;
        }

        // clear both
        lifo.clear();
        fifo.clear();

        // count should be 0 after clear
        if (lifo.count() == 0) {
            counted++;
        }
        if (fifo.count() == 0) {
            counted++;
        }

        // peek should return -1 after clear
        if (lifo.peek() == -1) {
            peeked++;
        }
        if (fifo.peek() == -1) {
            peeked++;
        }

        // pull should fail after clear
        if (!lifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }
        if (!fifo.pull(dataBuffer) && dataBuffer.id == -1 && dataBuffer.information == "") {
            pulled++;
        }

        // push again after clear should work normally
        for (int i = 1; i <= 5; i++) {
            if (lifo.push(i, info)) {
                pushed++;
            }
            if (fifo.push(i, info)) {
                pushed++;
            }
        }

        // count should be 5 again
        if (lifo.count() == 5) {
            counted++;
        }
        if (fifo.count() == 5) {
            counted++;
        }

        // pushed: 20/20 | counted: 6/6 | peeked: 2/2 | pulled: 2/2
        cout << "pushed: " << pushed << "/20 | ";
        cout << "counted: " << counted << "/6 | ";
        cout << "peeked: " << peeked << "/2 | ";
        cout << "pulled: " << pulled << "/2" << endl;
        cout << "total: " << (pushed + counted + peeked + pulled) << "/30" << endl << endl;

        if (pushed == 20 && counted == 6 && peeked == 2 && pulled == 2) {
            sectionsPassed++;
        }
    }

    // ================================================
    // SECTION 8: Random Stress Test
    // ================================================
    cout << "=== Section 8: Random Stress Test ===" << endl;
    {
        Data dataBuffer;
        bool lifoStressPassed = false;
        bool fifoStressPassed = false;

        Queue lifo(LIFO);
        Queue fifo(FIFO);

        // seed both queues with initial items before stress test
        for (int i = 0; i < SEED_SIZE; i++) {
            string str = rand_string();
            lifo.push((rand() % MAX_ID) + 1, str);
            fifo.push((rand() % MAX_ID) + 1, str);
        }

        // cases 1-2: push valid (mutating x2)
        // cases 3-4: pull (mutating x2)
        // case 5: peek (read-only)
        // case 6: count (read-only)
        // case 7: exists (read-only)
        // case 8: find (read-only)
        // case 9: push invalid (rejection test)

        // LIFO stress test
        cout << "running LIFO stress test (" << RANDOM_ITERATIONS << " iterations)..." << endl;
        {
            int passed = 0, total = 0;
            int startCount = lifo.count();
            int netChange = 0;

            for (int i = 0; i < RANDOM_ITERATIONS; i++) {
                switch (rand() % CHOICES + 1) {
                    case 1:
                    case 2: {
                        string str = rand_string();
                        total++;
                        if (lifo.push((rand() % MAX_ID) + 1, str)) {
                            passed++;
                            netChange++;
                        }
                        break;
                    }
                    case 3:
                    case 4:
                        total++;
                        if (lifo.pull(dataBuffer)) {
                            passed++;
                            netChange--;
                        } else if (lifo.count() == 0) {
                            passed++;
                        }
                        break;
                    case 5:
                        total++;
                        if ((lifo.count() == 0 && lifo.peek() == -1) || (lifo.count() > 0 && lifo.peek() > 0)) {
                            passed++;
                        }
                        break;
                    case 6:
                        total++;
                        if (lifo.count() >= 0) {
                            passed++;
                        }
                        break;
                    case 7:
                        total++;
                        lifo.exists((rand() % MAX_ID) + 1);
                        passed++;
                        break;
                    case 8:
                        total++;
                        lifo.find((rand() % MAX_ID) + 1);
                        passed++;
                        break;
                    case 9: {
                        string str = rand_string();
                        total++;
                        if (!lifo.push(-(rand() % MAX_ID + 1), str)) {
                            passed++;
                        }
                        break;
                    }
                }
            }

            lifoStressPassed = (passed == total) && (startCount + netChange == lifo.count());
            cout << "  LIFO total: " << passed << "/" << total << " | ";
            cout << "net change check: " << (startCount + netChange == lifo.count() ? "passed" : "FAILED") << endl;
        }

        // FIFO stress test
        cout << "running FIFO stress test (" << RANDOM_ITERATIONS << " iterations)..." << endl;
        {
            int passed = 0, total = 0;
            int startCount = fifo.count();
            int netChange = 0;

            for (int i = 0; i < RANDOM_ITERATIONS; i++) {
                switch (rand() % CHOICES + 1) {
                    case 1:
                    case 2: {
                        string str = rand_string();
                        total++;
                        if (fifo.push((rand() % MAX_ID) + 1, str)) {
                            passed++;
                            netChange++;
                        }
                        break;
                    }
                    case 3:
                    case 4:
                        total++;
                        if (fifo.pull(dataBuffer)) {
                            passed++;
                            netChange--;
                        } else if (fifo.count() == 0) {
                            passed++;
                        }
                        break;
                    case 5:
                        total++;
                        if ((fifo.count() == 0 && fifo.peek() == -1) || (fifo.count() > 0 && fifo.peek() > 0)) {
                            passed++;
                        }
                        break;
                    case 6:
                        total++;
                        if (fifo.count() >= 0) {
                            passed++;
                        }
                        break;
                    case 7:
                        total++;
                        fifo.exists((rand() % MAX_ID) + 1);
                        passed++;
                        break;
                    case 8:
                        total++;
                        fifo.find((rand() % MAX_ID) + 1);
                        passed++;
                        break;
                    case 9: {
                        string str = rand_string();
                        total++;
                        if (!fifo.push(-(rand() % MAX_ID + 1), str)) {
                            passed++;
                        }
                        break;
                    }
                }
            }

            fifoStressPassed = (passed == total) && (startCount + netChange == fifo.count());
            cout << "  FIFO total: " << passed << "/" << total << " | ";
            cout << "net change check: " << (startCount + netChange == fifo.count() ? "passed" : "FAILED") << endl;
        }
        cout << endl;

        if (lifoStressPassed && fifoStressPassed) {
            sectionsPassed++;
        }
    }

    // ================================================
    // FINAL RESULT
    // ================================================
    cout << "=== FINAL RESULT: " << sectionsPassed << "/8 SECTIONS PASSED ===" << endl;
    if (sectionsPassed == 8) {
        cout << "ALL TESTS PASSED" << endl;
    } else {
        cout << "SOME TESTS FAILED" << endl;
    }

    return (sectionsPassed == 8) ? 0 : 1;
}
