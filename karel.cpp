/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>     // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int countRoutes(int street, int avenue) {
    if (street < 1 || avenue < 1)
        error("Input is not within a valid range.");
    if (street == 1 || avenue == 1)
        return 1;
    else {
        return countRoutes(street - 1, avenue) + countRoutes(street, avenue - 1);
        }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test countRoutes") {
   EXPECT_EQUAL(countRoutes(2, 3), 3);
}

STUDENT_TEST("Test countRoutes") {
   EXPECT_EQUAL(countRoutes(100, 1), 1);
   EXPECT_EQUAL(countRoutes(6, 2), 6);
   EXPECT_ERROR(countRoutes(0, 1));
   EXPECT_EQUAL(countRoutes(1, 1), 1);
}
