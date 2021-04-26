/*
 * This function returns the total number of routes Karel can take back to the origin
 * whilst only going S and W as it is somewhere N, NE, or E of the origin.
 */
#include <iostream>     // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * While Karel is N, NE, or E of the origin, we count how many distinct routes
 * Karel can follow back to the origin going W and S.
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
   EXPECT_ERROR(countRoutes(10, -2));
   EXPECT_EQUAL(countRoutes(1, 1), 1);
}
