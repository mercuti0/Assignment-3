/*
 * This function merges sorts, if not sorted, and merges sequences into
 * one larger sorted sequence.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This helper function runs through the sequence, ensuring that it is in
 * ascending order, returning true if it is.
 */
bool sortCheck(Queue<int> aOrB) {
    int size = aOrB.size();
    for (int i = 1; i < size; i++) {
        if (aOrB.dequeue() > aOrB.peek())
            return false;
    }
    return true;
}

/*
 * This function combines two inputed queues and sorts them in ascending order.
 */
Queue<int> merge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    if (!sortCheck(a) || !sortCheck(b))
        error("One or both inputed sequences are not in ascending order.");
    while (a.size() > 0 && b.size() > 0){
        if (a.peek() > b.peek())
            result.enqueue(b.dequeue());
        else if (a.peek() < b.peek())
            result.enqueue(a.dequeue());
        else {
            result.enqueue(a.dequeue());
            result.enqueue(b.dequeue());
        }
    }
    while (a.size() > 0)
        result.enqueue(a.dequeue());
    while (b.size() > 0)
        result.enqueue(b.dequeue());
    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined merge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> multiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = merge(q, result);
    }
    return result;
}

/*
 * This function recursively combines k number of sequences. Recursively,
 * k is halved and sorted in ascending order until all k sequences have
 * been sorted.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    if (all.isEmpty())
        return {};
    // Returns the first all component as we have halved as many times as possible
    else if (all.size() == 1)
        return all[0];
    // Creates vectors using subList
    Vector<Queue<int>> leftHalve = all.subList(0, all.size()/2);
    Vector<Queue<int>> rightHalve = all.subList(all.size()/2);
    // Recursively create two halves
    Queue<int> leftSorted = recMultiMerge(leftHalve);
    Queue<int> rightSorted = recMultiMerge(rightHalve);
    // Merge recursive halves each time
    result = merge(leftSorted, rightSorted);
    return result;
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("Test binary merge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(merge(a, b), expected);
    EXPECT_EQUAL(merge(b, a), expected);
}

PROVIDED_TEST("Test multiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(multiMerge(all), expected);
}

PROVIDED_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 1000;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

PROVIDED_TEST("Time binary merge operation") {
    int n = 1500000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size(), merge(a, b));
}

PROVIDED_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Test helper function") {
    EXPECT(!sortCheck({0, 1, 0}));
    EXPECT(!sortCheck({1, 1, 0}));
    EXPECT(sortCheck({0, 1, 50}));
    EXPECT(sortCheck({-1, 1, 50}));
}
STUDENT_TEST("Test binary merge, two sequences") {
    Queue<int> a = {-1, 0, 4, 10, 20, 55};
    Queue<int> b = {1, 3, 3, 4, 9, 20};
    Queue<int> c = {};
    Queue<int> d = {};
    Queue<int> e = {0, 1, 1, 2, 1, 5, 10};
    Queue<int> expected = {-1, 0, 1, 3, 3, 4, 4, 9, 10, 20, 20, 55};
    Queue<int> expectedTwo = {};
    EXPECT_EQUAL(merge(a, b), expected);
    EXPECT_EQUAL(merge(b, a), expected);
    EXPECT_EQUAL(merge(c, b), b);
    EXPECT_EQUAL(merge(b, c), b);
    EXPECT_EQUAL(merge(c, d), expectedTwo);
    EXPECT_ERROR(merge(a, e));
}
STUDENT_TEST("Time binary merge operation") {
    Queue<int> a = createSequence(2000000);
    Queue<int> b = createSequence(4000000);
    Queue<int> c = createSequence(8000000);
    Queue<int> d = createSequence(16000000);
    TIME_OPERATION(a.size(), merge(a, b));
    TIME_OPERATION(b.size(), merge(b, b));
    TIME_OPERATION(c.size(), merge(c, b));
    TIME_OPERATION(d.size(), merge(d, b));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 22000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 33000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 44000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 55000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/2;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}
STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/4;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/100;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Time multiMerge operation") {
    int n = 11000;
    int k = n/200;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), multiMerge(all));
}

STUDENT_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 2000;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

STUDENT_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 3000;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

STUDENT_TEST("Test recMultiMerge by compare to multiMerge") {
    int n = 4000;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(multiMerge(all), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 100000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 200000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 300000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 400000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 500000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 11000;
    int k = n/2;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}
STUDENT_TEST("Time recMultiMerge operation") {
    int n = 11000;
    int k = n;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 11000;
    int k = 2*n;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 11000;
    int k = 4*n;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 11000;
    int k = 8*n;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}
